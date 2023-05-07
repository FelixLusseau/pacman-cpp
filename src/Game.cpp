#include "../include/Game.hpp"
#include "../include/Dot.hpp"

clock_t Game::timer_begin = 0;
clock_t Game::timer_end = 0;
int Game::ghosts_eaten = 0;
int Game::level = 1;
bool Game::next_level = false;

Game::Game() {

    pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 680, 900, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);

    plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");

    bg = {0, 0, 672, 864}; // scale x4

    // appearence of the map
    src_bg = {201, 4, 166, 216}; // x,y, w,h (0,0) at the top left
    src_bg_dotless = {201 + 166 + 3, 4, 166, 216};
    src_bg_white = {201 + 2 * 166 + 8, 4, 166, 216};
    src_bg = src_bg_dotless;

    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    map_ = std::make_unique<Map>(bg);

    int pX{map_->getWidth()};
    int pY{map_->getHeight()};

    pacman_ = std::make_unique<ThePacman>(pX, pY);

    ghosts_[0] = std::make_shared<Blinky>(pX, pY);
    blinky_ = ghosts_[0];
    ghosts_[1] = std::make_shared<Pinky>(pX, pY);
    pinky_ = ghosts_[1];
    ghosts_[2] = std::make_shared<Clyde>(pX, pY);
    clyde_ = ghosts_[2];
    ghosts_[3] = std::make_shared<Inky>(pX, pY, blinky_);
    inky_ = ghosts_[3];

    Ghost::timer_begin_ghost = clock();

    score_ = 0;
    count_ = 0;

    launched_ = false;

    // creation of all the dots from the map
    std::vector<std::vector<Tile>> thisMap{map_->getMap()};

    for (long unsigned int i{0}; i < thisMap.size(); i++) {

        for (long unsigned int j{0}; j < thisMap[0].size(); j++) {

            if (thisMap[i][j] == Tile::Dot) {

                int y = static_cast<int>(i * pY + (pY / 4));
                int x = static_cast<int>(j * pX + (pX / 4));
                dots_.push_back(std::make_unique<Dot>(x, y, TypeDot::Simple));

            } else if (thisMap[i][j] == Tile::PowerPellet) {

                int y = static_cast<int>(i * pY + (pY / 4) - 4);
                int x = static_cast<int>(j * pX + (pX / 4) - 4);

                dots_.push_back(std::make_unique<Dot>(x, y, TypeDot::Big));
            }
        }
    }
}

int Game::start() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_FillRect(win_surf, NULL, 0x000000);
    SDL_Rect title{3, 3, 184, 49};
    SDL_Rect titleScale{60, 20, 552, 150};
    SDL_BlitScaled(plancheSprites, &title, win_surf, &titleScale);

    bool start{false};
    SDL_SetColorKey(plancheSprites, false, 0);
    dictionary_ = std::make_unique<Write>();
    std::map<char, SDL_Rect> my_dictionary = dictionary_->getDictionary();
    SDL_Rect press_pos{110, 400, 22, 22};
    std::string press_str{"PRESS S TO START !"};
    dictionary_->drawText(plancheSprites, win_surf, press_pos, press_str);

    SDL_Rect namco{27, 77, 61, 9};
    SDL_Rect namcoScale{215, 700, 244, 36};
    SDL_BlitScaled(plancheSprites, &namco, win_surf, &namcoScale);

    SDL_Rect authors{10, 850, 10, 10};
    std::string authors_str{"BY LOUISE COUTURE AND FELIX LUSSEAU"};
    dictionary_->drawText(plancheSprites, win_surf, authors, authors_str);

    SDL_UpdateWindowSurface(pWindow);
    SDL_Delay(500);

    bool quit{false};
    while (!start) {
        SDL_Event event;
        while (!start && SDL_PollEvent(&event)) {
            int nbk;
            const Uint8 *keys = SDL_GetKeyboardState(&nbk);
            if (keys[SDL_SCANCODE_S]) {
                start = true;
            }
            if (keys[SDL_SCANCODE_ESCAPE]) {
                start = true;
                quit = true;
                break;
            }
            switch (event.type) {
            case SDL_QUIT:
                start = true;
                quit = true;
                break;
            default:
                break;
            }
            SDL_Delay(16);
        }
    }

    // Main loop
    while (!quit) {
        SDL_Event event;
        while (!quit && SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
            }
            SDL_Delay(16);
        }

        // Keyboard management
        int nbk;
        const Uint8 *keys{SDL_GetKeyboardState(&nbk)};

        int animation{this->changeSprite()};

        pacman_->move(keys, animation, map_, bg);

        for (std::shared_ptr<Ghost> fantom : ghosts_) {

            if (fantom->getStatus() == Status::chase) {
                fantom->chase(pacman_, map_->getMap(), bg);
            }
            fantom->move(NULL, animation, map_, bg);

            // ghost - Pacman collision
            if (abs(pacman_->getPosition().x - fantom->getPosition().x) < fantom->getPosition().w &&
                abs(pacman_->getPosition().y - fantom->getPosition().y) < fantom->getPosition().h) {

                // ghost are not vulnerable
                if (fantom->getStatus() == Status::eyes || fantom->getStatus() == Status::eaten) {
                    break;
                }

                // vulnerable ghosts
                if (Ghost::idle && fantom->getStatus() != Status::eaten) {
                    ghosts_eaten++;
                    switch (ghosts_eaten) {
                    case 1:
                        score_ += 200;
                        break;
                    case 2:
                        score_ += 400;
                        break;
                    case 3:
                        score_ += 800;
                        break;
                    case 4:
                        score_ += 1600;
                        break;
                    }
                    fantom->setStatus(Status::eaten);
                    break;
                }

                // Pacman dies
                quit = gameOver();

                if (pacman_->getLives() != 0) {
                    quit = false;
                    resetPositions(ghosts_, pacman_);
                    break;
                }
                if (quit) {
                    break;
                }
            }
        }
        if (next_level) {
            nextLevel(ghosts_, pacman_, bg);
            next_level = false;
        }

        // Display
        draw();

        /* Waiting for the launch of the PacMan */
        while (!launched_) {
            SDL_Event event;
            while (!launched_ && SDL_PollEvent(&event)) {
                int nbk;
                const Uint8 *keys{SDL_GetKeyboardState(&nbk)};
                if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_DOWN]) {
                    launched_ = true;
                }
                switch (event.type) {
                case SDL_QUIT:
                    launched_ = true;
                    break;
                default:
                    break;
                }
            }
        }

        if (keys[SDL_SCANCODE_ESCAPE]) {
            quit = gameOver();
        }

        // Limit to 60 FPS
        SDL_Delay(16);
    }
    SDL_FreeSurface(plancheSprites);
    SDL_DestroyWindow(pWindow);
    SDL_Quit(); // Quitting SDL
    return 0;
}

void Game::draw() {
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    // Draw the score
    dictionary_ = std::make_unique<Write>();
    std::map<char, SDL_Rect> my_dictionary = dictionary_->getDictionary();
    SDL_Rect score_pos{34, 870, 14, 14};
    std::string score_str{"SCORE " + std::to_string(score_) + " PT" + (score_ > 1 ? "S" : "")};
    dictionary_->drawText(plancheSprites, win_surf, score_pos, score_str);

    // Draw "Ready" at the beginning of the game when Pacman is not launched
    if (!launched_) {
        SDL_Rect ready_pos = {265, 485, 20, 20};
        std::string ready_str{"READY!"};
        dictionary_->drawText(plancheSprites, win_surf, ready_pos, ready_str);
    }

    // Draw the lives
    SDL_Rect lives_pos{580, 865, 28, 28};
    SDL_Rect lives{168, 75, 14, 14};
    SDL_BlitScaled(plancheSprites, &lives, win_surf, &lives_pos);

    if (pacman_->getLives() >= 2) {
        lives_pos.x += 29;
        SDL_BlitScaled(plancheSprites, &lives, win_surf, &lives_pos);
    }
    if (pacman_->getLives() == 3) {
        lives_pos.x += 29;
        SDL_BlitScaled(plancheSprites, &lives, win_surf, &lives_pos);
    }

    // Draw the bonus
    if (count_ >= 2000) {
        if (count_ == 2000) {
            bonus_ = std::make_unique<Bonus>();
            bonus_->setExists(true);
        }
        SDL_Rect bonus_pos = bonus_->getPosition();
        SDL_Rect bonus_sprite = bonus_->getSprite();
        SDL_Rect bonus_sprite_points = bonus_->getSpritePoints();
        if (bonus_->getExists()) {
            SDL_BlitScaled(plancheSprites, &bonus_sprite, win_surf, &bonus_pos);
            score_ += bonus_->getEat(pacman_->getPosition());
        }
        if (bonus_->bonus_score_timer && bonus_->bonus_score_timer < 16) {
            SDL_BlitScaled(plancheSprites, &bonus_sprite_points, win_surf, &bonus_pos);
            bonus_->bonus_score_timer++;
        }
    }

    // transparent color
    SDL_SetColorKey(plancheSprites, true, 0);

    // dots_ management
    for (long unsigned int i{0}; i < dots_.size(); i++) {

        score_ += dots_[i]->getEat(pacman_->getPosition());

        if (dots_[i]->getExist()) { // draw
            SDL_BlitScaled(plancheSprites, &dots_[i]->getSprite(), win_surf, &dots_[i]->getPosition());
        }
    }
    // release of Inky and Clyde
    if (dots_[0]->nb_dot_eaten >= 30 && inky_->getStatus() == Status::stay_jail) {
        inky_->setStatus(Status::chase);
    }
    if (dots_[0]->nb_dot_eaten >= 60 && clyde_->getStatus() == Status::stay_jail) {
        clyde_->setStatus(Status::chase);
    }

    // draw the ghosts
    for (std::shared_ptr<Ghost> fantom : ghosts_) {
        SDL_BlitScaled(plancheSprites, &fantom->get_currSprite(), win_surf, &fantom->getPosition());
    }

    // draw Pacman
    SDL_BlitScaled(plancheSprites, &pacman_->get_currSprite(), win_surf, &pacman_->getPosition());

    SDL_UpdateWindowSurface(pWindow);

    count_++;
}

int Game::changeSprite() {
    // We alternate between sprites for the animation
    int animation{0};

    if ((count_ / 4) % 2) {
        animation = 1;
    }

    return animation;
}

bool Game::gameOver() {

    SDL_FillRect(win_surf, NULL, 0x000000);
    SDL_BlitScaled(plancheSprites, &src_bg_dotless, win_surf, &bg);
    SDL_UpdateWindowSurface(pWindow);
    SDL_Delay(500);

    // transparent color
    SDL_SetColorKey(plancheSprites, true, 0);

    // Pacman die animation
    pacman_->die(plancheSprites, src_bg_dotless, win_surf, bg, pWindow);

    // Map blinking
    for (int i{0}; i < 3; i++) {
        SDL_BlitScaled(plancheSprites, &src_bg_dotless, win_surf, &bg);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(500);

        SDL_BlitScaled(plancheSprites, &src_bg_white, win_surf, &bg);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(500);
    }

    SDL_Delay(500);

    // Game over screen
    if (pacman_->getLives() == 0) {
        std::cout << "GAME OVER" << std::endl;
        std::cout << "Score: " << score_ << std::endl;

        SDL_FillRect(win_surf, NULL, 0x000000);
        SDL_Rect title{3, 3, 184, 49};
        SDL_Rect titleScale{60, 20, 552, 150};
        SDL_BlitScaled(plancheSprites, &title, win_surf, &titleScale);

        bool key_pressed{false};
        SDL_SetColorKey(plancheSprites, false, 0);
        dictionary_ = std::make_unique<Write>();
        std::map<char, SDL_Rect> my_dictionary = dictionary_->getDictionary();
        SDL_Rect game_over_pos{100, 300, 42, 42};
        std::string game_over_str{"GAME OVER !"};
        dictionary_->drawText(plancheSprites, win_surf, game_over_pos, game_over_str);

        // Center the score
        int x_score = 0;
        switch (std::to_string(score_).length()) {
        case 2:
            x_score = 110;
            break;
        case 3:
            x_score = 100;
            break;
        case 4:
            x_score = 90;
            break;
        case 5:
            x_score = 80;
            break;
        }
        SDL_Rect score_pos{x_score, 450, 16, 16};
        std::string score_str{"YOUR SCORE IS " + std::to_string(score_) + " POINT" + (score_ > 1 ? "S" : "")};
        dictionary_->drawText(plancheSprites, win_surf, score_pos, score_str);

        SDL_Rect exit_pos{170, 580, 12, 12};
        std::string exit_str{"PRESS ANY KEY TO EXIT"};
        dictionary_->drawText(plancheSprites, win_surf, exit_pos, exit_str);

        SDL_Rect namco{27, 77, 61, 9};
        SDL_Rect namcoScale{215, 700, 244, 36};
        SDL_BlitScaled(plancheSprites, &namco, win_surf, &namcoScale);

        SDL_Rect authors{10, 850, 10, 10};
        std::string authors_str{"BY LOUISE COUTURE AND FELIX LUSSEAU"};
        dictionary_->drawText(plancheSprites, win_surf, authors, authors_str);

        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(500);
        while (!key_pressed) {
            SDL_Event event;
            while (!key_pressed && SDL_PollEvent(&event)) {
                int nbk;
                const Uint8 *keys{SDL_GetKeyboardState(&nbk)};
                if (keys[SDL_SCANCODE_ESCAPE]) {
                    continue;
                }
                for (int i{0}; i < nbk; i++) {
                    if (keys[i]) {
                        key_pressed = true;
                        break;
                    }
                }
                switch (event.type) {
                case SDL_QUIT:
                    key_pressed = true;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return true;
}

void Game::resetPositions(std::array<std::shared_ptr<Ghost>, 4> &ghosts_, std::unique_ptr<ThePacman> &pacman_) {
    pacman_->setPosition(pacman_->get_initPosition());
    for (int i{0}; i < 4; i++) {
        ghosts_[i]->setPosition(ghosts_[i]->get_initPosition());
        ghosts_[i]->setStatus(Status::chase);
        ghosts_[i]->set_outJail(false);
        ghosts_[i]->set_speed(1);
    }
    blinky_->set_outJail(true); // Blinky already out of jail
    launched_ = false;
    count_ = 0;
    Ghost::idle = false;
}

void Game::nextLevel(std::array<std::shared_ptr<Ghost>, 4> &ghosts, std::unique_ptr<ThePacman> &pacman, SDL_Rect bg) {
    level++;
    resetPositions(ghosts, pacman);
    for (long unsigned int i{0}; i < dots_.size(); i++) {
        dots_[i]->setExist(true);
    }
    Dot::nb_dot_eaten = 0;
    SDL_FillRect(win_surf, NULL, 0x000000);
    SDL_Delay(500);

    // transparent color
    SDL_SetColorKey(plancheSprites, true, 0);

    // Map blinking
    for (int i{0}; i < 3; i++) {
        SDL_BlitScaled(plancheSprites, &src_bg_dotless, win_surf, &bg);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(250);

        SDL_BlitScaled(plancheSprites, &src_bg_white, win_surf, &bg);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(250);
    }

    SDL_Delay(500);
    // Animation on some level transitions
    switch (level) {
    case 3:
        level2To3();
        break;
    default:
        break;
    }
}

void Game::level2To3() {
    std::array<SDL_Rect, 2> pacman_left{SDL_Rect{48, 90, 16, 16}, SDL_Rect{62, 90, 14, 16}};
    std::array<SDL_Rect, 2> blinky_left{SDL_Rect{36, 123, 16, 16}, SDL_Rect{53, 123, 16, 16}};
    int xp{700}, xb{1020};
    SDL_Rect pacman;
    SDL_Rect blinky;
    int j{0};

    for (int i{0}; i < 300; i++) {
        SDL_FillRect(win_surf, NULL, 0x000000);
        if (i % 4 == 0) {
            j = (j + 1) % 2;
        }
        pacman = {xp, 446, 58, 58};
        blinky = {xb, 450, 48, 48};
        SDL_BlitScaled(plancheSprites, &pacman_left[j], win_surf, &pacman);
        SDL_BlitScaled(plancheSprites, &blinky_left[j], win_surf, &blinky);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(20);
        xp -= 3;
        xb -= 4;
    }

    std::array<SDL_Rect, 3> big_pacman{SDL_Rect{3, 218, 31, 31}, SDL_Rect{37, 218, 31, 31}, SDL_Rect{69, 218, 31, 31}};
    std::array<SDL_Rect, 2> blue_ghost{SDL_Rect{3, 195, 16, 16}, SDL_Rect{20, 195, 16, 16}};
    SDL_Rect blue;
    xp = -750;
    xb = -100;
    int k{0};

    for (int i{0}; i < 300; i++) {
        SDL_FillRect(win_surf, NULL, 0x000000);
        if (i % 4 == 0) {
            j = (j + 1) % 3;
            k = (k + 1) % 2;
        }
        pacman = {xp, 405, 100, 100};
        blue = {xb, 450, 48, 48};
        SDL_BlitScaled(plancheSprites, &big_pacman[j], win_surf, &pacman);
        SDL_BlitScaled(plancheSprites, &blue_ghost[k], win_surf, &blue);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(20);
        xp += 5;
        xb += 3;
    }
}
