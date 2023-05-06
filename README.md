# PacMan

[![CMake](https://github.com/FelixLusseau/pacman-cpp/actions/workflows/cmake.yml/badge.svg)](https://github.com/FelixLusseau/pacman-cpp/actions/workflows/cmake.yml)
[![Author](https://img.shields.io/badge/author-@LouiseCouture-blue)](https://github.com/LouiseCouture)
[![Author](https://img.shields.io/badge/author-@FelixLusseau-blue)](https://github.com/FelixLusseau)

- Clone the project

- Install dependencies :

```bash
sudo apt install libsdl2-dev -y
```

- To compile the first time :

```bash
mkdir build && cd build
cmake -S ../ -B ./
```

- Then to rebuild, from the build directory :

```bash
cmake --build ./ -j8
```

- To launch the game :

```bash
./PacMan
```

- To clean and recompile from the root of the project :

```bash
./clean-and-compile.sh
```