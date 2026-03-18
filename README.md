# Satellite-orbit-simulation
This project simulates the motion of two satellites interacting under Newtonian gravity using C++. The simulation outputs trajectory and energy data to a CSV file, which is then analyzed and visualized using Python.

# 🚀 Satellite Orbit Simulation (C++ + Python)

## 📌 Overview
This project simulates the motion of two satellites interacting under **Newtonian gravity** using C++. The simulation outputs trajectory and energy data to a CSV file, which is then analyzed and visualized using Python.

---

## ⚙️ Features

### 🔹 C++ Simulation
- 2D vector-based physics engine
- Gravitational force calculation
- Semi-implicit Euler integration
- Energy calculations:
  - Kinetic Energy
  - Potential Energy
  - Total Energy
- CSV export

### 🔹 Python Analysis
- Data inspection using pandas
- Orbit trajectory visualization
- Distance vs Time graph
- Velocity vs Time graph
- Orbit classification

---

## 🧠 Physics

### Newton’s Law of Gravitation
F = (G * m1 * m2) / r²

### Integration Method
Semi-Implicit Euler:
- velocity = velocity + acceleration * dt
- position = position + velocity * dt

---
