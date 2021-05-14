#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* ren)
{
	//Loads the sprite image and puts it onto a surface
	SDL_Surface* tmpSurface = IMG_Load(texture);
	//Creates a texture from the surface
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
	//Clears the surface ready for the next image
	SDL_FreeSurface(tmpSurface);

	//Returns the newly created texture
	return tex;
}