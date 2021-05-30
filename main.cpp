#include "Game.h"


Game* game = nullptr;

int main(int argc, char* argv[])
{
	//Limits the frame rate
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	//Creates a game object
	game = new Game();

	//Initialises the game window
	game->init("Crossy Cat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 832, 768, false);
	
	//Runs while the game is running
	while (game->running())
	{
		//Get what tick the frame started on
		frameStart = SDL_GetTicks();

		//Run all the frame updates
		game->handleEvents();
		game->update();
		game->render();

		//Work out how much time it took to perform the frame update
		frameTime = SDL_GetTicks() - frameStart;

		//If the frame updates faster then the frame rate, wait for the next frame to be needed
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	//Clears memory when the game is no longer running
	game->clean();

	return 0;
}