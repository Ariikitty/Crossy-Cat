#pragma once

#include "ECS.h"
#include "Vector2D.h"
#include "Game.h"
#include "TextureManager.h"

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

	TileComponenet(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
	{
		texture = Game::assets->GetTexture(id);

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