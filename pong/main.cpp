
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <SDL2/SDL.h>
#include <time.h>
#include <random>
//#include "GameManager.h"
#include <vector>
#include "clientPong.h"

using namespace std;

int main(int argc, char* argv[]) {

    //initialization client and game manager
    clientPong *ClientHadik = new clientPong();
    //GameManager gameManager(2);
    //gameManager.initSnakes(ClientHadik);
    //gameManager.spawnFruit();

    //initialization window for snakes
    SDL_Event e;
    SDL_Window *window;
    SDL_Renderer* renderer;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
            "Pong",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            GameManager::WINDOW_WIDTH,
            GameManager::WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL
    );
    renderer = SDL_CreateRenderer(window, -1, 0);

    /*  //if game is run
      bool playing = true;
      while (playing) { *//* Main Game LOOP *//*

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
            {
                playing = false;
                break;
            }
            if (e.type == SDL_KEYDOWN) {

                // if the KEY was pressed
                switch (e.key.keysym.sym) {
                    //send pressed kez = direction on server to client
                    case SDLK_RIGHT:
                        //gameManager.setDirectionOfSnakeOnLocalhost(Snake::RIGHT);
                        ClientHadik->sendToClient('r');
                        break;

                    case SDLK_LEFT:
                        //gameManager.setDirectionOfSnakeOnLocalhost(Snake::LEFT);
                        ClientHadik->sendToClient('l');
                        break;

                    case SDLK_UP:
                        //gameManager.setDirectionOfSnakeOnLocalhost(Snake::UP);
                        ClientHadik->sendToClient('u');
                        break;

                    case SDLK_DOWN:
                        // gameManager.setDirectionOfSnakeOnLocalhost(Snake::DOWN);
                        ClientHadik->sendToClient('d');
                        break;
                }
            }
        }

        // if snake's head [0] is at fruit position , the snake is gonna eat the fruit
        if (gameManager.fruitAte()) {
            gameManager.spawnFruit();
        }

        //VYHODNOTENIE HRY
        char directionOfEnemySnake = ClientHadik->getDirection();
        gameManager.setDirectionToSnake(directionOfEnemySnake);
        gameManager.moveAllSnakes();

        //if -1 -> nobody made a mistake
        int idOfSnakeThatMadeMistake = gameManager.idOfSnakeThatMadeMistake();
        if (idOfSnakeThatMadeMistake == -1) {
            playing = true;
        } else {
            std::cout << "********************************" << std::endl;
            std::cout << "            VYHODNOTENIE        " << std::endl;
            if (idOfSnakeThatMadeMistake == 0) {
                std::cout << "Prehrali ste. Urobili ste chybu, ktoru super nekompromisne vyuzil." << std::endl;
            } else {
                std::cout << "VITAZSTVO!!! Supera ste rozlozili ako stan!" << std::endl;

            }
            std::cout << "Porovnavam dlzky... "  << std::endl;
            std::cout << "Vas hadik je dlhy: " << gameManager.getSnakes()->at(0)->getLengthOfSnake() << std::endl;
            std::cout << "Superov hadik ma dlzku: " << gameManager.getSnakes()->at(1)->getLengthOfSnake() << std::endl;
            std::cout << "********************************" << std::endl;
            std::cout << "Pre opatovne spustenie hry napiste prikaz : ./Snake" << std::endl;
            std::cout << "a pockajte kym sa pripoji super." << std::endl;
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;
            playing = false;
            break;
        }

        //RENDERRING
        // Render gameplan
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Fruit render
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, gameManager.getFruit());

        // Snakes render
        std::vector<Snake*> *snakes = gameManager.getSnakes();
        for (int i = 0; i < snakes->size(); i++) {
            if (i == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 100, 0, 100, 255);
            }

            for (int x = 0; x < snakes->at(i)->getLengthOfSnake(); x++) {
                SDL_Rect* rect = snakes->at(i)->getSnake()->at(x);
                SDL_RenderFillRect(renderer, rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(600);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Clean up
    delete ClientHadik;*/
    SDL_Quit();
    return 0;
}
