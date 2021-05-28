#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

//Add Game Objects here
Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity()); 
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

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
	map = new Map();

	tile0.addComponent<TileComponenet>(200, 200, 32, 32, 0);
	tile1.addComponent<TileComponenet>(250, 250, 32, 32, 1);
	tile2.addComponent<TileComponenet>(150, 150, 32, 32, 2);
	tile2.addComponent <ColliderComponent>("house");

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/Player.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent <SpriteComponent>("assets/playerFront2.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents()
{

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
	manager.refresh();
	manager.update();

	for (auto& cc : colliders)
	{
		(Collision::AABB(player.getComponent<ColliderComponent>(), *cc));
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	//Render level here
	//map->DrawMap();

	//Render all game objects here

	manager.draw();

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