# StrategicBoardGame-MCST-OpenMP

<!-- ABOUT THE PROJECT -->
## About The Project
This project implements Monte Carlo Search Tree (MCST) using the OpenMP library, aiming to achieve efficient, multithreaded and faster tree search and reinforcement learning operations. It leverages `openmp` for parallel processing.

### Built With
* [![C++][C++-logo]][C++-url]

## Prerequisites
Ensure that OpenMP are installed before building the project:

- **OpenMP**: This is usually installed by default with most compilers. If not, refer to the [OpenMP installation instructions](https://www.openmp.org/resources/openmp-compilers-tools/).
- If you are using macOS, I recommend installing the OpenMP library using Homebrew.

## Paths
Ensure that include library paths to the make file:
```
HEADERS_INCLUDE = "$(shell pwd)/../include"

OPENMP_INCLUDE_PATH = "$(shell brew --prefix libomp)/include"
OPENMP_LIBRARY_PATH = "$(shell brew --prefix libomp)/lib"
```

<!-- HOW TO BUILD -->
## How to Build
1. Clone the repository:
   ```sh
   git clone https://github.com/altugparlak/StrategicBoardGame-MCTS-OpenMP.git
   ```
2. Navigate to the project directory:
   ```sh
   cd StrategicBoardGame-MCTS-OpenMP
   ```
3. Navigate to the build directory and compile with CMake:
   ```sh
   cd build
   make
   ```
4. Run the application:
   ```sh
   ./main.exe <debug(true|false)> 
   ```
5. Play:
   ```
   (っ◔◡◔)っ Welcome to Strategic Board Game ♗
   Menu:
   1. Play with AI ☺⚔♝
   2. Multiplayer ☺⚔☺
   3. Change difficulty ✎
   4. Exit the program ☒
   ```
   
<!-- RESULTS -->
## Results
```
AI performance results is going to be added soon.
```

<!-- Badge Images -->
[C++-logo]: https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white

<!-- Badge URLs -->
[C++-url]: https://isocpp.org/
