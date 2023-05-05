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
    int point;
    bool exist_;

    SDL_Rect sprite_;

    /* position dans la fenètre de jeu */
    SDL_Rect position_;

  public:
    static int nb_dot_tot_, nb_dot_eaten_;

    Dot(int x, int y, TypeDot type);

    bool inline getExist(void) const { return exist_; }
    inline SDL_Rect &getPosition(void) { return position_; }
    inline SDL_Rect &getSprite(void) { return sprite_; }
    inline int getPoint(void) const { return point; }
    inline void setExist(bool exist) { exist_ = exist; }

    /* fonction pour manger les points: renvoit 0 si pas mangé, son nombre de point sinon */
    int getEat(const SDL_Rect &pac_position);
};

#endif