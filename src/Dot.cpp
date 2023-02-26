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

    float side=pac_position->w/2;
    float distance=sqrt(pow(float(position_.x)-float(pac_position->x+side),2)+pow(float(position_.y)-float(pac_position->y+side),2));

    if(distance < side){
        exist=false;
        score=point;
        std::cout<<"get eaten!, +"<<score<<std::endl;
    }

    return score;
};