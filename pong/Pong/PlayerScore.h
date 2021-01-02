

#ifndef PLAYERSCORE_H
#define PLAYERSCORE_H
#include <stdio.h>
#include "SDL_ttf.h"

class PlayerScore
{
public:
    // pointer preto lebo chcem pracovat s obsahom kedže sa bude menit pocas hry 
    PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font)
        : renderer(renderer), font(font)
    {
            // vytvorit podklad pre text, biely 
            surface = TTF_RenderText_Solid(font,"0",{0xFF,0xFF,0xFF,0xFF});
            // to ca sa bude vykreslovat 
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            
            int width, height;
            SDL_QueryTexture(texture, NULL, NULL, &width, &height);
            
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);      
        rect.w = width;          
        rect.h = height;
    }

    ~PlayerScore()
    {
        
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
    
    void Draw()
    {
       SDL_RenderCopy(renderer, texture,NULL,&rect);
    }

    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Surface* surface{};
    SDL_Texture* texture{};
    SDL_Rect rect{};
};
#endif 

