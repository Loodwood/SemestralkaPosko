#include "GameManager.h"

void GameManager::initSnakes(clientPong *ClientHadik)
{
    int xSnake1 = -1;
    int xSnake2 = -1;
    int ySnake1 = -1;
    int ySnake2 = -1;
    bool canStart = ClientHadik->getCanStart();

    while (!canStart) {
        canStart = ClientHadik->getCanStart();
    }
    if (ClientHadik->getClientID() == 0) {
        xSnake1 = 40;
        ySnake1 = 300;
        xSnake2 = 100;
        ySnake2 = 200;
    } else if (ClientHadik->getClientID() == 1) {
        xSnake1 = 100;
        ySnake1 = 200;
        xSnake2 = 40;
        ySnake2 = 300;
    }
    Snake *snake = snakes->at(0);
    snake->initializeSnake(xSnake1, ySnake1);
    Snake *snake2 = snakes->at(1);
    snake2->initializeSnake(xSnake2, ySnake2);
}

void GameManager::spawnFruit()
{
	int x = rand() % (this->WINDOW_WIDTH / Snake::SIZE) * Snake::SIZE;
	int y = rand() % (this->WINDOW_HEIGHT / Snake::SIZE) * Snake::SIZE;
	for (int i = 0; i < snakes->size(); i++) {
		if (snakes->at(i)->isThisPosOfSnakeHead(x, y)) {
			x = rand() % (this->WINDOW_WIDTH / Snake::SIZE) * Snake::SIZE;
		    y = rand() % (this->WINDOW_HEIGHT / Snake::SIZE) * Snake::SIZE;
			i = 0;
		}
	}
	this->fruit->x = x;
	this->fruit->y = y;
}

bool GameManager::fruitAte()
{
	for (int i = 0; i < snakes->size(); i++) {
		if (snakes->at(i)->isThisPosOfSnakeHead(fruit->x, fruit->y)) {
			snakes->at(i)->makeLonger();
			return true;
		}
	}
	return false;
}

void GameManager::moveAllSnakes()
{
	for (Snake *snake : *snakes) {
		snake->moveSnake();
	}
}

void GameManager::setDirectionOfSnakeOnLocalhost(int direction)
{
	snakes->at(0)->setDirection(direction);
}

int GameManager::idOfSnakeThatMadeMistake()
{
	//check for hitting himself
	for (int i = 0; i < snakes->size(); i++) {
		if (snakes->at(i)->hitItself()) {
			return i;
		}
	}

	//check for hitting border
	for (int i = 0; i < snakes->size(); i++) {
		if (snakes->at(i)->hitBorder(WINDOW_WIDTH, WINDOW_HEIGHT)) {
			return i;
		}
	}

	//check for hitting another snake - !!!!!!! THIS IS METHOD ONLY FOR TWO SNAKES !!!!!!!!
	for (int i = 0; i < snakes->size(); i++) {
		int xSnakeHead = snakes->at(i)->getSnake()->at(0)->x;
		int ySnakeHead = snakes->at(i)->getSnake()->at(0)->y;
		std::vector<SDL_Rect*> *snakeBody = NULL;
		if (i == 0) {
			snakeBody = snakes->at(1)->getSnake();
		}
		else {
			snakeBody = snakes->at(0)->getSnake();
		}

		for (SDL_Rect *partOfSnake : *snakeBody) {
			int xSnake2 = partOfSnake->x;
			int ySnake2 = partOfSnake->y;
			if (xSnakeHead == xSnake2 && ySnakeHead == ySnake2) {
				return i;
			}
		}
	}
	return -1;
}


void GameManager::setDirectionToSnake(char direction) {
    switch (direction) {
		case 'u' :
			snakes->at(1)->setDirection(Snake::UP);
			break;
		case 'd':
			snakes->at(1)->setDirection(Snake::DOWN);
			break;
		case 'r':
			snakes->at(1)->setDirection(Snake::RIGHT);
			break;
		case 'l':
			snakes->at(1)->setDirection(Snake::LEFT);
			break;
		default:
			throw std::invalid_argument("GAME MANAGER: setDirectionToSnakes -> wrong char parameter ");
		}
}

void GameManager::setDirectionToSnakes(char * directions)
{
	int dC = 0;
	for (int i = 1; i < snakes->size(); i++) {
		switch (directions[dC]) {
		case 'u' :
			snakes->at(i)->setDirection(Snake::UP);
			break;
		case 'd':
			snakes->at(i)->setDirection(Snake::DOWN);
			break;
		case 'r':
			snakes->at(i)->setDirection(Snake::RIGHT);
			break;
		case 'l':
			snakes->at(i)->setDirection(Snake::LEFT);
			break;
		default:
			throw std::invalid_argument("GAME MANAGER: setDirectionToSnakes -> wrong char parameter ");
		}
		dC++;
	}
}

GameManager::GameManager()
{
}

GameManager::GameManager(int numberOfPlayers)
{
	snakes = new std::vector<Snake*>();
	fruit = new SDL_Rect();
	fruit->h = Snake::SIZE;
	fruit->w = Snake::SIZE;
	for (int i = 0; i < numberOfPlayers; i++) {
		Snake *snake = new Snake();
		snakes->push_back(snake);
	}
}

SDL_Rect* GameManager::getFruit()
{
	return fruit;
}

std::vector<Snake*>* GameManager::getSnakes()
{
	return snakes;
}

GameManager::~GameManager()
{
	Snake *snake = NULL;
	for (int i = 0; i < snakes->size(); i++) {
        snake = snakes->at(i);
        delete snake;
	}

	delete snakes;
	delete fruit;
}
