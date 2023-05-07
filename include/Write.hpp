#ifndef WRITE_HPP
#define WRITE_HPP

#include <SDL2/SDL.h>
#include <map>
#include <string>

class Write {
  private:
    std::map<char, SDL_Rect> dictionary_;

  public:
    Write();
    /**
     * @brief Get the dictionary
     *
     * @return std::map<char, SDL_Rect>
     */
    inline std::map<char, SDL_Rect> getDictionary(void) const { return dictionary_; }

    /**
     * @brief Draw text given on the screen
     *
     * @param plancheSprites
     * @param win_surf
     * @param pos
     * @param text
     */
    void drawText(SDL_Surface *plancheSprites, SDL_Surface *win_surf, SDL_Rect &pos, const std::string text);
};

#endif