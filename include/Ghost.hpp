#ifndef GHOST_HPP
#define GHOST_HPP

#include "Character.hpp"
#include "ThePacman.hpp"
#include "Map.hpp"
  
enum class Status{ eyes,chase,flee, stay_jail};

class Ghost : public Character {
  protected:
    SDL_Rect jail_position_;
    SDL_Rect goal_;
    SDL_Rect corner_;
    SDL_Rect blue_sprite_[2];
    SDL_Rect white_sprite_[2];
    SDL_Rect eyes_sprite_[4];
    SDL_Scancode last_prec_key;
    Status status_;
    bool out_jail;

  public:
    Ghost();
    static bool idle;

    inline void set_outJail(bool t_f){
      out_jail=t_f;
    }
    inline void setStatus(Status stat){
      status_=stat;
    }
    inline Status getStatus(void){
      return status_;
    }

    void dontStopMoving(int animation,  std::vector<std::vector<Tile>> map, SDL_Rect bg);

    void move(int animation,  Map *map, SDL_Rect bg);

    virtual void chase(int animation, ThePacman *pacman,  std::vector<std::vector<Tile>> map, SDL_Rect bg);

    /* est bien placé à une intersection */
    bool intersection(int tailleCaseX, int tailleCaseY, std::vector<Tile> directions);

    /* change key_prec selon la meilleur direction celon si on veut aller au Goal ou s'éloigné de Goal */
    void choosePath(SDL_Rect Goal,std::vector<Tile> directions, float min_init);

};

#endif