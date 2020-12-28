/*
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
	std::vector<Padle*> *padles;
	SDL_Rect *ball;
public:
	const static int WINDOW_HEIGHT = 600;
	const static int WINDOW_WIDTH = 800;
	GameManager();
	void initPadles(clientPong *CliePong);
	void spawnFruit();
	bool fruitAte();
	void moveAllSnakes();
	void setDirectionOfSnakeOnLocalhost(int direction);
	int idOfSnakeThatMadeMistake();
	void setDirectionToSnake(char direction);
	void setDirectionToSnakes(char *directions);
	GameManager(int numberOfPlayers);
	SDL_Rect* getFruit();
	std::vector<Padle*>* getPadles();
	~GameManager();


};

*/
