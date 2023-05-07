#ifndef DOT_HPP
#define DOT_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

enum class TypeDot { Simple, Big };

class Dot {
  private:
    TypeDot type;
    int points; // number of points
    bool exist_;
    SDL_Rect sprite_;   // sprite of the dot
    SDL_Rect position_; // position in the game window

  public:
    static int nb_dot_tot_, nb_dot_eaten_; // counters of dots for the release of the ghosts and the level change

    Dot(const int x, const int y, const TypeDot type);

    /**
     * @brief Get the Exist object
     * 
     * @return true 
     * @return false 
     */
    bool inline getExist(void) const { return exist_; }
    /**
     * @brief Get the Position object
     * 
     * @return SDL_Rect& 
     */
    inline SDL_Rect &getPosition(void) { return position_; }
    /**
     * @brief Get the Sprite object
     * 
     * @return SDL_Rect& 
     */
    inline SDL_Rect &getSprite(void) { return sprite_; }
    /**
     * @brief Get the number of Point (score) the dot is 
     * 
     * @return int 
     */
    inline int getPoint(void) const { return points; }
    /**
     * @brief Set the Exist object
     * 
     * @param exist 
     */
    inline void setExist(const bool exist) { exist_ = exist; }

    /**
     * @brief Function to eat the points: return 0 if not eaten, its number of points otherwise
     *
     * @param pac_position
     * @return int
     */
    int getEat(const SDL_Rect &pac_position);
};

#endif