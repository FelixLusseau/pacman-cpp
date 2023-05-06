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

    bool wasNotIdle;

    std::array<SDL_Rect, 2> blue_sprite_;
    std::array<SDL_Rect, 2> white_sprite_;
    std::array<SDL_Rect, 4> eyes_sprite_;
    SDL_Rect two_hundreds_sprite_;
    SDL_Rect four_hundreds_sprite_;
    SDL_Rect eight_hundreds_sprite_;
    SDL_Rect sixteen_hundreds_sprite_;

  public:
    static clock_t timer_begin_ghost, timer_end_ghost;

    Ghost();
    static bool idle;

    inline void set_outJail(const bool t_f) { out_jail_ = t_f; }

    /**
     * @brief Set the status of the ghost
     *
     * @param stat
     */
    inline void setStatus(const Status stat) { status_ = stat; }

    /**
     * @brief Get the status of the ghost
     *
     * @return Status
     */
    inline Status getStatus() const { return status_; }

    /**
     * @brief Manage the animation of the ghost according to the mode in which it is
     *
     * @param animation
     * @param map
     * @param bg
     */
    void dontStopMoving(const int animation, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg);

    /**
     * @brief Function managing the movement of the ghost
     *
     * @param keys
     * @param animation
     * @param map
     * @param bg
     */
    void move(const Uint8 *keys, const int animation, const std::unique_ptr<Map> &map, const SDL_Rect bg);

    /**
     * @brief Strategy to follow Pacman
     *
     * @param pacman
     * @param map
     * @param bg
     */
    virtual void chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) = 0;

    /**
     * @brief Return if it is at an intersection
     *
     * @param tailleCaseX
     * @param tailleCaseY
     * @param directions
     * @return true
     * @return false
     */
    bool intersection(const int tailleCaseX, const int tailleCaseY, const std::vector<Tile> directions);

    /* change key_prec selon la meilleur direction celon si on veut aller au Goal ou s'éloigné de Goal */
    void choosePath(const SDL_Rect Goal, const std::vector<Tile> directions, float min_init);

    /**
     * @brief Change direction when in idle mode
     *
     */
    void turnAround(void);
};

#endif