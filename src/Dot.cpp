#include "../include/Dot.hpp"

Dot::Dot(int x, int y){

    point =100;
    exist=true;

    sprite_={3,80,4,4};
    position_={x,y,16,16};
};

int Dot::getEat(SDL_Rect*pac_position){

    if(!exist){
        return 0;
    }

    int score=0;

    float side=(float(pac_position->w)/2);

    float origineX= float(pac_position->x)+float(pac_position->w)/2;
    float origineY= float(pac_position->y)+float(pac_position->w)/2;

    //float distance=sqrt( pow(float(position_.x)-origineX,2) + pow(float(position_.y)-origineY,2) );

    if( abs(origineX-position_.x)<side && abs(origineY-position_.y)<side ){
        exist=false;
        score=point;
        std::cout<<"get eaten!, +"<<score<<" x:"<<position_.x<<" y:"<<position_.y<<std::endl;
        std::cout<<"pacman x:"<<origineX<<" y:"<<origineY<<std::endl;
    }

    return score;
};