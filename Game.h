#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game 
{

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;

	static int lives;
	static int score;
	static int delay;
	static bool isRunning;
	static AssetManager* assets;

	//Creates the layers for the game
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupHouses,
		groupObjects,
		groupColliders
	};

private:
	int cnt = 0;
	SDL_Window* window;
};