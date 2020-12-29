

#ifndef PADDLE_H
#define PADDLE_H

#include "Vec2.h"

const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 80;

class Paddle
{
public:
       Paddle(Vec2 position)
        : position(position)
    {
        // pre to ze vsetky atributy v rect su int potrebujeme pretypovanie 
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);      
        rect.w = PADDLE_WIDTH;          
        rect.h = PADDLE_HEIGHT;
    }
      
        // vzdy sa bude volat pri vykreslovani a pohybe raketky
    void Draw(SDL_Renderer* renderer)
    {
        // na pohyb nam staci len prepisovat y poziciu 
        rect.y = static_cast<int>(position.y);   
        // metoda sluzi na vykreslenie objektu na obrazovku
        SDL_RenderFillRect(renderer,&rect);
    }
            
    // astribut pre nasu raketku kde sa nachadza         
    Vec2 position;
    // a SDL na vykreslenie tvaru nasej rasketky
    SDL_Rect rect{};
    
};
#endif 
