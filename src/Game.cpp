#include "../include/Game.hpp"
#include "../include/Dot.hpp"

clock_t Game::timer_begin = 0;
clock_t Game::timer_end = 0;

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

    map = new Map{bg};

    int pX = map->getWidth();
    int pY = map->getHeight();

    // std::cout << "map: " << pX << " " << pY << std::endl;

    pacman = new ThePacman{pX, pY};

    ghosts[0] = new Blinky{pX, pY};
    ghosts[1] = new Pinky{pX, pY};
    ghosts[2] = new Clyde{pX, pY};
    ghosts[3] = new Inky{pX, pY, ghosts[0]};

    score = {0};

    bool launched{false};

    /* création de tout les points à partir de la map fournit */
    std::vector<std::vector<Tile>> thisMap = map->getMap();

    for (int i{0}; i < thisMap.size(); i++) {

        for (int j{0}; j < thisMap[0].size(); j++) {

            if (thisMap[i][j] == Tile::Dot) {

                int y = i * pY + (pY / 4);
                int x = j * pX + (pX / 4);
                dots.push_back(new Dot{x, y, TypeDot::Simple});

                // std::cout << "dot: " << i << " " << j << " " << x << " " << y << std::endl;

            } else if (thisMap[i][j] == Tile::PowerPellet) {

                int y = i * pY + (pY / 4) - 4;
                int x = j * pX + (pX / 4) - 4;

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

    SDL_FillRect(win_surf, NULL, 0x000000);
    SDL_Rect title{3, 3, 184, 49};
    SDL_Rect titleScale{60, 20, 552, 150};
    SDL_BlitScaled(plancheSprites, &title, win_surf, &titleScale);

    bool start{false};
    SDL_SetColorKey(plancheSprites, false, 0);
    dictionary = new Write{};
    std::map<char, SDL_Rect> my_dictionary = dictionary->getDictionary();
    SDL_Rect press_pos = {110, 400, 22, 22};
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
        }
        // std::cout << "Appuyer sur une touche pour commencer" << std::endl;
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
        }

        // Gestion du clavier
        int nbk;
        const Uint8 *keys = SDL_GetKeyboardState(&nbk);

        pacman->move(keys, this->changeSprite(), map->getMap(), bg);

        for (Ghost *fantom : ghosts) {
            // std::cout << fantom->getPosition()->x << " " << fantom->getPosition()->y << std::endl;
            if (abs(pacman->getPosition()->x - fantom->getPosition()->x) < fantom->getPosition()->w &&
                abs(pacman->getPosition()->y - fantom->getPosition()->y) < fantom->getPosition()->h) {
                if (Ghost::idle) {
                    score += 200;
                    fantom->setStatus(Status::eyes);
                    // fantom->set_speed(2);
                    break;
                }
                quit = gameOver();
                if (pacman->getLives() != 0) {
                    quit = false;
                    resetPositions(ghosts, pacman, map->getMap(), bg);
                    break;
                }
                if (quit) {
                    break;
                }
            }
        }

        // AFFICHAGE
        draw();

        /* Waiting for the launch of the PacMan */
        while (!launched) {
            SDL_Event event;
            while (!launched && SDL_PollEvent(&event)) {
                int nbk;
                const Uint8 *keys = SDL_GetKeyboardState(&nbk);
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
    SDL_Quit(); // ON SORT
    return 0;
}

void Game::draw() {
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    dictionary = new Write{};
    std::map<char, SDL_Rect> my_dictionary = dictionary->getDictionary();
    SDL_Rect score_pos = {34, 870, 14, 14};
    std::string score_str = "SCORE " + std::to_string(score) + " PT" + (score > 1 ? "S" : "");
    dictionary->drawText(plancheSprites, win_surf, &score_pos, score_str);

    if (!launched) {
        SDL_Rect ready_pos = {265, 485, 20, 20};
        std::string ready_str{"READY!"};
        dictionary->drawText(plancheSprites, win_surf, &ready_pos, ready_str);
    }

    SDL_Rect lives_pos = {580, 865, 28, 28};
    SDL_Rect lives = {168, 75, 14, 14};
    SDL_BlitScaled(plancheSprites, &lives, win_surf, &lives_pos);

    if (pacman->getLives() >= 2) {
        lives_pos.x += 29;
        SDL_BlitScaled(plancheSprites, &lives, win_surf, &lives_pos);
    }
    if (pacman->getLives() == 3) {
        lives_pos.x += 29;
        SDL_BlitScaled(plancheSprites, &lives, win_surf, &lives_pos);
    }

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);

    /* gestion des points */
    for (int i{0}; i < dots.size(); i++) {

        score += dots[i]->getEat(pacman->getPosition());

        if (dots[i]->getExist()) { // affichage
            SDL_BlitScaled(plancheSprites, dots[i]->getSprite(), win_surf, dots[i]->getPosition());
        }
    }

    int animation = this->changeSprite();

    // choix du fantome
    for (Ghost *fantom : ghosts) {

        fantom->chase(animation, pacman, map->getMap(), bg);
        fantom->move(animation, map, bg);

        // affichage fantome
        SDL_BlitScaled(plancheSprites, fantom->get_currSprite(), win_surf, fantom->getPosition());
    }

    // affichage pacman
    SDL_BlitScaled(plancheSprites, pacman->get_currSprite(), win_surf, pacman->getPosition());

    SDL_UpdateWindowSurface(pWindow);

    count = (count + 1) % (512);
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
        dictionary = new Write{};
        std::map<char, SDL_Rect> my_dictionary = dictionary->getDictionary();
        SDL_Rect game_over_pos = {100, 300, 42, 42};
        std::string game_over_str{"GAME OVER !"};
        dictionary->drawText(plancheSprites, win_surf, &game_over_pos, game_over_str);

        int x_score;
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
        SDL_Rect score_pos = {x_score, 450, 16, 16};
        std::string score_str{"YOUR SCORE IS " + std::to_string(score) + " POINT" + (score > 1 ? "S" : "")};
        dictionary->drawText(plancheSprites, win_surf, &score_pos, score_str);

        SDL_Rect exit_pos = {170, 580, 12, 12};
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
                const Uint8 *keys = SDL_GetKeyboardState(&nbk);
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

void Game::resetPositions(Ghost **ghosts, ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) {
    pacman->setPosition(*(pacman->get_initPosition()));
    for (int i{0}; i < 4; i++) {
        ghosts[i]->setPosition(*(ghosts[i]->get_initPosition()));
        ghosts[i]->setStatus(Status::chase);
        ghosts[i]->set_outJail(false);
    }
    ghosts[0]->set_outJail(true); // blinky déjà dehors
}
