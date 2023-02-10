
#include "thePacman.hpp"

thePacman::thePacman(){
    sprite_r[0]= {18, 90, 16, 16};
    sprite_r[1]= {34, 90, 14, 16};

    sprite_l[0]= {48, 90, 16, 16};
    sprite_l[1]= {64, 90, 12, 16};

    sprite_u[0]= {76, 90, 16, 16};
    sprite_u[1]= {92, 90, 16, 16};

    sprite_d[0]= {108, 90, 16, 16};
    sprite_d[1]= {124, 90, 20, 16};


    position = {34, 34, 32, 32};
}