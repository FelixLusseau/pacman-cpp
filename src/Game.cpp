#include "../include/Game.hpp"
#include "../include/Dot.hpp"

clock_t Game::timer_begin = 0;
clock_t Game::timer_end = 0;

Game::Game() {

    pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);

    plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");

    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    // apparence de la carte
    src_bg = {201, 4, 166, 214}; // x,y, w,h (0,0) en haut a gauche
    src_bg_dotless = {201 + 166 + 3, 4, 166, 214};
    src_bg_white = {201 + 2 * 166 + 8, 4, 166, 214};
    src_bg = src_bg_dotless;

    bg = {0, 0, 664, 856}; // ici scale x4

    map = new Map{};
    std::vector<std::vector<Tile>> thisMap = map->getMap();

    /* tailles cases */
    float pixelX = float(bg.w) / float(thisMap[0].size());
    float pixelY = float(bg.h) / float(thisMap.size());

    pacman = new ThePacman{10 * (int)(pixelX) + 8, 20 * (int)(pixelY) + 18};

    ghosts[0] = new Blinky{(int)pixelX, (int)pixelY};
    ghosts[1] = new Pinky{(int)pixelX, (int)pixelY};
    ghosts[2] = new Inky{};
    ghosts[3] = new Clyde{};

    score = {0};

    /* création de tout les points à partir de la map fournit */
    for (int i{0}; i < thisMap.size(); i++) {

        for (int j{0}; j < thisMap[0].size(); j++) {

            if (thisMap[i][j] == Tile::Dot) {

                int y = (int)(float(i) * pixelY + (pixelY / 4) + 0.5);
                int x = (int)(float(j) * pixelX + (pixelX / 4));
                dots.push_back(new Dot{x, y, TypeDot::Simple});

                // std::cout << "dot: " << i << " " << j << " " << x << " " << y << std::endl;

            } else if (thisMap[i][j] == Tile::PowerPellet) {

                int y = (int)(float(i) * pixelY + (pixelY / 8) + 0.5);
                int x = (int)(float(j) * pixelX + (pixelX / 8));

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

    // BOUCLE PRINCIPALE
    bool quit = false;
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
                    fantom->setEyes(true);
                    fantom->set_speed(4);
                    break;
                }
                quit = gameOver();
                if (quit) {
                    break;
                }
            }
        }

        // AFFICHAGE
        draw();

        if (keys[SDL_SCANCODE_ESCAPE]) {
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
    SDL_Rect score_pos = {34, 860, 14, 14};
    std::string score_str = "SCORE " + std::to_string(score) + " PTS";
    dictionary->drawText(plancheSprites, win_surf, &score_pos, score_str);

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
    for (int i{0}; i < 4; i++) {

        Ghost *cur_ghost = ghosts[i];

        cur_ghost->chase(animation,pacman, map->getMap(), bg);

        // affichage fantome
        SDL_BlitScaled(plancheSprites, cur_ghost->get_currSprite(), win_surf, cur_ghost->getPosition());
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

    std::cout << "GAME OVER" << std::endl;
    std::cout << "score: " << score << std::endl;

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

    return true;
}