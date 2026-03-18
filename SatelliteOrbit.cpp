#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include <filesystem>
using namespace std;

class vector2D {
public:
    double x, y;
    vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    vector2D operator+(const vector2D& other) const {
        return vector2D(x + other.x, y + other.y);
    }
    vector2D operator-(const vector2D& other) const {
        return vector2D(x-other.x, y-other.y);
    }
    vector2D operator*(double scalar) const {
        return vector2D(x * scalar, y * scalar);
    }
    double magnitude() const {
        double mag = sqrt(x*x + y*y);
        return mag;
    }
    vector2D normalize() const {
        double mag = magnitude();
        if (mag == 0) return vector2D(0,0);
        return vector2D(x/mag, y/mag);
    }
};

class Satellite {
public:
    vector2D position;
    vector2D velocity;
    vector2D force;
    vector2D acceleration;
    double mass;
    Satellite(double mass, vector2D position, vector2D velocity) : mass(mass), position(position), velocity(velocity), force(0, 0), acceleration(0, 0) {}

    void resetForce() {
        force = vector2D(0, 0);
    }

    void addforce(const Satellite& other) {
        const double G = 6.67430e-11;
        vector2D diff = other.position - position;
        double distance = diff.magnitude();
        if (distance == 0) return;
        double epsilon = 1e-5;
        double F = (G * mass * other.mass) / ((distance * distance) + epsilon);
        vector2D direction = diff.normalize();
        force = force + direction * F;
    }

    void update(double dt) {
        // semi-implicit Euler method
        acceleration = force * (1/mass);
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt;
        force = vector2D(0, 0);
    }
};

class Simulation {
public:
    vector<Satellite> satellites;
    Simulation(const vector<Satellite>& satellites) : satellites(satellites) {}

    void step(double dt) {
        for (auto& sat : satellites)
            sat.resetForce();
        for (size_t i = 0; i < satellites.size(); i++) {
            for (size_t j = 0; j < satellites.size(); j++) {
                if (i != j)
                    satellites[i].addforce(satellites[j]);
            }
        }
        for (auto& sat : satellites)
            sat.update(dt);
    }

    double kineticEnergy() {
        double KE = 0;
        for (auto& sat : satellites) {
            double v = sat.velocity.magnitude();
            KE += 0.5 * sat.mass * v * v;
        }
        return KE;
    }

    double potentialEnergy() {
        const double G = 6.67430e-11;
        double PE = 0;
        for (size_t i = 0; i < satellites.size(); i++) {
            for (size_t j = i + 1; j < satellites.size(); j++) {
                double distance = (satellites[i].position - satellites[j].position).magnitude();
                PE += - (G * satellites[i].mass * satellites[j].mass) / distance;
            }
        }
        return PE;
    }

    double totalEnergy() {
        return kineticEnergy() + potentialEnergy();
    }
};

int main() {
    double dt;
    int step, choice;
    string obj1, obj2;
    double mass1, mass2;
    double x1, x2, y1, y2;
    double vx1, vy1, vx2, vy2;

    cout << "Enter the name of the of the first object: ";
    getline(cin, obj1);
    cout <<"Enter mass of " << obj1 << " :";
    cin >> mass1;
    cout << "Enter position (x y) of " << obj1 << ": ";
    cin >> x1 >> y1;
    cout << "Enter velocity (vx vy) of " << obj1 << ": ";
    cin >> vx1 >> vy1;

    cin.ignore();

    cout << "Enter the name of the of the second object: ";
    getline(cin, obj2);
    cout <<"Enter mass of " << obj2 << " :";
    cin >> mass2;
    cout << "Enter position (x y) of " << obj2 << ": ";
    cin >> x2 >> y2;
    cout << "Enter velocity (vx vy) of " << obj2 << ": ";
    cin >> vx2 >> vy2;

    cout << "Enter time step (dt): ";
    cin >> dt;

    cout << "Enter number of steps: ";
    cin >> step;

    Satellite object1(mass1, vector2D(x1, y1), vector2D(vx1, vy1));
    Satellite object2(mass2, vector2D(x2, y2), vector2D(vx2, vy2));
    Simulation sim({object1, object2});

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Run FULL simulation & save CSV\n";
        cout << "2. Show Kinetic Energy\n";
        cout << "3. Show Potential Energy\n";
        cout << "4. Show Total Energy\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {

            case 1: {
                ofstream out("C:\\Users\\shrey\\OneDrive\\Documents\\Desktop\\Projects\\Satellite Orbit\\orbit_data.csv");
                out << "Time,X1,Y1,X2,Y2,Energy\n";
                for (int i = 0; i < step; i++) {
                    sim.step(dt);
                    out << i << "," << sim.satellites[0].position.x << "," << sim.satellites[0].position.y << "," 
                        << sim.satellites[1].position.x << "," << sim.satellites[1].position.y << "," << sim.totalEnergy() << "\n";
                }
                out.close();
                cout << "Data saved to orbit_data.csv\n" << endl;
                cout << "Path: " << std::filesystem::current_path() << endl;
                break;
            }

            case 2:
                cout << "Kinetic Energy: " << sim.kineticEnergy() << " J\n";
                break;

            case 3:
                cout << "Potential Energy: " << sim.potentialEnergy() << " J\n";
                break;

            case 4:
                cout << "Total Energy: " << sim.totalEnergy() << " J\n";
                break;

            case 5:
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}