#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponenet : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TileComponenet() = default;

	~TileComponenet()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponenet(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};