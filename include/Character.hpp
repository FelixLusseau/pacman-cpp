#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Map.hpp"
#include <SDL2/SDL.h>
#include <array>
#include <iostream>
#include <vector>

#include <ctime>
#include <memory>

class Character {
  protected:
    // sprite to move in the 4 directions (2 images per directions)
    // order: right-left-down-up
    std::array<SDL_Rect, 8> sprite_;

    // sprite currently drawn
    SDL_Rect cur_sprite_;

    // current position in the window
    SDL_Rect position_;

    // initial position in the window
    SDL_Rect init_position_;

    // precedent key pressed (pacman) / direction taken (ghosts)
    SDL_Scancode prec_key;

    // speed of the character
    int speed;

    // map data: height and width of a tile
    int height;
    int width;

  public:
    Character();
    Character(const int px, const int py);
    virtual ~Character();

   /**
   * @brief Get the Sprite object
   * 
   * @param i 
   * @return SDL_Rect& 
   */
    inline SDL_Rect &getSprite(const int i) { return sprite_[i]; };

    /**
     * @brief Get the Position object
     * 
     * @return SDL_Rect& 
     */
    inline SDL_Rect &getPosition() { return position_; };

    /**
     * @brief Set the Position object
     * 
     * @param newPosition 
     */
    inline void setPosition(SDL_Rect newPosition) { position_ = newPosition; };

    /**
     * @brief Get the current Sprite 
     * 
     * @return SDL_Rect& 
     */
    inline SDL_Rect &get_currSprite() { return cur_sprite_; };

    /**
     * @brief Get the prec_key object
     * 
     * @return SDL_Scancode 
     */
    inline SDL_Scancode get_key() const { return prec_key; };

    /**
     * @brief Set the speed object
     * 
     * @param newSpeed 
     */
    inline void set_speed(const float newSpeed) { speed = newSpeed; };

    /**
     * @brief change the position if it is allowed
     * 
     * @param x 
     * @param y 
     * @param map 
     * @param bg 
     * @return int 
     */
    int changePosition(const int x, const int y, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg);

    /**
     * @brief Get the initPosition object
     * 
     * @return SDL_Rect 
     */
    inline SDL_Rect get_initPosition() const { return init_position_; };

    /**
     * @brief virtual method for the movement of the character
     * 
     * @param keys 
     * @param animation 
     * @param map 
     * @param bg 
     */
    virtual void move(const Uint8 *keys, const int animation, const std::unique_ptr<Map> &map, const SDL_Rect bg) = 0;
};

#endif