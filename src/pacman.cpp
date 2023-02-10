#include "ghosts.hpp"
#include "thePacman.hpp"

#include <SDL.h>
#include <iostream>

SDL_Window *pWindow = nullptr;
SDL_Surface *win_surf = nullptr;
SDL_Surface *plancheSprites = nullptr;

SDL_Rect src_bg = {200, 3, 168, 216}; // x,y, w,h (0,0) en haut a gauche
SDL_Rect bg = {4, 4, 672, 864};       // ici scale x4

SDL_Rect red_ghost_r = {3, 123, 16, 16};
SDL_Rect red_ghost_l = {37, 123, 16, 16};
SDL_Rect red_ghost_d = {105, 123, 16, 16};
SDL_Rect red_ghost_u = {71, 123, 16, 16};
SDL_Rect ghost = {34, 34, 32, 32}; // ici scale x2
SDL_Rect pacman = {34, 34, 32, 32}; // ici scale x2

SDL_Rect pink_ghost_r = {3, 141, 16, 16};
SDL_Rect pink_ghost_l = {37, 141, 16, 16};
SDL_Rect pink_ghost_d = {105, 141, 16, 16};
SDL_Rect pink_ghost_u = {71, 141, 16, 16};

SDL_Rect cyan_ghost_r = {3, 159, 16, 16};
SDL_Rect cyan_ghost_l = {37, 159, 16, 16};
SDL_Rect cyan_ghost_d = {105, 159, 16, 16};
SDL_Rect cyan_ghost_u = {71, 159, 16, 16};

SDL_Rect orange_ghost_r = {3, 177, 16, 16};
SDL_Rect orange_ghost_l = {37, 177, 16, 16};
SDL_Rect orange_ghost_d = {105, 177, 16, 16};
SDL_Rect orange_ghost_u = {71, 177, 16, 16};

SDL_Rect idle_ghost = {3, 195, 16, 16};
SDL_Rect reappearing_ghost = {37, 195, 16, 16};

SDL_Rect eyes_l = {88, 195, 16, 16};
SDL_Rect eyes_u = {105, 195, 16, 16};
SDL_Rect eyes_d = {122, 195, 16, 16};
SDL_Rect eyes_r = {71, 195, 16, 16};

int count;

void init() {
    pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);

    plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
    count = 0;
}

// fonction qui met à jour la surface de la fenetre "win_surf"
void draw(SDL_Rect *pac_move) {
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    // petit truc pour faire tourner le fantome
    SDL_Rect *ghost_in = nullptr;
    switch (count / 128) {
    case 0:
        ghost_in = &(cyan_ghost_r);
        ghost.x++;
        break;
    case 1:
        ghost_in = &(cyan_ghost_d);
        ghost.y++;
        break;
    case 2:
        ghost_in = &(cyan_ghost_l);
        ghost.x--;
        break;
    case 3:
        ghost_in = &(cyan_ghost_u);
        ghost.y--;
        break;
    }
    count = (count + 1) % (512);

    // ici on change entre les 2 sprites sources pour une jolie animation.
    SDL_Rect ghost_in2 = *ghost_in;
    if ((count / 4) % 2)
        ghost_in2.x += 17;

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &ghost);
    SDL_BlitScaled(plancheSprites, pac_move, win_surf, &pacman);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError() << std::endl;
        return 1;
    }

    //
    thePacman *pac=new thePacman{};
    int animation=0;
    SDL_Rect *pac_move=pac->getLeft(0);

    init();
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
        
        if ((count ) % 2)
            animation = (animation+1)%2;

        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;
        if (keys[SDL_SCANCODE_LEFT]){
            pac_move=pac->getLeft(animation);
        }
        if (keys[SDL_SCANCODE_RIGHT]){
            pac_move=pac->getRight(animation);
        }
        if (keys[SDL_SCANCODE_UP]){
            pac_move=pac->getUp(animation);
        }
        if (keys[SDL_SCANCODE_DOWN]){
            pac_move=pac->getDown(animation);
        }

        // AFFICHAGE
        draw(pac_move);
        SDL_UpdateWindowSurface(pWindow);
        // LIMITE A 60 FPS
        SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
    }
    SDL_Quit(); // ON SORT
    delete(pac);
    return 0;
}
