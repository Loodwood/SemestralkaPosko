

#ifndef PLAYERSCORE_H
#define PLAYERSCORE_H
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"

class PlayerScore
{
public:
    // pointer preto lebo chcem pracovat s obsahom kedže sa bude menit pocas hry 
    PlayerScore(Vec2 position, SDL_Renderer* renderer)
        : renderer(renderer)
    {
            // vytvorit podklad pre text, biely 
            loadMedia();
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
    
    bool loadMedia()
{
    //Loading success flag
    bool success = true;

     
    
    //Load splash image
    surface = SDL_LoadBMP( "C:/Users/marti/Desktop/SEMKAPOS/pong/Pong/score/zero.bmp" );
    if( surface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "score/one.png", SDL_GetError() );
        success = false;
    }

    return success;
}

    SDL_Renderer* renderer;
    SDL_Surface* surface{};
    SDL_Texture* texture{};
    SDL_Rect rect{};
};
#endif 

