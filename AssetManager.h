#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"

class AssetManager
{
public:

	AssetManager(Manager* man);
	~AssetManager();

	//Game Objects
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id, int line);

	//Texture Management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};