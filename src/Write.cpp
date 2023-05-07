#include "../include/Write.hpp"

Write::Write() {
    dictionary_['A'] = {12, 61, 7, 7};
    dictionary_['B'] = {20, 61, 7, 7};
    dictionary_['C'] = {28, 61, 7, 7};
    dictionary_['D'] = {36, 61, 7, 7};
    dictionary_['E'] = {44, 61, 7, 7};
    dictionary_['F'] = {52, 61, 7, 7};
    dictionary_['G'] = {60, 61, 7, 7};
    dictionary_['H'] = {68, 61, 7, 7};
    dictionary_['I'] = {76, 61, 7, 7};
    dictionary_['J'] = {84, 61, 7, 7};
    dictionary_['K'] = {92, 61, 7, 7};
    dictionary_['L'] = {100, 61, 7, 7};
    dictionary_['M'] = {108, 61, 7, 7};
    dictionary_['N'] = {116, 61, 7, 7};
    dictionary_['O'] = {124, 61, 7, 7};

    dictionary_['P'] = {4, 69, 7, 7};
    dictionary_['Q'] = {12, 69, 7, 7};
    dictionary_['R'] = {20, 69, 7, 7};
    dictionary_['S'] = {28, 69, 7, 7};
    dictionary_['T'] = {36, 69, 7, 7};
    dictionary_['U'] = {44, 69, 7, 7};
    dictionary_['V'] = {52, 69, 7, 7};
    dictionary_['W'] = {60, 69, 7, 7};
    dictionary_['X'] = {68, 69, 7, 7};
    dictionary_['Y'] = {76, 69, 7, 7};
    dictionary_['Z'] = {84, 69, 7, 7};
    dictionary_['.'] = {92, 69, 7, 7};
    dictionary_['>'] = {100, 69, 7, 7};
    dictionary_[' '] = {108, 69, 7, 7};
    dictionary_['c'] = {116, 69, 7, 7};
    dictionary_['"'] = {124, 69, 7, 7};

    dictionary_['0'] = {4, 53, 7, 7};
    dictionary_['1'] = {12, 53, 7, 7};
    dictionary_['2'] = {20, 53, 7, 7};
    dictionary_['3'] = {28, 53, 7, 7};
    dictionary_['4'] = {36, 53, 7, 7};
    dictionary_['5'] = {44, 53, 7, 7};
    dictionary_['6'] = {52, 53, 7, 7};
    dictionary_['7'] = {60, 53, 7, 7};
    dictionary_['8'] = {68, 53, 7, 7};
    dictionary_['9'] = {76, 53, 7, 7};
    dictionary_['-'] = {84, 53, 7, 7};
    dictionary_['/'] = {92, 53, 7, 7};
    dictionary_['!'] = {100, 53, 7, 7};
    dictionary_['\''] = {108, 53, 7, 7};
};

void Write::drawText(SDL_Surface *plancheSprites, SDL_Surface *win_surf, SDL_Rect &pos, const std::string text) {
    // Draw each letter independantly on the screen
    for (auto e : text) {
        SDL_BlitScaled(plancheSprites, &dictionary_[e], win_surf, &pos);
        pos.x += pos.w + 4;
    }
}