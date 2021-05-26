#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

#include "ECS.h"
#include "Components.h"

//Add Game Objects here
GameObject* player;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		std::cout << "Subsystems Initialised!..." << std::endl;

		//Creates the SDL Window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		//Creates the SDL Renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			//Sets the renderer colour to white
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		//Starts the game loop
		isRunning = true;
	}

	//Add Game Object textures here
	player = new GameObject("assets/player.png", 0, 0);
	map = new Map();

	newPlayer.addComponent<PositionComponent>();
	newPlayer.getComponent<PositionComponent>().setPos(500, 500);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		//If the game is quit, stop the game loop
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	//Updates the player object
	player->Update();
	manager.update();
	std::cout << newPlayer.getComponent<PositionComponent>().x() << ", "
		<< newPlayer.getComponent<PositionComponent>().y() << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	//Render level here
	map->DrawMap();

	//Render all game objects here
	player->Render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	//Cleans up memory when the game exits
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}