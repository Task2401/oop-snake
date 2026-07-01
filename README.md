# Retro Snake Game (C++ / OOP / Raylib)

![Language](https://img.shields.io/badge/language-C%2B%2B11-blue.svg)
![Build](https://img.shields.io/badge/build-MinGW%20/%20Make-green.svg)
![Framework](https://img.shields.io/badge/framework-Raylib-red.svg)

A modular, clean object-oriented implementation of the classic Snake game featuring an arcade-style camera system, dynamic eagle predators, and smooth grid-aligned state synchronization.

---

## Overview
The project features a fully controllable Snake (@, o) navigating an infinite procedural grid populated with static score-increasing apples and dynamic hunting eagles (▲) that actively change directions. The codebase strictly decouples game loop calculations, state tracking, and graphical rendering to ensure optimal modularity and zero logical race conditions.

## Key Technical Features

### 1. State-Driven Architectural Pattern (MVC / SDC)
The game utilizes a strict state-decoupling architecture to isolate calculations from visual frames (implementation in State.cpp):
* **State Engine:** Tracks entity matrices, frame pacing (`FRAMES_PER_STATE`), score records, and game-over criteria safely away from the window loop.
* **Input Layer:** Captures non-blocking edge-triggered keyboard events (WASD / Arrows) using a custom `Keystates` struct.
* **Deterministic Boundary Management:** Dynamically prunes off-screen objects beyond a spatial threshold (600 units) to minimize structural overhead and memory footprint.

### 2. Autonomous Entity Logic
* **Dynamic Predator Pathfinding:** Eagles (▲) navigate the map independently, utilizing stochastic probability arrays (`EAGLE_NEXT_DIRECTION_PROBABILITY`) to randomize their patrol vectors.
* **Grid-Based Collisions:** Implements high-precision spatial distance evaluation (`calculateDistance`) between the snake head, node bodies, and game objects to prevent overlapping issues and physics clipping.
* **Procedural Spawning Loops:** Regulates real-time object pooling to guarantee a minimum density of active predators and apples around the player's immediate field of view.

### 3. Architecture & OOP Standards
* **Decoupled Graphics Abstraction:** The `Interface` layer strictly isolates all Raylib framework calls, preventing external framework dependencies from leaking into the core application logic.
* **Encapsulation & Data Hiding:** Strict usage of getter and constant safety functions (`const std::vector<GameObject>&`) protecting entity lists from unintended mutations.
* **Data Structures:** Custom standard library lists (`std::list<Position>`) utilizing highly efficient `push_back` and `pop_front` mutations for linear time complexity queue handling during snake locomotion.

## Installation & Usage

### 1. Prerequisites
* **C++ Compiler:** G++ (MinGW-w64 for Windows / GCC for Linux).
* **Framework:** Raylib (linked via library path vectors).
* **Build Tool:** GNU Make (`mingw32-make` or `make`).

### 2. Compilation
Build the project using the optimized cross-platform Makefile. The configuration automatically targets object generation rules.

**Windows (PowerShell / CMD):**
```powershell
mingw32-make
```

**Linux / macOS:**
```bash
make
```

### 3. Execution
Run the compiled executable directly from the root directory:

**Windows (PowerShell / CMD):**
```powershell
.\snake_game.exe
```

**Linux / macOS:**
```bash
./snake_game
```

### 4. Clean Project Files
To erase previous build binaries and .o object allocations before a fresh compilation:

**Windows (PowerShell / CMD):**
```powershell
mingw32-make clean
```

**Linux / macOS:**
```bash
make clean
```

### Game Visuals & Interface Description

The graphical **interface** focuses on rendering a smooth, high-contrast gameplay environment that decouples internal physics grid positioning from presentation layers.

- **Camera System (Smooth Tracking):** he game features a 2D camera viewport initialized with centered offsets. Instead of standard static views, the camera locks directly onto the coordinate point of the snake's head, dynamically scrolling across the rendering space as the player navigates.

- **The Player Entity (Snake):** Rendered as a sequence of linked, high-visibility geometry. The main head node is drawn as a distinct dark green circle to indicate vector direction, while trailing body segments are rendered as bright lime green circles, ensuring optimal contrast against background colors.

- **Collectible Objects (Apples):** Represented by solid red circular forms distributed dynamically across coordinates. When the calculated Manhattan distance to the snake's head reaches zero, a score mutation event triggers, expanding the tail node list.

- **Predator Entities (Eagles):** Drawn as solid black triangles that actively patrol surrounding zones. A strict collision framework evaluates overlapping area states between any vertex of the black triangles and the green body array of the player, prompting a transition into the Game Over overlay state.

- **Interface Overlays & Contrast:** Standard game viewports render over a consistent light gray background matrix. Menu structures (Start Screen, Pause Screen, and Game Over Screen) utilize semi-transparent alpha-blended black background overlays with precisely calculated text alignments to prevent visual clipping.

### Directory Structure
```plaintext
oop-snake/
├── assets/             # Multimedia files (game_icon.png)
├── include/            # C++ Header files (.h code declarations)
├── src/                # C++ Source files (.cpp system implementations)
└── Makefile            # Native cross-platform automated compilation script
```


### Author

**Anastasis - Christos Kyrios (Task2401)** _Software Engineer / Computer Science Student_
