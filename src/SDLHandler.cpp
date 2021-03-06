#include "../includes/Gomoku.hpp"

SDLHandler::SDLHandler() : pWindow(NULL)
{

}

SDLHandler::~SDLHandler()
{

}

/*
**	Initialize the window and the renderer for the engine.
*/

int		SDLHandler::InitWindow()
{
	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stdout,"SDL init Error(%s)\n", SDL_GetError());
		return (-1);
	}

	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Gomoku",
				0,
				0,
				WINDOW_WIDTH, WINDOW_HEIGHT,
				SDL_WINDOW_SHOWN);
				/*pWindow = SDL_CreateWindow("Gomoku",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WINDOW_WIDTH, WINDOW_HEIGHT,
				SDL_WINDOW_SHOWN);*/
	if (!pWindow)
	{
		fprintf(stderr,"Window creation ERROR: %s\n",
					SDL_GetError());
		return (-1);
	}
	renderer = SDL_CreateRenderer(pWindow, -1,
				SDL_RENDERER_ACCELERATED);
	return (0);
}

int		SDLHandler::InitSDL_ttf()
{
	if (!TTF_WasInit() && TTF_Init() == -1)
	{
		std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
		return (-1);
	}
	return (0);
}

/*
**	Clear the image to black.
*/

void	SDLHandler::ClearWindow()
{
	/* Select the color for drawing. Black here. */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	/* Clear the entire screen to our selected color. */
	SDL_RenderClear(renderer);
}
