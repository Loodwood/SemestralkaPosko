#include "Snake.h"

void Snake::initializeSnake(int headX, int headY)
{
	//lengthOfSnake = 1;
	snakeBody->push_back(new SDL_Rect());
	snakeBody->at(0)->x = headX;
	snakeBody->at(0)->y = headY;
	snakeBody->at(0)->h = this->SIZE;
	snakeBody->at(0)->w = this->SIZE;

}

void Snake::makeLonger()
{
	snakeBody->push_back(new SDL_Rect());
	//snakeBody->at(lengthOfSnake) = new SDL_Rect();
	snakeBody->at(lengthOfSnake)->w = SIZE;
	snakeBody->at(lengthOfSnake)->h = SIZE;

	/*append another block of the snake */
	switch (this->direction) {
	case UP:
		snakeBody->at(lengthOfSnake)->x = snakeBody->at(lengthOfSnake - 1)->x;
		snakeBody->at(lengthOfSnake)->y = snakeBody->at(lengthOfSnake - 1)->y + SIZE;
		break;
	case DOWN:
		snakeBody->at(lengthOfSnake)->x = snakeBody->at(lengthOfSnake - 1)->x;
		snakeBody->at(lengthOfSnake)->y = snakeBody->at(lengthOfSnake - 1)->y - SIZE;
		break;
	case LEFT:
		snakeBody->at(lengthOfSnake)->x = snakeBody->at(lengthOfSnake - 1)->x + SIZE;
		snakeBody->at(lengthOfSnake)->y = snakeBody->at(lengthOfSnake - 1)->y;
		break;
	case RIGHT:
		snakeBody->at(lengthOfSnake)->x = snakeBody->at(lengthOfSnake - 1)->x - SIZE;
		snakeBody->at(lengthOfSnake)->y = snakeBody->at(lengthOfSnake - 1)->y;
		break;
	}

	lengthOfSnake++;

}

void Snake::moveSnake()
{
	/* Logic in the movement of the snake is that we replace the coordinates of [i]. block with
		   the coordinates of [i-1]. block going from the end ... [2] <- [1] ; [1] <- [0] etc.. except for the [0]. element
		   which we change according to the key */
	switch (this->direction) {
	case UP:
		for (int i = 1; i < lengthOfSnake; i++)
		{
			snakeBody->at(lengthOfSnake - i)->x = snakeBody->at(lengthOfSnake - i - 1)->x;
			snakeBody->at(lengthOfSnake - i)->y = snakeBody->at(lengthOfSnake - i - 1)->y;
		}
		snakeBody->at(0)->y -= SIZE;
		break;
	case DOWN:
		for (int i = 1; i < lengthOfSnake; i++)
		{
			snakeBody->at(lengthOfSnake - i)->x = snakeBody->at(lengthOfSnake - i - 1)->x;
			snakeBody->at(lengthOfSnake - i)->y = snakeBody->at(lengthOfSnake - i - 1)->y;
		}
		snakeBody->at(0)->y += SIZE;
		break;
	case LEFT:
		for (int i = 1; i < lengthOfSnake; i++) {
			snakeBody->at(lengthOfSnake - i)->x = snakeBody->at(lengthOfSnake - i - 1)->x;
			snakeBody->at(lengthOfSnake - i)->y = snakeBody->at(lengthOfSnake - i - 1)->y;
		}
		snakeBody->at(0)->x -= SIZE;
		break;
	case RIGHT:
		for (int i = 1; i < lengthOfSnake; i++)
		{
			snakeBody->at(lengthOfSnake - i)->x = snakeBody->at(lengthOfSnake - i - 1)->x;
			snakeBody->at(lengthOfSnake - i)->y = snakeBody->at(lengthOfSnake - i - 1)->y;
		}
		snakeBody->at(0)->x += SIZE;
		break;
	}
}

void Snake::setDirection(int direction)
{
	switch (direction) {
	case UP:
		this->direction = UP;
		break;
	case DOWN:
		this->direction = DOWN;
		break;
	case LEFT:
		this->direction = LEFT;
		break;
	case RIGHT:
		this->direction = RIGHT;
		break;
	default:
		throw std::invalid_argument("wrong argument passed to direction");
		break;
	}

}

bool Snake::hitItself()
{
	for (int j = 1; j < lengthOfSnake; j++) {
		if (snakeBody->at(0)->x == snakeBody->at(j)->x && snakeBody->at(0)->y == snakeBody->at(j)->y) {
			return true;
			break;
		}
	}
	return false;
}

bool Snake::hitBorder(int width, int height)
{
	int headX = snakeBody->at(0)->x;
	int headY = snakeBody->at(0)->y;
	if (headX < 0 || headY < 0 || headX + SIZE > width || headY + SIZE > height) {
		return true;
	}
	else {
		return false;
	}
}

int Snake::getLengthOfSnake()
{
	return lengthOfSnake;
}

std::vector<SDL_Rect*>* Snake::getSnake()
{
	return snakeBody;
}

bool Snake::isThisPosOfSnakeHead(int x, int y)
{

	if (snakeBody->at(0)->y == y && snakeBody->at(0)->x == x) {
		return true;
	}
	else {
		return false;
	}

}

Snake::Snake()
{
	this->snakeBody = new std::vector<SDL_Rect*>();
	this->direction = Snake::RIGHT;
	this->lengthOfSnake = 1;
}

Snake::~Snake()
{
	for (int i = 0; i < snakeBody->size(); i++) {
        SDL_Rect *rectBody = snakeBody->at(i);
		delete rectBody;
	}
	delete snakeBody;
}
