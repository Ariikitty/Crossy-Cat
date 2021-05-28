#pragma once

#include "Components.h"
#include "SDL.h"

class TileComponenet : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;
	TileComponenet() = default;

	TileComponenet(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "assets/house.png";
			break;
		case 1:
			path = "assets/road.png";
			break;
		case 2:
			path = "assets/track.png";
			break;
		case 3:
			path = "assets/grass.png";
			break;
		default:
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};