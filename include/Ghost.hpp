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
    SDL_Rect jail_position_;    // position for the ghosts starting into the jail
    bool out_jail_;             // true if the ghost can leave the jail
    SDL_Rect goal_;             // goal of the ghost when moving
    SDL_Rect corner_;           // corner of the ghost when fleeing
    SDL_Scancode last_prec_key; // current direction of the ghost
    Status status_;             // strategy of the ghost
    int eaten_score_timer_;     // timer for the score when eating a ghost

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

    /**
     * @brief Set the outJail bool
     * 
     * @param t_f 
     */
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

    /**
     * @brief Choose the best direction to go to the goal or to move away from it by modifying the prec_key
     *
     * @param Goal
     * @param directions
     * @param min_init
     */
    void choosePath(const SDL_Rect Goal, const std::vector<Tile> directions, float min_init);

    /**
     * @brief Change direction when in idle mode
     *
     */
    void turnAround(void);
};

#endif