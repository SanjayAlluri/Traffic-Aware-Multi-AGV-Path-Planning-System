# Traffic-Aware Multi-AGV Path Planning System

A C++ simulation that plans collision-free paths for multiple Automated Guided Vehicles (AGVs) on a grid using Time-Expanded A* Search and dynamic space-time reservation tables.

---

## Features

- **Time-Expanded A* Search** — plans paths through (x, y, t) space so agents avoid each other across both position and time
- **Space-Time Reservation Tables** — cells reserved per timestep using a custom-hashed `unordered_map` for O(1) collision lookups
- **Traffic-Aware Routing** — penalizes high-traffic cells in the cost function to distribute load across the grid
- **Path Efficiency Metrics** — reports actual vs single-agent optimal path length per AGV
- **Infeasibility Detection** — identifies and reports when no valid collision-free path exists
- **CLI Scaling** — configurable grid size and AGV count at runtime

---

## Benchmark Results

| Grid Size | AGVs | Planning Time | Avg Path Overhead |
|-----------|------|---------------|-------------------|
| 20 × 20   | 10   | 38 ms         | < 1 step          |
| 30 × 30   | 25   | 179 ms        | ~2.5 steps        |
| 50 × 50   | 50   | 3742 ms       | ~3 steps          |

Zero collisions detected across all scenarios.

---

## Build & Run

**Requirements:** C++17 or later

```bash
g++ -O2 -std=c++17 main.cpp astar.cpp simulator.cpp -o agv
./agv <grid_size> <num_agvs>
```

**Examples:**
```bash
./agv 20 10
./agv 30 25
./agv 50 50
```

---

## Project Structure

```
├── astar.h        # Hash structs, type aliases, A* declaration
├── astar.cpp      # Time-expanded A* implementation
├── simulator.h    # AGV struct definition
├── simulator.cpp  # Simulation loop and metrics
└── main.cpp       # Grid generation, AGV spawning, CLI, benchmarking
```
