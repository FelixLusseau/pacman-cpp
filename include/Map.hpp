#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

enum class Tile { Wall, Empty, Dot, PowerPellet, GhostHouse, GhostHouseDoor, EscapeTunnel };

class Map {
  private:
    std::vector<std::vector<Tile>> map;

  public:
    Map();
    inline std::vector<std::vector<Tile>> getMap(void){
      return map;
    }
};

#endif