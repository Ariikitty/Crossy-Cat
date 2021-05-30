#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	//Creates the object's texture using the texture manager
	objectTexture = TextureManager::LoadTexture(textureSheet);

	//Set's the object's starting position
	xpos = x;
	ypos = y;
}

void GameObject::Update() 
{
	//Updates the object's position
	xpos++;
	ypos++;

	//Set's the sprite's width, height and starting point
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	//Scales the sprite's width, height and updates it's position on screen
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
	//Copies the render information to the renderer
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}