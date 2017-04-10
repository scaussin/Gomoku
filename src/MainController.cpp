#include "../includes/Gomoku.hpp"

MainController::MainController() : CurrentStage(MAIN_MENU)
{

}


MainController::~MainController()
{

}

void	MainController::InitGomoku()
{
	SDLHandler.InitWindow();
	MainMenu.LoadImages(SDLHandler);
}

void	MainController::MainLoop()
{
	while (1)
	{
		SDLHandler.ClearWindow(); // set the window black.
		// Check for messages
		if (SDL_PollEvent(&(SDLHandler.event)))
		{
			// Check for the quit message
			if (SDLHandler.event.type == SDL_QUIT)
			{
				// Quit the program
				break ;
			}
		}

		// Game loop will go here...
		if (CurrentStage == MAIN_MENU)
		{
			MainMenu.DisplayImages(SDLHandler);
			//MainMenu.Events();
		}

		SDL_RenderPresent(SDLHandler.renderer);
	}
	// SDL to clean up and shut down
	SDL_Quit();
}
