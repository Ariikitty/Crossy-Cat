#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "Game.h"
#include <Windows.h>

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp, Vector2D vel, int l) : range(rng), speed(sp), velocity(vel), line(l)
	{}
	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;
		
		switch (line)
		{
		case 1:
			if (transform->position.x < -64)
			{
				std::cout << "Out of Range Line 1" << std::endl;
				entity->getComponent<TransformComponent>().position.x = 949;
				entity->getComponent<ProjectileComponent>().distance = 0;
			}
			break;
		case 2:
			if (transform->position.x < -64)
			{
				std::cout << "Out of Range Line 2" << std::endl;
				entity->getComponent<TransformComponent>().position.x = 1038;
				entity->getComponent<ProjectileComponent>().distance = 0;
			}
			break;
		case 3:
			if (transform->position.x > 832)
			{
				std::cout << "Out of Range Line 3" << std::endl;
				entity->getComponent<TransformComponent>().position.x = -337;
				entity->getComponent<ProjectileComponent>().distance = 0;
			}
			break;
		case 4:
			if (transform->position.x > 832)
			{
				std::cout << "Out of Range Line 4" << std::endl;
				entity->getComponent<TransformComponent>().position.x = -337;
				entity->getComponent<ProjectileComponent>().distance = 0;
			}
			break;
		default:
			break;
		}
	}

private:

	TransformComponent* transform = nullptr;

	int range = 0;
	int speed = 0;
	int distance = 0;
	int line = 0;
	Vector2D velocity = Vector2D(0,0);
};