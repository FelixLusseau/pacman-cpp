#ifndef THEPACMAN_HPP
#define THEPACMAN_HPP

#include <iostream>
#include "../include/Character.hpp"
#include <iostream>
#include <vector>

class ThePacman : public Character{
    private:
    
    public:

    ThePacman();

    void deplacement(const Uint8 *keys, int animation, std::vector<std::vector<Tile>> map);

};

#endif