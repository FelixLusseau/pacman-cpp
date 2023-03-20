#include "../include/Map.hpp"

Map::Map(SDL_Rect bg) {
    map = {
        //1
        {Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
        Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall},
        //2
        {Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Wall,
         Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Wall},
        //3
        {Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot, Tile::Wall,
         Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall},
        //4
        {Tile::Wall, Tile::PowerPellet, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,         Tile::Wall,
         Tile::Wall, Tile::Wall,        Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall,        Tile::Wall,
         Tile::Wall, Tile::Dot,         Tile::Wall, Tile::Wall, Tile::Wall, Tile::PowerPellet, Tile::Wall},
        //5
        {Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot, Tile::Wall,
         Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall},
        //6
        {Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot,
         Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Wall},
        //7
        {Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall,
         Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall},
        //8
        {Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall,
         Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall},
        //9
        {Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Wall,
         Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Wall},
        //10
        {Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Empty, Tile::Wall,
         Tile::Empty, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall},
        //11
        {Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Empty, Tile::Empty, Tile::Empty, Tile::Empty,
         Tile::Empty, Tile::Empty, Tile::Empty, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall,  Tile::Wall},
        //12
        {Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall,           Tile::Wall, Tile::Dot,  Tile::Wall,
         Tile::Empty, Tile::Wall, Tile::Wall, Tile::GhostHouseDoor, Tile::Wall, Tile::Wall, Tile::Empty,
         Tile::Wall,  Tile::Dot,  Tile::Wall, Tile::Wall,           Tile::Wall, Tile::Wall, Tile::Wall},
        //13
        {Tile::Wall,  Tile::Wall, Tile::Wall,       Tile::Wall,       Tile::Wall,       Tile::Dot,  Tile::Wall,
         Tile::Empty, Tile::Wall, Tile::GhostHouse, Tile::GhostHouse, Tile::GhostHouse, Tile::Wall, Tile::Empty,
         Tile::Wall,  Tile::Dot,  Tile::Wall,       Tile::Wall,       Tile::Wall,       Tile::Wall, Tile::Wall},
        //14
        {Tile::EscapeTunnel, Tile::Empty, Tile::Empty,      Tile::Empty,      Tile::Empty,      Tile::Dot,   Tile::Empty,
         Tile::Empty,        Tile::Wall,  Tile::GhostHouse, Tile::GhostHouse, Tile::GhostHouse, Tile::Wall,  Tile::Empty,
         Tile::Empty,        Tile::Dot,   Tile::Empty,      Tile::Empty,      Tile::Empty,      Tile::Empty, Tile::EscapeTunnel},
        //15
        {Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Empty, Tile::Wall, Tile::Wall, Tile::Wall,
         Tile::Wall, Tile::Wall, Tile::Empty, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall},
        //16
        {Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Empty, Tile::Empty, Tile::Empty, Tile::Empty,
         Tile::Empty, Tile::Empty, Tile::Empty, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall,  Tile::Wall},
        //17
        {Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Empty, Tile::Wall, Tile::Wall, Tile::Wall,
         Tile::Wall, Tile::Wall, Tile::Empty, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall},
        //18
        {Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Empty, Tile::Wall, Tile::Wall, Tile::Wall,
         Tile::Wall, Tile::Wall, Tile::Empty, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall},
        //19
        {Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Wall,
         Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Wall},
        //20
        {Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot, Tile::Wall,
         Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall},
        //21
        {Tile::Wall, Tile::PowerPellet, Tile::Dot, Tile::Dot, Tile::Wall, Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Dot,         Tile::Dot, Tile::Empty,
         Tile::Dot,  Tile::Dot,         Tile::Dot, Tile::Dot, Tile::Dot,  Tile::Wall, Tile::Dot, Tile::Dot, Tile::PowerPellet, Tile::Wall},
        //22
        {Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall,
         Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall},
        //23
        {Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall,
         Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall},
        //24
        {Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Wall,
         Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Wall},
        //25
        {Tile::Wall, Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot, Tile::Wall,
         Tile::Dot,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Dot,  Tile::Wall},
        //26
        {Tile::Wall, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot,
         Tile::Dot,  Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Dot, Tile::Wall},
        //27
        {Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
         Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall}
    };

    /* tailles cases */
    float pixelX = float(bg.w) / float(map[0].size());
    float pixelY = float(bg.h) / float(map.size());

    width_=static_cast<int>(pixelX);
    height_=static_cast<int>(pixelY);

    ligne_=map.size();
    colonne_=map[0].size();
    
    std::cout<<"ligne: "<<ligne_<<" colonne: "<<colonne_<<std::endl;
};

