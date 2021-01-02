

#ifndef PADDLE_H
#define PADDLE_H

#include "Vec2.h"
#include <stdio.h>
#include <string>

const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 80;

using namespace std;
class Paddle
{
public:
       Paddle(Vec2 position, Vec2 velocity)
        : position(position), velocity(velocity)
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
    
    // potrebjeme zistovat stav kde je podla pohybu a posledneho snimku a casu = dt
    void Update(float dt)
    {
        // PADDLE speed
	position += velocity * dt;

        if (position.y < 0)
	{
		// Restrict to top of the screen
		position.y = 0;
	}
	else if (position.y > (720 - PADDLE_HEIGHT))
	{
                // Restrict to bottom of the screen
		position.y = 720 - PADDLE_HEIGHT;
                cout<< position.y <<endl;
	}
    }
            
    // astribut pre nasu raketku kde sa nachadza         
    Vec2 position;
    // a SDL na vykreslenie tvaru nasej rasketky
    SDL_Rect rect{};
    // idukuje nam 3 stavy pohybhore , dole, a statie, constantna rychlost  
    Vec2 velocity;
    
};
#endif 
