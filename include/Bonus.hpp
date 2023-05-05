#ifndef BONUS_HPP
#define BONUS_HPP

#include <SDL.h>

enum class TypeBonus { Cherry, Strawberry, Orange, Apple, Melon, Galaxian, Bell, Key };

class Bonus {
  private:
    TypeBonus type;
    int points;
    bool exist;
    SDL_Rect sprite_;
    SDL_Rect sprite_points_;
    SDL_Rect position_;
    SDL_Rect hundred_sprite_;
    SDL_Rect three_hundreds_sprite_;
    SDL_Rect five_hundreds_sprite_;
    SDL_Rect seven_hundreds_sprite_;
    SDL_Rect one_thousand_sprite_;
    SDL_Rect two_thousands_sprite_;
    SDL_Rect three_thousands_sprite_;
    SDL_Rect five_thousands_sprite_;

    SDL_Rect cherry_sprite_;
    SDL_Rect strawberry_sprite_;
    SDL_Rect orange_sprite_;
    SDL_Rect apple_sprite_;
    SDL_Rect melon_sprite_;
    SDL_Rect galaxian_sprite_;
    SDL_Rect bell_sprite_;
    SDL_Rect key_sprite_;

  public:
    Bonus();
    int bonus_score_timer;
    inline SDL_Rect getSprite() const { return sprite_; }
    inline SDL_Rect getPosition() const { return position_; }
    inline SDL_Rect getSpritePoints() const { return sprite_points_; }
    inline bool getExists() const { return exist; }
    inline void setExists(bool e) { exist = e; }
    int getEat(const SDL_Rect &pac_position);
};

#endif