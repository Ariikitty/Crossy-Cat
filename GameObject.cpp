#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y)
{
	//Passes through the renderer
	renderer = ren;
	//Creates the object's texture using the texture manager
	objectTexture = TextureManager::LoadTexture(textureSheet, ren);

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
	srcRect.h = 32;
	srcRect.w = 32;
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
	SDL_RenderCopy(renderer, objectTexture, &srcRect, &destRect);
}