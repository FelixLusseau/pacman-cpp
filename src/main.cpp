#include "../include/Game.hpp"

int main() {
    std::unique_ptr<Game> pac_man = std::make_unique<Game>();
    pac_man->start();
    return 0;
}