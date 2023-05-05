#ifndef GHOST_HPP
#define GHOST_HPP

#include "Character.hpp"
#include "Map.hpp"
#include "ThePacman.hpp"
#include <array>
#include <memory>

enum class Status { eyes, chase, flee, stay_jail, eaten };

class Ghost : public Character {
  protected:
    /* position pour les fantomes commençant dans la prison */
    SDL_Rect jail_position_;
    /* pour sortir de la prison */
    bool out_jail_;
    /* endroit que les fantomes visent en bougeant*/
    SDL_Rect goal_;
    /* quand en status = flee ils s'enfuit vers un des coins du jeu*/
    SDL_Rect corner_;
    /* direction actuelle du fantome */
    SDL_Scancode last_prec_key;
    /* determine la stratégie du fantome*/
    Status status_;
    /* le score augmente avec le nombre de fantome mangé */
    int eaten_score_timer_;

    std::array<SDL_Rect, 2> blue_sprite_;
    std::array<SDL_Rect, 2> white_sprite_;
    std::array<SDL_Rect, 2> eyes_sprite_;
    SDL_Rect two_hundreds_sprite_;
    SDL_Rect four_hundreds_sprite_;
    SDL_Rect eight_hundreds_sprite_;
    SDL_Rect sixteen_hundreds_sprite_;

  public:
    static clock_t timer_begin_ghost, timer_end_ghost;

    Ghost();
    static bool idle;

    inline void set_outJail(bool t_f) { out_jail_ = t_f; }

    inline void setStatus(Status stat) { status_ = stat; }
    inline Status getStatus() { return status_; }

    /* gère l'animation des fantomes celon le mode dans lequel il est*/
    void dontStopMoving(int animation, std::vector<std::vector<Tile>> &map, SDL_Rect bg);

    void move(const Uint8 *keys, int animation, std::unique_ptr<Map> &map, SDL_Rect bg);

    /* stratégie pour pousuivre pacman */
    virtual void chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) = 0;

    /* est bien placé à une intersection */
    bool intersection(int tailleCaseX, int tailleCaseY, std::vector<Tile> directions);

    /* change key_prec selon la meilleur direction celon si on veut aller au Goal ou s'éloigné de Goal */
    void choosePath(SDL_Rect Goal, std::vector<Tile> directions, float min_init);
};

#endif