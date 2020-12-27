#pragma once
#include <vector>
#include "Snake.h"
#include <time.h>
#include <random>
#include "include/SDL.h"
#include <stdexcept>
#include "clientPong.h"
#include <iostream>
class GameManager
{
private:
	std::vector<Snake*> *snakes;
	SDL_Rect *fruit;
public:
	const static int WINDOW_HEIGHT = 600;
	const static int WINDOW_WIDTH = 800;
	GameManager();
	void initSnakes(clientPong *ClientHadik);
	void spawnFruit();
	bool fruitAte();
	void moveAllSnakes();
	void setDirectionOfSnakeOnLocalhost(int direction);
	int idOfSnakeThatMadeMistake();
	void setDirectionToSnake(char direction);
	void setDirectionToSnakes(char *directions);
	GameManager(int numberOfPlayers);
	SDL_Rect* getFruit();
	std::vector<Snake*>* getSnakes();
	~GameManager();


};

