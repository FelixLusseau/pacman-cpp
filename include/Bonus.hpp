#ifndef BONUS_HPP
#define BONUS_HPP

#include <SDL2/SDL.h>

enum class TypeBonus { Cherry, Strawberry, Orange, Apple, Melon, Galaxian, Bell, Key };

class Bonus {
  private:
    TypeBonus type_;
    int points_;
    bool exist_;
    SDL_Rect sprite_;
    SDL_Rect sprite_points_;
    SDL_Rect position_;
    SDL_Rect hundred_sprite_, three_hundreds_sprite_, five_hundreds_sprite_, seven_hundreds_sprite_, one_thousand_sprite_, two_thousands_sprite_,
        three_thousands_sprite_, five_thousands_sprite_;
    SDL_Rect cherry_sprite_, strawberry_sprite_, orange_sprite_, apple_sprite_, melon_sprite_, galaxian_sprite_, bell_sprite_, key_sprite_;

  public:
    Bonus();
    int bonus_score_timer;

    /**
     * @brief Get the sprite of bonuses
     *
     * @return SDL_Rect
     */
    inline SDL_Rect getSprite() const { return sprite_; }

    /**
     * @brief Get the position of the bonus
     *
     * @return SDL_Rect
     */
    inline SDL_Rect getPosition() const { return position_; }

    /**
     * @brief Get the points of the bonus
     *
     * @return SDL_Rect
     */
    inline SDL_Rect getSpritePoints() const { return sprite_points_; }

    /**
     * @brief Get if the bonus exists and has to appear
     *
     * @return true
     * @return false
     */
    inline bool getExists() const { return exist_; }

    /**
     * @brief Set if the bonus exists and has to appear
     *
     * @param b
     */
    inline void setExists(const bool b) { exist_ = b; }

    /**
     * @brief Check if Pacman is on the bonus
     *
     * @param pac_position
     * @return int
     */
    int getEat(const SDL_Rect &pac_position);
};

#endif