#ifndef DOT_HPP
#define DOT_HPP

#include <SDL.h>
#include <iostream>
#include <vector>

enum class TypeDot { Simple, Big /* , Fruit */ };

class Dot {
  private:
    TypeDot type;

    /* combien de points il vaut */
    int point_;
    bool exist_;

    SDL_Rect sprite_;

    /* position dans la fenètre de jeu */
    SDL_Rect position_;

  public:
    static int nb_dot_tot_, nb_dot_eaten_;

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
    inline int getPoint(void) const { return point_; }
    /**
     * @brief Set the Exist object
     * 
     * @param exist 
     */
    inline void setExist(const bool exist) { exist_ = exist; }

    /* fonction pour manger les points: renvoit 0 si pas mangé, son nombre de point sinon */
    int getEat(const SDL_Rect &pac_position);
};

#endif