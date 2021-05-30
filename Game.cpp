#include "Game.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

//Add Game Objects here
Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

//Creating entities
auto& player(manager.addEntity()); 

Game::Game()
{}

Game::~Game()
{}

//Initalising the game
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen)
		{
			//Set's the flag to fullscreen the game 
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

	map = new Map("assets/main_ss.png", 1, 64);

	//Add Game Object textures here
	
	//Loads the map file
	map->LoadMap("assets/main.map", 13, 12);

	//Adds the player's components
	player.addComponent<TransformComponent>(384.0f, 640.0f, 64, 64, 1);
	player.addComponent<SpriteComponent>("assets/cat.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& objects(manager.getGroup(Game::groupObjects));
auto& colliders(manager.getGroup(Game::groupColliders));

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

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	//Updates the player object
	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}
}

void Game::render()
{
	//Clears the renderer
	SDL_RenderClear(renderer);

	//Draws all the layers
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& c : colliders)
	{
		c->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& o : objects)
	{
		o->draw();
	}	

	//Presents the renderer
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