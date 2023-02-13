#include "../include/Game.hpp"

Game::Game() {

    pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);

    plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
    src_bg = {200, 3, 168, 216}; // x,y, w,h (0,0) en haut a gauche
    bg = {4, 4, 672, 864};       // ici scale x4
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    pacman = new ThePacman{};

    for (int i = 0; i < 4; i++) {
        ghosts[i] = new Blinky();
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

        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;
        if (keys[SDL_SCANCODE_LEFT]) {
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
        }
        if (keys[SDL_SCANCODE_UP]) {
        }
        if (keys[SDL_SCANCODE_DOWN]) {
        }

        // AFFICHAGE
        draw();
        // LIMITE A 60 FPS
        SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
    }
    SDL_Quit(); // ON SORT
    return 0;
}

void Game::draw() {

    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    // petit truc pour faire tourner le fantome
    SDL_Rect *ghost_in = nullptr;

    // ici on change entre les 2 sprites sources pour une jolie animation.
    int animation = 0;
    if ((count / 4) % 2) {
        animation = 1;
    }
    int x = ghosts[0]->getPosition()->x;
    int y = ghosts[0]->getPosition()->y;

    switch (count / 128) {
    case 0:
        ghost_in = ghosts[0]->getSprite(0 + animation);
        x++;
        break;
    case 1:
        ghost_in = ghosts[0]->getSprite(6 + animation);
        y++;
        break;
    case 2:
        ghost_in = ghosts[0]->getSprite(2 + animation);
        x--;
        ghosts[0]->changePosition(x, y);
        break;
    case 3:
        ghost_in = ghosts[0]->getSprite(4 + animation);
        y--;
        break;
    }
    ghosts[0]->changePosition(x, y);
    count = (count + 1) % (512);

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites, ghost_in, win_surf, ghosts[0]->getPosition());

    SDL_UpdateWindowSurface(pWindow);
}