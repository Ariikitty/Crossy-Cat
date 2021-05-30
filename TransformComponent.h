#pragma once

#include "Components.h"
#include "Vector2D.h"
#include <cmath>
#include <iostream>

class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height = 64;
	int width = 64;
	int scale = 1;

	int speed = 3;

	

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		//velocity.Normalize(); //Normalising the vector is cauing a -nan(ind). I can only assume it's because it's trying to divide by 0
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		/* if (position.x != 0 || position.y != 0)
		{
			std::cout << position.x << ", " << position.y << std::endl;
		} */ //This is only here so I could try to debug why my sprite isn't rendering when I normalize this
	}
};
