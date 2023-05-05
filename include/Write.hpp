#ifndef WRITE_HPP
#define WRITE_HPP

#include <SDL2/SDL.h>
#include <map>
#include <string>

class Write {
  private:
    std::map<char, SDL_Rect> dictionary;

  public:
    Write();
    inline std::map<char, SDL_Rect> getDictionary(void) const { return dictionary; }
    void drawText(SDL_Surface *plancheSprites, SDL_Surface *win_surf, SDL_Rect *pos, const std::string text);
};

#endif