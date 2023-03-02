#include "../include/Write.hpp"

Write::Write() {
    dictionary['A'] = {12, 61, 7, 7};
    dictionary['B'] = {20, 61, 7, 7};
    dictionary['C'] = {28, 61, 7, 7};
    dictionary['D'] = {36, 61, 7, 7};
    dictionary['E'] = {44, 61, 7, 7};
    dictionary['F'] = {52, 61, 7, 7};
    dictionary['G'] = {60, 61, 7, 7};
    dictionary['H'] = {68, 61, 7, 7};
    dictionary['I'] = {76, 61, 7, 7};
    dictionary['J'] = {84, 61, 7, 7};
    dictionary['K'] = {92, 61, 7, 7};
    dictionary['L'] = {100, 61, 7, 7};
    dictionary['M'] = {108, 61, 7, 7};
    dictionary['N'] = {116, 61, 7, 7};
    dictionary['O'] = {124, 61, 7, 7};

    dictionary['P'] = {4, 69, 7, 7};
    dictionary['Q'] = {12, 69, 7, 7};
    dictionary['R'] = {20, 69, 7, 7};
    dictionary['S'] = {28, 69, 7, 7};
    dictionary['T'] = {36, 69, 7, 7};
    dictionary['U'] = {44, 69, 7, 7};
    dictionary['V'] = {52, 69, 7, 7};
    dictionary['W'] = {60, 69, 7, 7};
    dictionary['X'] = {68, 69, 7, 7};
    dictionary['Y'] = {76, 69, 7, 7};
    dictionary['Z'] = {84, 69, 7, 7};
    dictionary['.'] = {92, 69, 7, 7};
    dictionary['>'] = {100, 69, 7, 7};
    dictionary[' '] = {108, 69, 7, 7};
    dictionary['c'] = {116, 69, 7, 7};
    dictionary['"'] = {124, 69, 7, 7};

    dictionary['0'] = {4, 53, 7, 7};
    dictionary['1'] = {12, 53, 7, 7};
    dictionary['2'] = {20, 53, 7, 7};
    dictionary['3'] = {28, 53, 7, 7};
    dictionary['4'] = {36, 53, 7, 7};
    dictionary['5'] = {44, 53, 7, 7};
    dictionary['6'] = {52, 53, 7, 7};
    dictionary['7'] = {60, 53, 7, 7};
    dictionary['8'] = {68, 53, 7, 7};
    dictionary['9'] = {76, 53, 7, 7};
    dictionary['-'] = {84, 53, 7, 7};
    dictionary['/'] = {92, 53, 7, 7};
    dictionary['!'] = {100, 53, 7, 7};
    dictionary['\''] = {108, 53, 7, 7};
};

// SDL_Rect Write::get(char c) { return dictionary[c]; }
void Write::drawText(SDL_Surface *plancheSprites, SDL_Surface *win_surf, SDL_Rect *pos, std::string text) {
    for (auto e : text) {

        SDL_BlitScaled(plancheSprites, &dictionary[e], win_surf, pos);
        pos->x += 18;
    }
}