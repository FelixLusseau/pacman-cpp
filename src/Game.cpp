#include "../include/Game.hpp"

Game::Game() {

    pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);

    plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
    src_bg = {201, 4, 166, 214}; // x,y, w,h (0,0) en haut a gauche
    bg = {0, 0, 664, 856};       // ici scale x4
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    pacman = new ThePacman{};

    ghosts[0] = new Blinky{};
    ghosts[1] = new Pinky{};
    ghosts[2] = new Inky{};
    ghosts[3] = new Clyde{};

    map=new Map{};

    blueghost = new BlueGhost{};
    blankghost = new BlankGhost{};
    eyes = new Eyes{};
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

        pacman->deplacement(keys,this->changeSprite(),map->getMap());

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

    // choix du fantome
    Ghost *cur_ghost = ghosts[3];

    int animation=this->changeSprite();

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
    //cur_ghost->changePosition(x, y, map->getMap());
    count = (count + 1) % (512);

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites, ghost_in, win_surf, cur_ghost->getPosition());
    
    SDL_BlitScaled(plancheSprites, pacman->get_currSprite(), win_surf, pacman->getPosition());

    SDL_UpdateWindowSurface(pWindow);
}

int Game::changeSprite(){
    // ici on change entre les 2 sprites sources pour une jolie animation.
    int animation = 0;

    if ((count / 4) % 2) {
        animation = 1;
    }

  return animation;  
}