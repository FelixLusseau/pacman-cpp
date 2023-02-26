#include "../include/Game.hpp"
#include "../include/Dot.hpp"

Game::Game() {

    pacman = new ThePacman{};

    ghosts[0] = new Blinky{};
    ghosts[1] = new Pinky{};
    ghosts[2] = new Inky{};
    ghosts[3] = new Clyde{};

    blueghost = new BlueGhost{};
    blankghost = new BlankGhost{};
    eyes = new Eyes{};

    map = new Map{};

    score = 0;

    pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);

    plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
    src_bg = {201, 4, 166, 214}; // x,y, w,h (0,0) en haut a gauche
    src_bg_dotless = {201 + 166 + 3, 4, 166, 214};
    src_bg_white = {201 + 2 * 166 + 8, 4, 166, 214};
    src_bg = src_bg_dotless;

    bg = {0, 0, 664, 856}; // ici scale x4

    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    std::vector<std::vector<Tile>> thisMap = map->getMap();

    /* tailles cases */
    float pixelX = float(bg.w) / float(thisMap[0].size());
    float pixelY = float(bg.h) / float(thisMap.size());

    /* création de tout les points à partir de la map fournit */
    for (int i = 0; i < thisMap.size(); i++) {

        int y = (int)(float(i) * pixelY + (pixelY / 4) + 0.5);

        for (int j = 0; j < thisMap[0].size(); j++) {

            if (thisMap[i][j] == Tile::Dot) {

                int x = (int)(float(j) * pixelX + (pixelX / 4));

                std::cout << "dot: " << i << " " << j << " " << x << " " << y << std::endl;

                dots.push_back(new Dot{x, y});
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

    /* gestion des points */
    for (int i = 0; i < dots.size(); i++) {

        score += dots[i]->getEat(pacman->getPosition());

        if (dots[i]->getExist()) { // affichage
            SDL_BlitScaled(plancheSprites, dots[i]->getSprite(), win_surf, dots[i]->getPosition());
        }
    }

    // petit truc pour faire tourner le fantome
    SDL_Rect *ghost_in = nullptr;

    // choix du fantome
    Ghost *cur_ghost = ghosts[3];

    int animation = this->changeSprite();

    int x = cur_ghost->getPosition()->x;
    int y = cur_ghost->getPosition()->y;

    switch (count / 128) {
    case 0:
        ghost_in = cur_ghost->getSprite(0 + animation);
        x++;
        break;
    case 1:
        ghost_in = cur_ghost->getSprite(6 + animation);
        y++;
        break;
    case 2:
        ghost_in = cur_ghost->getSprite(2 + animation);
        x--;
        break;
    case 3:
        ghost_in = cur_ghost->getSprite(4 + animation);
        y--;
        break;
    }
    // cur_ghost->changePosition(x, y, map->getMap(), bg);
    count = (count + 1) % (512);

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites, ghost_in, win_surf, cur_ghost->getPosition());
    // affichage pacman
    SDL_BlitScaled(plancheSprites, pacman->get_currSprite(), win_surf, pacman->getPosition());

    SDL_UpdateWindowSurface(pWindow);
}

int Game::changeSprite() {
    // ici on change entre les 2 sprites sources pour une jolie animation.
    int animation = 0;

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

    pacman->die(plancheSprites, &src_bg_dotless, win_surf, &bg, pWindow);

    for (int i = 0; i < 3; i++) {

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