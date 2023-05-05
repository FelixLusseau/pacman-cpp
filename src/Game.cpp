#include "../include/Game.hpp"
#include "../include/Dot.hpp"

clock_t Game::timer_begin = 0;
clock_t Game::timer_end = 0;
int Game::ghosts_eaten = 0;
int Game::level = 1;
bool Game::next_level = false;

Game::Game() {

    pWindow =
        SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 680, 900, SDL_WINDOW_SHOWN); // 680 à vérifier (initialement 700)
    win_surf = SDL_GetWindowSurface(pWindow);

    plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");

    bg = {0, 0, 672, 864}; // ici scale x4

    // apparence de la carte
    src_bg = {201, 4, 168, 216}; // x,y, w,h (0,0) en haut a gauche
    src_bg_dotless = {201 + 166 + 3, 4, 168, 216};
    src_bg_white = {201 + 2 * 166 + 8, 4, 168, 216};
    src_bg = src_bg_dotless;

    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    map = std::make_unique<Map>(bg);

    int pX{map->getWidth()};
    int pY{map->getHeight()};

    // std::cout << "map: " << pX << " " << pY << std::endl;

    pacman = std::make_unique<ThePacman>(pX, pY);

    ghosts[0] = new Blinky{pX, pY};
    ghosts[1] = new Pinky{pX, pY};
    ghosts[2] = new Clyde{pX, pY};
    ghosts[3] = new Inky{pX, pY, ghosts[0]};
    Ghost::timer_begin_ghost = clock();

    score = 0;
    count = 0;

    launched = false;

    /* création de tout les points à partir de la map fournie */
    std::vector<std::vector<Tile>> thisMap = map->getMap();

    for (long unsigned int i{0}; i < thisMap.size(); i++) {

        for (long unsigned int j{0}; j < thisMap[0].size(); j++) {

            if (thisMap[i][j] == Tile::Dot) {

                int y = static_cast<int>(i * pY + (pY / 4));
                int x = static_cast<int>(j * pX + (pX / 4));
                dots.push_back(new Dot{x, y, TypeDot::Simple});

                // std::cout << "dot: " << i << " " << j << " " << x << " " << y << std::endl;

            } else if (thisMap[i][j] == Tile::PowerPellet) {

                int y = static_cast<int>(i * pY + (pY / 4) - 4);
                int x = static_cast<int>(j * pX + (pX / 4) - 4);

                dots.push_back(new Dot{x, y, TypeDot::Big});

                // std::cout << "dot: " << i << " " << j << " " << x << " " << y << std::endl;
            }
        }
    }
}

int Game::start() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError() << std::endl;
        return 1;
    }

    // Pour faciliter travail sur les animations
    /* // for (int i{0}; i < 10; i++) {
    level2To3();
    // }
    return 0; */

    SDL_FillRect(win_surf, NULL, 0x000000);
    SDL_Rect title{3, 3, 184, 49};
    SDL_Rect titleScale{60, 20, 552, 150};
    SDL_BlitScaled(plancheSprites, &title, win_surf, &titleScale);

    bool start{false};
    SDL_SetColorKey(plancheSprites, false, 0);
    dictionary = std::make_unique<Write>();
    std::map<char, SDL_Rect> my_dictionary = dictionary->getDictionary();
    SDL_Rect press_pos{110, 400, 22, 22};
    std::string press_str{"PRESS S TO START !"};
    dictionary->drawText(plancheSprites, win_surf, &press_pos, press_str);

    SDL_Rect namco{27, 77, 61, 9};
    SDL_Rect namcoScale{215, 700, 244, 36};
    SDL_BlitScaled(plancheSprites, &namco, win_surf, &namcoScale);

    SDL_Rect authors{10, 850, 10, 10};
    std::string authors_str{"BY LOUISE COUTURE AND FELIX LUSSEAU"};
    dictionary->drawText(plancheSprites, win_surf, &authors, authors_str);

    SDL_UpdateWindowSurface(pWindow);
    SDL_Delay(500);
    while (!start) {
        SDL_Event event;
        while (!start && SDL_PollEvent(&event)) {
            int nbk;
            const Uint8 *keys = SDL_GetKeyboardState(&nbk);
            if (keys[SDL_SCANCODE_S]) {
                start = true;
            }
            switch (event.type) {
            case SDL_QUIT:
                start = true;
                break;
            default:
                break;
            }
            SDL_Delay(16);
        }
    }

    // BOUCLE PRINCIPALE
    bool quit{false};
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

        // Gestion du clavier
        int nbk;
        const Uint8 *keys{SDL_GetKeyboardState(&nbk)};

        int animation{this->changeSprite()};

        pacman->move(keys, animation, map, bg);

        for (Ghost *fantom : ghosts) {

            if (fantom->getStatus() == Status::chase) {
                fantom->chase(pacman, map->getMap(), bg);
            }
            fantom->move(NULL, animation, map, bg);

            // std::cout << fantom->getPosition()->x << " " << fantom->getPosition()->y << std::endl;

            // collison fantome / pacman
            if (abs(pacman->getPosition().x - fantom->getPosition().x) < fantom->getPosition().w &&
                abs(pacman->getPosition().y - fantom->getPosition().y) < fantom->getPosition().h) {

                // fantomes non touchable
                if (fantom->getStatus() == Status::eyes || fantom->getStatus() == Status::eaten) {
                    break;
                }

                // fantome vulnérable
                if (Ghost::idle && fantom->getStatus() != Status::eaten) {
                    // std::cout << score;
                    ghosts_eaten++;
                    switch (ghosts_eaten) {
                    case 1:
                        score += 200;
                        break;
                    case 2:
                        score += 400;
                        break;
                    case 3:
                        score += 800;
                        break;
                    case 4:
                        score += 1600;
                        break;
                    }
                    // std::cout << " " << score << std::endl;
                    fantom->setStatus(Status::eaten);
                    // fantom->set_speed(2);
                    break;
                }

                // pacman meurt
                quit = gameOver();

                if (pacman->getLives() != 0) {
                    quit = false;
                    resetPositions(ghosts, pacman);
                    break;
                }
                if (quit) {
                    break;
                }
            }
        }
        if (next_level) {
            nextLevel(ghosts, pacman, bg);
            next_level = false;
        }

        // AFFICHAGE
        draw();

        /* Waiting for the launch of the PacMan */
        while (!launched) {
            SDL_Event event;
            while (!launched && SDL_PollEvent(&event)) {
                int nbk;
                const Uint8 *keys{SDL_GetKeyboardState(&nbk)};
                if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_DOWN]) {
                    launched = true;
                }
                switch (event.type) {
                case SDL_QUIT:
                    launched = true;
                    break;
                default:
                    break;
                }
            }
        }

        if (keys[SDL_SCANCODE_ESCAPE]) { // bug sur la page de fin avec ce if
            quit = gameOver();
        }

        // LIMITE A 60 FPS
        SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
    }
    SDL_FreeSurface(plancheSprites);
    SDL_DestroyWindow(pWindow);
    SDL_Quit(); // ON SORT
    return 0;
}

void Game::draw() {
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    dictionary = std::make_unique<Write>();
    std::map<char, SDL_Rect> my_dictionary = dictionary->getDictionary();
    SDL_Rect score_pos{34, 870, 14, 14};
    std::string score_str{"SCORE " + std::to_string(score) + " PT" + (score > 1 ? "S" : "")};
    dictionary->drawText(plancheSprites, win_surf, &score_pos, score_str);

    if (!launched) {
        SDL_Rect ready_pos = {265, 485, 20, 20};
        std::string ready_str{"READY!"};
        dictionary->drawText(plancheSprites, win_surf, &ready_pos, ready_str);
    }

    SDL_Rect lives_pos{580, 865, 28, 28};
    SDL_Rect lives{168, 75, 14, 14};
    SDL_BlitScaled(plancheSprites, &lives, win_surf, &lives_pos);

    if (pacman->getLives() >= 2) {
        lives_pos.x += 29;
        SDL_BlitScaled(plancheSprites, &lives, win_surf, &lives_pos);
    }
    if (pacman->getLives() == 3) {
        lives_pos.x += 29;
        SDL_BlitScaled(plancheSprites, &lives, win_surf, &lives_pos);
    }

    // score
    if (count >= 2000) {
        if (count == 2000) {
            bonus = std::make_unique<Bonus>();
            bonus->setExists(true);
        }
        SDL_Rect bonus_pos = bonus->getPosition();
        SDL_Rect bonus_sprite = bonus->getSprite();
        SDL_Rect bonus_sprite_points = bonus->getSpritePoints();
        if (bonus->getExists()) {
            SDL_BlitScaled(plancheSprites, &bonus_sprite, win_surf, &bonus_pos);
            score += bonus->getEat(pacman->getPosition());
        }
        if (bonus->bonus_score_timer && bonus->bonus_score_timer < 16) {
            SDL_BlitScaled(plancheSprites, &bonus_sprite_points, win_surf, &bonus_pos);
            bonus->bonus_score_timer++;
        }
    }

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);

    /* gestion des points */
    for (long unsigned int i{0}; i < dots.size(); i++) {

        score += dots[i]->getEat(pacman->getPosition());

        if (dots[i]->getExist()) { // affichage
            SDL_BlitScaled(plancheSprites, &dots[i]->getSprite(), win_surf, &dots[i]->getPosition());
        }
    }
    // sortie de inky et clyde
    if (dots[0]->nb_dot_eaten_ >= 30 && ghosts[3]->getStatus() == Status::stay_jail) {
        ghosts[3]->setStatus(Status::chase);
    }
    if (dots[0]->nb_dot_eaten_ >= 60 && ghosts[2]->getStatus() == Status::stay_jail) {
        ghosts[2]->setStatus(Status::chase);
    }

    // int animation{this->changeSprite()};

    // choix du fantome
    for (Ghost *fantom : ghosts) {
        // affichage fantome
        SDL_BlitScaled(plancheSprites, &fantom->get_currSprite(), win_surf, &fantom->getPosition());
    }

    // affichage pacman
    SDL_BlitScaled(plancheSprites, &pacman->get_currSprite(), win_surf, &pacman->getPosition());

    SDL_UpdateWindowSurface(pWindow);

    count++;
    // std::cout << count << std::endl;
}

int Game::changeSprite() {
    // ici on change entre les 2 sprites sources pour une jolie animation.
    int animation{0};

    if ((count / 4) % 2) {
        animation = 1;
    }

    return animation;
}

bool Game::gameOver() {

    SDL_FillRect(win_surf, NULL, 0x000000);
    SDL_BlitScaled(plancheSprites, &src_bg_dotless, win_surf, &bg);
    SDL_UpdateWindowSurface(pWindow);
    SDL_Delay(500);

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);

    pacman->die(plancheSprites, &src_bg_dotless, win_surf, &bg, pWindow);

    for (int i{0}; i < 3; i++) {

        SDL_BlitScaled(plancheSprites, &src_bg_dotless, win_surf, &bg);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(500);

        SDL_BlitScaled(plancheSprites, &src_bg_white, win_surf, &bg);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(500);
    }

    SDL_Delay(500);

    if (pacman->getLives() == 0) {
        std::cout << "GAME OVER" << std::endl;
        std::cout << "Score: " << score << std::endl;

        SDL_FillRect(win_surf, NULL, 0x000000);
        SDL_Rect title{3, 3, 184, 49};
        SDL_Rect titleScale{60, 20, 552, 150};
        SDL_BlitScaled(plancheSprites, &title, win_surf, &titleScale);

        bool key_pressed{false};
        SDL_SetColorKey(plancheSprites, false, 0);
        dictionary = std::make_unique<Write>();
        std::map<char, SDL_Rect> my_dictionary = dictionary->getDictionary();
        SDL_Rect game_over_pos{100, 300, 42, 42};
        std::string game_over_str{"GAME OVER !"};
        dictionary->drawText(plancheSprites, win_surf, &game_over_pos, game_over_str);

        int x_score = 0;
        switch (std::to_string(score).length()) {
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
        std::string score_str{"YOUR SCORE IS " + std::to_string(score) + " POINT" + (score > 1 ? "S" : "")};
        dictionary->drawText(plancheSprites, win_surf, &score_pos, score_str);

        SDL_Rect exit_pos{170, 580, 12, 12};
        std::string exit_str{"PRESS ANY KEY TO EXIT"};
        dictionary->drawText(plancheSprites, win_surf, &exit_pos, exit_str);

        SDL_Rect namco{27, 77, 61, 9};
        SDL_Rect namcoScale{215, 700, 244, 36};
        SDL_BlitScaled(plancheSprites, &namco, win_surf, &namcoScale);

        SDL_Rect authors{10, 850, 10, 10};
        std::string authors_str{"BY LOUISE COUTURE AND FELIX LUSSEAU"};
        dictionary->drawText(plancheSprites, win_surf, &authors, authors_str);

        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(500);
        while (!key_pressed) {
            SDL_Event event;
            while (!key_pressed && SDL_PollEvent(&event)) {
                int nbk;
                const Uint8 *keys{SDL_GetKeyboardState(&nbk)};
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

void Game::resetPositions(Ghost **ghosts, std::unique_ptr<ThePacman> &pacman) {
    pacman->setPosition(pacman->get_initPosition());
    for (int i{0}; i < 4; i++) {
        ghosts[i]->setPosition(ghosts[i]->get_initPosition());
        ghosts[i]->setStatus(Status::chase);
        ghosts[i]->set_outJail(false);
        ghosts[i]->set_speed(1);
    }
    ghosts[0]->set_outJail(true); // blinky déjà dehors
    launched = false;
    count = 0;
}

void Game::nextLevel(Ghost **ghosts, std::unique_ptr<ThePacman> &pacman, SDL_Rect bg) {
    level++;
    resetPositions(ghosts, pacman);
    for (long unsigned int i{0}; i < dots.size(); i++) {
        dots[i]->setExist(true);
    }
    Dot::nb_dot_eaten_ = 0;
    SDL_FillRect(win_surf, NULL, 0x000000);
    SDL_Delay(500);

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);

    for (int i{0}; i < 3; i++) {

        SDL_BlitScaled(plancheSprites, &src_bg_dotless, win_surf, &bg);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(250);

        SDL_BlitScaled(plancheSprites, &src_bg_white, win_surf, &bg);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(250);
    }

    SDL_Delay(500);
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