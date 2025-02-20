# Rain Effect Simulation

A C++ project that simulates a rain effect in the console using multithreading and randomization. This project is built with Visual Studio and designed to demonstrate console manipulation and threading in C++.

---

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Tech Stack](#tech-stack)
4. [Setup and Usage](#setup-and-usage)
5. [Project Structure](#project-structure)
6. [Credits](#credits)
7. [License](#license)

---

## Project Overview
This project creates a visually appealing rain effect in the console window by using multiple threads, random character generation, and console manipulation techniques. It is a fun demonstration of multithreading, mutex locks, and random number generation in C++.

---

## Features
- **Multithreaded Execution**: Each raindrop is handled by a separate thread.
- **Randomized Effects**: Raindrops have varying speeds, lengths, and positions.
- **Console Manipulation**: Includes cursor movement, color changes, and window resizing.
- **Customizable Parameters**: Configure rain density, trail length, and speed.

---

## Tech Stack
- **Language**: C++
- **Libraries**:
  - `<iostream>` for console output
  - `<thread>` for multithreading
  - `<mutex>` for thread synchronization
  - `<random>` for randomization
  - Windows-specific libraries (`<windows.h>`) for console manipulation
- **IDE**: Visual Studio

---

## Setup and Usage

### Prerequisites
1. Install Visual Studio (with C++ development tools).
2. Clone this repository from GitHub.

### Steps to Build and Run
1. Open the project in Visual Studio.
2. Build the solution (`Ctrl+Shift+B`).
3. Run the executable (`F5` or `Ctrl+F5`).

### Customization
You can modify the following parameters in `main.cpp`:
- `rainCount`: Number of raindrops.
- `rainLength`: Length of the rain column.
- `maxWindowCharX`: Width of the console window.
- `trailLengthVal`: Length of the trailing effect.

---

## Project Structure

| File               | Description                                   |
|--------------------|-----------------------------------------------|
| `main.cpp`         | Entry point of the program                   |
| `ConsoleManager.h` | Header file for console management utilities  |
| `ConsoleManager.cpp` | Implementation of console utilities         |
| `RainEffect.h`     | Header file for rain effect logic             |
| `RainEffect.cpp`   | Implementation of rain effect logic           |

---

## Credits
- **Lucas Jeanes**: Developer of the project.
- **Michelle Lynch**: ASCII art contribution used in the header comment.
