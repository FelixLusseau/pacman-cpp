#ifndef MAP_HPP
#define MAP_HPP

#include <SDL.h>
#include <iostream>
#include <vector>

enum class Tile { Wall, Empty, Dot, PowerPellet, GhostHouse, GhostHouseDoor, EscapeTunnel, Corridor };

class Map {
  private:
    std::vector<std::vector<Tile>> map;
    int height_;
    int width_;
    long unsigned int colonne_;
    long unsigned int ligne_;

  public:
    Map(const SDL_Rect bg);

    /**
     * @brief Get the Map object
     *
     * @return std::vector<std::vector<Tile>>&
     */
    inline std::vector<std::vector<Tile>> &getMap(void) { return map; }

    /**
     * @brief Get the Width of a case of the map
     *
     * @return int
     */
    inline int getWidth(void) const { return width_; }

    /**
     * @brief Get the Height of a case of the map
     *
     * @return int
     */
    inline int getHeight(void) const { return height_; }


    /**
     * @brief Get the colunm  of the map
     *
     * @return int
     */
    inline int getColunm(void) const { return colonne_; }

    /**
     * @brief Get the Line of the map
     *
     * @return int
     */
    inline int getLine(void) const { return ligne_; }
};

#endif