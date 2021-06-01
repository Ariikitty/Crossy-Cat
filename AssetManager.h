#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"
#include "SDL_ttf.h"
#include <SDL_mixer.h>

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

	//Font Management
	void AddFont(std::string id, std::string path, int fontsize);
	TTF_Font* GetFont(std::string id);

	//Sound Management
	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);

private:

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Mix_Music*> mMusic;
	std::map<std::string, Mix_Chunk*> mSFX;
};