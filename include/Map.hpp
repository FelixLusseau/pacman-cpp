#ifndef MAP_HPP
#define MAP_HPP

#include <SDL.h>
#include <iostream>
#include <vector>

enum class Tile { Wall, Empty, Dot, PowerPellet, GhostHouse, GhostHouseDoor, EscapeTunnel };

class Map {
  private:
    std::vector<std::vector<Tile>> map;
    int height_;
    int width_;
    int colonne_;
    int ligne_;

  public:
    Map(SDL_Rect bg);

    inline std::vector<std::vector<Tile>> getMap(void) { return map; }

    inline int getWidth(void) { return width_; }
    inline int getHeight(void) { return height_; }
    inline int getColonne(void) { return colonne_; }
    inline int getLigne(void) { return ligne_; }
};

#endif