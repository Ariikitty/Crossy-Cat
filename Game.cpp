#include "Game.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

//Add Game Objects here
Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

int Game::lives = 5;
int Game::score = 0;
int Game::delay = 0;
bool Game::isRunning = false;

//Creating entities
auto& player(manager.addEntity()); 
auto& house(manager.addEntity());	

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

	//Texture Library
	assets->AddTexture("terrain", "assets/main_ss.png");
	assets->AddTexture("house", "assets/house.png");
	assets->AddTexture("player", "assets/cat.png");
	assets->AddTexture("carR", "assets/car.png");
	assets->AddTexture("carL", "assets/car2.png");
	assets->AddTexture("train", "assets/train.png");

	//Creates and loads the map
	map = new Map("terrain", 1, 64);
	map->LoadMap("assets/main.map", 13, 12);

	//Adds the player's components
	player.addComponent<TransformComponent>(384.0f, 640.0f, 64, 64, 1);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	//Creates the houses
	house.addComponent<TransformComponent>(384.0f, 64.0f, 64, 64, 1);
	house.addComponent<SpriteComponent>("house");
	house.addComponent<ColliderComponent>("house");
	house.addGroup(groupHouses);

	//Creates the cars
	srand(time(NULL));

	delay = rand() % 400 + 832;
	assets->CreateProjectile(Vector2D(delay, 512), Vector2D(-1, 0), 350, 2, "carL", 1); //Line 1
	delay = rand() % 400 + 1232;
	assets->CreateProjectile(Vector2D(delay, 512), Vector2D(-1, 0), 350, 2, "carL", 1); //Line 1
	delay = rand() % 400 + 1632;
	assets->CreateProjectile(Vector2D(delay, 512), Vector2D(-1, 0), 350, 2, "carL", 1); //Line 1
	delay = rand() % 400 + 832;
	assets->CreateProjectile(Vector2D(delay, 192), Vector2D(-1, 0), 350, 2, "carL", 2); //Line 2
	delay = rand() % 400 + 1232;
	assets->CreateProjectile(Vector2D(delay, 192), Vector2D(-1, 0), 350, 2, "carL", 2); //Line 2
	delay = rand() % 400 + 1632;
	assets->CreateProjectile(Vector2D(delay, 192), Vector2D(-1, 0), 350, 2, "carL", 2); //Line 2
	delay = rand() % 400 + 64;
	assets->CreateProjectile(Vector2D(-delay, 448), Vector2D(1, 0), 350, 2, "carR", 3); //Line 3
	delay = rand() % 400 + 464;
	assets->CreateProjectile(Vector2D(-delay, 448), Vector2D(1, 0), 350, 2, "carR", 3); //Line 3
	delay = rand() % 400 + 864;
	assets->CreateProjectile(Vector2D(-delay, 448), Vector2D(1, 0), 350, 2, "carR", 3); //Line 3
	delay = rand() % 400 + 64;
	assets->CreateProjectile(Vector2D(-delay, 128), Vector2D(1, 0), 350, 2, "carR", 4); //Line 4
	delay = rand() % 400 + 464;
	assets->CreateProjectile(Vector2D(-delay, 128), Vector2D(1, 0), 350, 2, "carR", 4); //Line 4
	delay = rand() % 400 + 864;
	assets->CreateProjectile(Vector2D(-delay, 128), Vector2D(1, 0), 350, 2, "carR", 4); //Line 4

	//Creates the train
	delay = rand() % 400 + 832;
	assets->CreateProjectile(Vector2D(delay, 256), Vector2D(-2, 0), 350, 2, "carL", 2); //Line 1
	delay = rand() % 400 + 64;
	assets->CreateProjectile(Vector2D(-delay, 384), Vector2D(2, 0), 350, 2, "carR", 3); //Line 2
}

//Define the groups
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& houses(manager.getGroup(Game::groupHouses));
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

	//Updates the objects
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

	for (auto& o : objects)
	{
		SDL_Rect oCol = o->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(playerCol, oCol))
		{
			std::cout << "Hit the player" << std::endl; //384 640
			lives -= 1;
			player.getComponent<TransformComponent>().position.x = 384;
			player.getComponent<TransformComponent>().position.y = 640;
		}
	}

	for (auto& h : houses)
	{
		SDL_Rect hCol = h->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(hCol, playerCol))
		{
			std::cout << "Player reached Home" << std::endl;
			score++;
			player.getComponent<TransformComponent>().position.x = 384;
			player.getComponent<TransformComponent>().position.y = 640;
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
	for (auto& h : houses)
	{
		h->draw();
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