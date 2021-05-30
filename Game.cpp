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

//Creating entities
auto& player(manager.addEntity()); 
auto& wall(manager.addEntity());

//Creates the layers for the game
enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupObjects,
	groupColliders
};

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

	//Add Game Object textures here
	
	//Loads the map file
	Map::LoadMap("assets/main.map", 13, 10);

	//Adds the player's components
	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/Player.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	//Adds the wall's components
	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent <SpriteComponent>("assets/playerFront2.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
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

	//Checks for collisions
	for (auto& cc : colliders)
	{
		(Collision::AABB(player.getComponent<ColliderComponent>(), *cc));
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& objects(manager.getGroup(groupObjects));

void Game::render()
{
	//Clears the renderer
	SDL_RenderClear(renderer);

	//Draws all the layers
	for (auto& t : tiles)
	{
		t->draw();
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

void Game::AddTile(int id, int x, int y)
{	
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponenet>(x, y, 64, 64, id);
	tile.addGroup(groupMap);
}