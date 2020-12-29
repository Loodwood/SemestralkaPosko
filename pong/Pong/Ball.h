
#ifndef BALL_H
#define BALL_H

#include "Vec2.h"


//definovanoe konstant pre velkost nasej lopticky 
const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

class Ball 
{
public:
    Ball(Vec2 position)
        : position(position)
    {
        // pre to ze vsetky atributy v rect su int potrebujeme pretypovanie 
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);      
        rect.w = BALL_WIDTH;          
        rect.h = BALL_HEIGHT;
    }
      
        // vzdy sa bude volat pri vykreslovani a pohybe lopticky
    void Draw(SDL_Renderer* renderer)
    {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);   
        // metoda sluzi na vykreslenie objektu na obrazovku
        SDL_RenderFillRect(renderer,&rect);
    }
            
    // astribut pre nasu loptu kde sa nachadza         
    Vec2 position;
    // a SDL na vykreslenie tvaru nasej lopticky
    SDL_Rect rect{};
            
};

#endif /* BALL_H */