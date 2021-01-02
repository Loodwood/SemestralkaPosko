
#ifndef BALL_H
#define BALL_H

#include "Vec2.h"

enum class CollisionType
{
	None,
	Top,
	Middle,
	Bottom,
        Left,
	Right
};


struct Contact
{
	CollisionType type;
	float penetration;
};


//definovanoe konstant pre velkost nasej lopticky 
const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

 const int WINDOW_WIDTH_B = 1280;
 const int WINDOW_HEIGHT_B = 720;




class Ball 
{
public:
    Ball(Vec2 position, Vec2 velocity)
        : position(position), velocity(velocity)
    {
        // pre to ze vsetky atributy v rect su int potrebujeme pretypovanie 
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);      
        rect.w = BALL_WIDTH;          
        rect.h = BALL_HEIGHT;
    }
      
        // vzdy sa bude volat pri vykreslovani a pohybe lopticky
    void Draw(SDL_Renderer* renderer)
    {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);   
        // metoda sluzi na vykreslenie objektu na obrazovku
        SDL_RenderFillRect(renderer,&rect);
    }
    
    
    	void CollideWithWall(Contact const& contact)
	{
		if ((contact.type == CollisionType::Top)
		    || (contact.type == CollisionType::Bottom))
		{
			position.y += contact.penetration;
			velocity.y = -velocity.y;
		}
		else if (contact.type == CollisionType::Left)
		{
			position.x = WINDOW_WIDTH_B / 2.0f;
			position.y = WINDOW_HEIGHT_B / 2.0f;
			velocity.x = 1.0f;
			velocity.y = 0.75f * 1.0f;
		}
		else if (contact.type == CollisionType::Right)
		{
			position.x = WINDOW_WIDTH_B / 2.0f;
			position.y = WINDOW_HEIGHT_B / 2.0f;
			velocity.x = -1.0f;
			velocity.y = 0.75f * 1.0f;
		}
	}
    	void CollideWithPaddle(Contact const& contact)
	{
		position.x += contact.penetration;
		velocity.x = -velocity.x;

		if (contact.type == CollisionType::Top)
		{
			velocity.y = -.75f * 1.0f;
		}
		else if (contact.type == CollisionType::Bottom)
		{
			velocity.y = 0.75f * 1.0f;
		}
	}
    
    void Update(float dt)
    {
		position += velocity * dt;
    }
            
    // astribut pre nasu loptu kde sa nachadza         
    Vec2 position;
    // atribut pre pobyh lopticky
    Vec2 velocity;
    // a SDL na vykreslenie tvaru nasej lopticky
    SDL_Rect rect{};
            
};

#endif /* BALL_H */