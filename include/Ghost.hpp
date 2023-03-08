#ifndef GHOST_HPP
#define GHOST_HPP

#include "Character.hpp"
#include "ThePacman.hpp"

class Ghost : public Character {
  protected:
    SDL_Rect jail_position_;
    SDL_Rect blue_sprite_[2];
    SDL_Rect white_sprite_[2];
    SDL_Rect eyes_sprite_[4];
    bool eyes;

  public:
    Ghost();
    static bool idle;

    void dontStopMoving(int animation, std::vector<std::vector<Tile>> map, SDL_Rect bg);

    void move(ThePacman *pacman, int animation, std::vector<std::vector<Tile>> map, SDL_Rect bg);

    virtual void chase(int animation, ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg);

    /* est bien placé à une intersection */
    bool intersection(float tailleCaseX, float tailleCaseY, std::vector<Tile> directions);

    /* change key_prec selon la meilleur direction celon si on veut aller au Goal ou s'éloigné de Goal */
    void choosePath(SDL_Rect *Goal, std::vector<Tile> directions, std::vector<std::vector<Tile>> map, SDL_Rect bg);

    inline void setEyes(bool eyes) { this->eyes = eyes; }

    inline bool getEyes() { return eyes; }
};

#endif