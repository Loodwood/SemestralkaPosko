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
#include <bits/basic_file.h>
#include "SDL.h"
#include "Vec2.h"
#include "Ball.h"
#include "Paddle.h"
#include "PlayerScore.h"
#include <chrono>

#include "SDL_image.h"

using namespace std;

/*
 * 
 */
// konstasnty pre nase hracie okno 
 const int WINDOW_WIDTH = 1280;
 const int WINDOW_HEIGHT = 720;
 const float PADDLE_SPEED = 1.0f;

enum Buttons
{
	PaddleOneUp = 0,
	PaddleOneDown,
	PaddleTwoUp,
	PaddleTwoDown,
};



int main(int argc, char** argv) {
    
    
	// Initialize SDL components
	SDL_Init(SDL_INIT_VIDEO);
        //Initialization flag
        bool success = true;
        

          
        // vytvorit okno kde chceme vykreslovat hru 
	SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        
        
        // inicializovaie nasho fontu pre text 
        //TTF_Font* scoreFont = TTF_OpenFont("C:/Users/marti/Desktop/SEMKAPOS/pong/Pong/DejaVuSansMono.ttf",40);
        
        // Create the player score text fields
        PlayerScore playerOneScoreText(Vec2(WINDOW_WIDTH / 4, 20), renderer);

        PlayerScore playerTwoScoreText(Vec2(3 * WINDOW_WIDTH / 4, 20), renderer);
        
      
        
        
        //vytvor lopticku  
        Ball ball(
            Vec2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f),
            (WINDOW_HEIGHT / 2.0f) - (BALL_HEIGHT / 2.0f)));
        
        // Create the paddles
        Paddle paddleOne(
	Vec2(50.0f, WINDOW_HEIGHT / 2.0f),
                Vec2(0.0f,0.0f));

        Paddle paddleTwo(
	Vec2(WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT / 2.0f),
               Vec2(0.0f,0.0f));

	// Herna logika 
	{
		bool running = true;
                bool buttons[4] = {};
                
                // inicilizovanie kvoli pohybu 
                
                float dt = 0.0f;
		// Continue looping and processing events until user exits
		while (running)
		{
                    // herny cas zaciatok
                    auto startTime = std::chrono::high_resolution_clock::now();
                    
                    
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
                                        else if (event.key.keysym.sym == SDLK_w)
                                        {
                                                buttons[Buttons::PaddleOneUp] = true;
                                        }
                                        else if (event.key.keysym.sym == SDLK_s)
                                        {
                                                buttons[Buttons::PaddleOneDown] = true;
                                        }
                                        else if (event.key.keysym.sym == SDLK_UP)
                                        {
                                                buttons[Buttons::PaddleTwoUp] = true;
                                        }
                                        else if (event.key.keysym.sym == SDLK_DOWN)
                                        {
                                                buttons[Buttons::PaddleTwoDown] = true;
                                        }
                                }
                                else if (event.type == SDL_KEYUP)
                                {
                                    if (event.key.keysym.sym == SDLK_w)
                                    {
                                            buttons[Buttons::PaddleOneUp] = false;
                                    }
                                    else if (event.key.keysym.sym == SDLK_s)
                                    {
                                            buttons[Buttons::PaddleOneDown] = false;
                                    }
                                    else if (event.key.keysym.sym == SDLK_UP)
                                    {
                                            buttons[Buttons::PaddleTwoUp] = false;
                                    }
                                    else if (event.key.keysym.sym == SDLK_DOWN)
                                    {
                                            buttons[Buttons::PaddleTwoDown] = false;
                                    }
                                }
			}
                        
         if (buttons[Buttons::PaddleOneUp])
	{
		paddleOne.velocity.y = -PADDLE_SPEED;
	}
	else if (buttons[Buttons::PaddleOneDown])
	{
		paddleOne.velocity.y = PADDLE_SPEED;
	}
	else
	{
		paddleOne.velocity.y = 0.0f;
	}
                            
        if (buttons[Buttons::PaddleTwoUp])
	{
		paddleTwo.velocity.y = -PADDLE_SPEED;
	}
	else if (buttons[Buttons::PaddleTwoDown])
	{
		paddleTwo.velocity.y = PADDLE_SPEED;
	}
	else
	{
		paddleTwo.velocity.y = 0.0f;
	}
                        // Update the paddle positions
                        paddleOne.Update(dt);
                        paddleTwo.Update(dt);
                    
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
                       
                       // Display the scores
                        playerOneScoreText.Draw();
                        playerTwoScoreText.Draw();

			// Present the backbuffer
			SDL_RenderPresent(renderer);
                        
                        
                        // Calculate frame time
                        auto stopTime = std::chrono::high_resolution_clock::now();
                        dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
                        
                        
		}
                

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
        //TTF_CloseFont(scoreFont);
        //TTF_Quit();
	SDL_Quit();
       
        }
    return 0;
};




