/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: marti
 *
 * Created on Pondelok, 2020, decembra 28, 14:23
 */
#define SDL_MAIN_HANDLED
#include <cstdlib>
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"             // pre nas text 
#include "Vec2.h"
#include "Ball.h"
#include "Paddle.h"

using namespace std;

/*
 * 
 */
// konstasnty pre nase hracie okno 
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main(int argc, char** argv) {
    
    
	// Initialize SDL components
	SDL_Init(SDL_INIT_VIDEO);
        // pre zobrazenie textu 
        TTF_Init();

        // vytvorit okno kde chceme vykreslovat hru 
	SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        
        //vytvor lopticku  
        Ball ball(
            Vec2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f),
            (WINDOW_HEIGHT / 2.0f) - (BALL_HEIGHT / 2.0f)));
        
        // Create the paddles
        Paddle paddleOne(
	Vec2(50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)));

        Paddle paddleTwo(
	Vec2(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)));

	// Herna logika 
	{
		bool running = true;

		// Continue looping and processing events until user exits
		while (running)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
                                // pozriem sa ci som stlacil esc 
				else if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						running = false;
					}
				}
			}

			// Clear the window to black
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_RenderClear(renderer);
                        
                        // Set the draw color to be white
                       SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			// Vykresli sieť 
                       for(int y = 0; y < WINDOW_HEIGHT; ++y) {
                           
                           // aby sme vytvorili prerusovanu ciaru  kazdy 5 pixel nechame medzeru
                           if(y % 5) {
                               
                               SDL_RenderDrawPoint(renderer,WINDOW_WIDTH/2,y);
                           }
                       
                       }
                       
                       // Vykresli lopticku
                       ball.Draw(renderer);
                       
                       // Draw the paddles
                       paddleOne.Draw(renderer);
                       paddleTwo.Draw(renderer);

			// Present the backbuffer
			SDL_RenderPresent(renderer);
		}
                

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
        }
    return 0;
};

