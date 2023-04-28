#include "../include/Ghost.hpp"
#include "../include/Game.hpp"

bool Ghost::idle = false;
// void Ghost::setIdle(bool idle) { this->idle = idle; }

Ghost::Ghost() : Character() {
    blue_sprite_[0] = {3, 195, 16, 16};
    blue_sprite_[1] = {20, 195, 16, 16};
    white_sprite_[0] = {36, 195, 16, 16};
    white_sprite_[1] = {53, 195, 16, 16};

    eyes_sprite_[0] = {71, 195, 16, 16};
    eyes_sprite_[1] = {88, 195, 16, 16};
    eyes_sprite_[2] = {105, 195, 16, 16};
    eyes_sprite_[3] = {122, 195, 16, 16};

    two_hundreds_sprite_ = {154, 175, 15, 8};
    four_hundreds_sprite_ = {154, 184, 15, 8};
    eight_hundreds_sprite_ = {154, 193, 15, 8};
    sixteen_hundreds_sprite_ = {153, 202, 16, 8};

    jail_position_ = {0, 0, 0, 0};
    corner_ = jail_position_;
    goal_ = {jail_position_.x, jail_position_.y, jail_position_.w, jail_position_.h};

    out_jail_ = false;
    status_ = Status::chase;

    eaten_score_timer_ = 0;
}

void Ghost::move(int animation, Map *map, SDL_Rect bg) {

    // tailles d'une case de la carte
    int tailleCaseX{map->getWidth()};
    int tailleCaseY{map->getHeight()};

    // taille de la case du sprite
    int size{position_.w};

    // origine = centre de la case du sprite et pas son coin gauche
    int origineX{position_.x + (size / 2)};
    int origineY{position_.y + (size / 2)};

    int ligne{origineX / map->getWidth()};
    int colonne{origineY / map->getHeight()};

    std::vector<std::vector<Tile>> Map{map->getMap()};

    std::vector<Tile> directions{Map[colonne + 1][ligne], Map[colonne - 1][ligne], Map[colonne][ligne + 1], Map[colonne][ligne - 1]};

    bool inter{intersection(tailleCaseX, tailleCaseY, directions)};

    if (Map[colonne][ligne] == Tile::GhostHouse) {
        if ((status_ != Status::stay_jail) && position_.x == (10 * tailleCaseX)) {
            goal_.x = 10 * tailleCaseX;
            goal_.y = 10 * tailleCaseY;
            goal_.w = tailleCaseX;
            goal_.h = tailleCaseY;
            choosePath(goal_, directions, (float)bg.h);
        } else if (status_ != Status::stay_jail) {
            goal_.x = 10 * tailleCaseX;
            goal_.y = 12 * tailleCaseY;
            goal_.w = tailleCaseX;
            goal_.h = tailleCaseY;
            choosePath(goal_, directions, (float)bg.h);
        } else if (position_.y > (init_position_.y - tailleCaseY) && prec_key != SDL_SCANCODE_DOWN) {
            prec_key = SDL_SCANCODE_UP;
        } else {
            prec_key = SDL_SCANCODE_DOWN;
        }
    }

    // on choisit une nouvelle direction si on est a une intersection (3 directions possible) ou si on a arrêté de bouger
    else if (inter || prec_key == SDL_SCANCODE_UNKNOWN) {
        out_jail_ = true;

        if (idle) {
            goal_.x = position_.x;
            goal_.y = position_.y;
            goal_.w = position_.w;
            goal_.h = position_.h;
        } else if (status_ == Status::eyes) { // on a été mangé on retourne à sa position initiale
            if (!(sqrt(pow(float(position_.x - init_position_.x), 2) + pow(float(position_.y - init_position_.y), 2)) < 60)) {
                goal_.x = init_position_.x;
                goal_.y = init_position_.y;
                goal_.w = init_position_.w;
                goal_.h = init_position_.h;
            } else {
                status_ = Status::chase;
                // speed = 1;
            }
        }
        choosePath(goal_, directions, (float)bg.h);
    }

    dontStopMoving(animation, Map, bg);
}

void Ghost::dontStopMoving(int animation, std::vector<std::vector<Tile>> map, SDL_Rect bg) {

    SDL_Rect sp = cur_sprite_;

    int mv_x{0};
    int mv_y{0};

    if (status_ == Status::eaten) {
        switch (Game::ghosts_eaten) {
        case 1:
            cur_sprite_ = two_hundreds_sprite_;
            break;
        case 2:
            cur_sprite_ = four_hundreds_sprite_;
            break;
        case 3:
            cur_sprite_ = eight_hundreds_sprite_;
            break;
        case 4:
            cur_sprite_ = sixteen_hundreds_sprite_;
            break;
        }
        eaten_score_timer_++;
        if (eaten_score_timer_ == 8) {
            status_ = Status::eyes;
            eaten_score_timer_ = 0;
        }
    } else if (status_ == Status::eyes) {
        switch (prec_key) {
        case SDL_SCANCODE_RIGHT:
            cur_sprite_ = eyes_sprite_[0];
            mv_x = speed;
            break;
        case SDL_SCANCODE_LEFT:
            cur_sprite_ = eyes_sprite_[1];
            mv_x = -speed;
            break;
        case SDL_SCANCODE_UP:
            cur_sprite_ = eyes_sprite_[2];
            mv_y = -speed;
            break;
        case SDL_SCANCODE_DOWN:
            cur_sprite_ = eyes_sprite_[3];
            mv_y = speed;
            break;
        }
    } else {
        switch (prec_key) {
        case SDL_SCANCODE_RIGHT:
            cur_sprite_ = sprite_[0 + animation];
            mv_x = speed;
            break;
        case SDL_SCANCODE_LEFT:
            cur_sprite_ = sprite_[2 + animation];
            mv_x = -speed;
            break;
        case SDL_SCANCODE_UP:
            cur_sprite_ = sprite_[4 + animation];
            mv_y = -speed;
            break;
        case SDL_SCANCODE_DOWN:
            cur_sprite_ = sprite_[6 + animation];
            mv_y = speed;
            break;
        }
        if (idle) {
            cur_sprite_ = blue_sprite_[0 + animation];
            Game::timer_end = clock();
            if (Game::timer_end - Game::timer_begin > 1500000) {
                cur_sprite_ = white_sprite_[0 + animation];
            }
            if (Game::timer_end - Game::timer_begin > 1600000) {
                cur_sprite_ = blue_sprite_[0 + animation];
            }
            if (Game::timer_end - Game::timer_begin > 1700000) {
                cur_sprite_ = white_sprite_[0 + animation];
            }
            if (Game::timer_end - Game::timer_begin > 1800000) {
                cur_sprite_ = blue_sprite_[0 + animation];
            }
            if (Game::timer_end - Game::timer_begin > 1900000) {
                cur_sprite_ = white_sprite_[0 + animation];
            }
            if (Game::timer_end - Game::timer_begin > 2000000) {
                idle = false;
                Game::ghosts_eaten = 0;
            }
        }
    }

    this->changePosition(position_.x + mv_x, position_.y + mv_y, map, bg);
}

void Ghost::chase(int animation, ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) {
    std::cout << "ne devrait pas apparaitre" << std::endl;
}

bool Ghost::intersection(int tailleCaseX, int tailleCaseY, std::vector<Tile> directions) {

    // bien aligné sur une case => est ce qu'on est sur une intersection?
    int rondeur{2};
    int intersection{0};

    int cornerX{(position_.x + rondeur) / tailleCaseX};
    int cornerXX{(position_.x + position_.w - rondeur) / tailleCaseX};

    int cornerY{(position_.y + rondeur) / tailleCaseY};
    int cornerYY{(position_.y + position_.h - rondeur) / tailleCaseY};

    if (cornerX == cornerXX && cornerY == cornerYY) { // aligné sur une case
        for (int i{0}; i < 4; i++) {
            if (directions[i] != Tile::Wall) { // intersection
                intersection++;
            }
        }
    }

    if (intersection >= 3) {
        return true;
        std::cout << "inter " << std::endl;
    }
    return false;
}

void Ghost::choosePath(SDL_Rect Goal, std::vector<Tile> directions, float min_init) {

    // taille de la case du sprite
    int size{position_.w / 2};

    // origine = centre de la case du sprite et pas son coin gauche
    int origineX{position_.x + size};
    int origineY{position_.y + size};

    // origine = centre de la case du sprite et pas son coin gauche
    int GoalOrigineX{Goal.x + size};
    int GoalOrigineY{Goal.y + size};

    float min{min_init}; // distance min entre le goal et le ghost
    int best{5};         // meilleur direction possible

    for (int i{0}; i < 4; i++) {

        int nextX{origineX};
        int nextY{origineY};

        // on teste quelle direction est la meilleur
        if (directions[i] != Tile::Wall && ((directions[i] != Tile::GhostHouseDoor || status_ == Status::eyes) || !out_jail_)) {
            bool went_here{true};
            switch (i) {
            case 0:
                if (last_prec_key == SDL_SCANCODE_UP) {
                    went_here = false;
                }
                nextY = origineY + size * 2;
                break;
            case 1:
                if (last_prec_key == SDL_SCANCODE_DOWN) {
                    went_here = false;
                }
                nextY = origineY - size * 2;
                break;
            case 2:
                if (last_prec_key == SDL_SCANCODE_LEFT) {
                    went_here = false;
                }
                nextX = origineX + size * 2;
                break;
            case 3:
                if (last_prec_key == SDL_SCANCODE_RIGHT) {
                    went_here = false;
                }
                nextX = origineX - size * 2;
                break;
            }

            float dist{static_cast<float>(sqrt(pow(float(nextX - GoalOrigineX), 2) + pow(float(nextY - GoalOrigineY), 2)))};

            if (went_here && dist < min) {
                min = dist;
                best = i;
            }
        }
    }

    switch (best) {
    case 0:
        // std::cout<<"best:down"<<std::endl;
        prec_key = SDL_SCANCODE_DOWN;
        break;
    case 1:
        // std::cout<<"best:up"<<std::endl;
        prec_key = SDL_SCANCODE_UP;
        break;
    case 2:
        // std::cout<<"best:right"<<std::endl;
        prec_key = SDL_SCANCODE_RIGHT;
        break;
    case 3:
        // std::cout<<"best:left"<<std::endl;
        prec_key = SDL_SCANCODE_LEFT;
        break;
    }

    last_prec_key = prec_key;
}
