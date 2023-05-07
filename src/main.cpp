#include "../include/Game.hpp"

int main() {
    std::unique_ptr<Game> pacman = std::make_unique<Game>();
    pacman->start();
    return 0;
}