# PacMan

[![CMake](https://github.com/FelixLusseau/pacman-cpp/actions/workflows/cmake.yml/badge.svg)](https://github.com/FelixLusseau/pacman-cpp/actions/workflows/cmake.yml)
[![Author](https://img.shields.io/badge/author-@LouiseCouture-blue)](https://github.com/LouiseCouture)
[![Author](https://img.shields.io/badge/author-@FelixLusseau-blue)](https://github.com/FelixLusseau)

- Cloner le projet

- Installer les dépendances :

```bash
sudo apt install libsdl2-dev -y
```

- Pour compiler la première fois :

```bash
mkdir build && cd build
cmake -S ../ -B ./
```

- Ensuite pour recompiler, depuis le dossier build :

```bash
cmake --build ./
```

- Pour lancer le programme :

```bash
./PacMan
```

- Pour nettoyer le projet et recompiler depuis la racine du projet :

```bash
./clean-and-compile.sh
```