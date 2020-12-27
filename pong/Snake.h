#pragma once
#include "include/SDL.h"
#include <time.h>
#include <random>
#include <stdlib.h>
#include <stdexcept>
#include <vector>

class Snake
{
private:
	std::vector <SDL_Rect*> *snakeBody;
	int direction;
	int lengthOfSnake;

public:
	const static int UP = 0;
	const static int DOWN = 1;
	const static int LEFT = 2;
	const static int RIGHT = 3;
	const static int SIZE = 20;//size of block of snake
	bool isThisPosOfSnakeHead(int x, int y);
	void initializeSnake(int headX, int headY);
	void makeLonger();
	void moveSnake();
	void setDirection(int direction);
	bool hitItself();
	bool hitBorder(int width, int height);
	int getLengthOfSnake();
	std::vector<SDL_Rect*>* getSnake();
	Snake();
	~Snake();
};
