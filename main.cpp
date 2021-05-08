#include "SDL.h"

int main(int argc, char* argv[])
{
	//Sets up the window and the renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	
	//Sets the rendered window to green
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	//Clears the renderer
	SDL_RenderClear(renderer);

	//Shows the rendered screen
	SDL_RenderPresent(renderer);

	//Delays SDL's output
	SDL_Delay(3000);

	return 0;
}