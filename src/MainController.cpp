#include "../includes/Gomoku.hpp"

MainController::MainController() : CurrentScene(MAIN_MENU)
{

}


MainController::~MainController()
{

}

void	MainController::InitGomoku()
{
	// Init SDL engine and components.
	SDLHandler.InitWindow();
	SDLHandler.InitSDL_ttf();

	// For the main Menu scene
	MainMenu.LoadImages(SDLHandler);

	// TODO: For the In Game scene
	//InGame.LoadImages(SDLHandler);
}

// ------------------------------------------------------------	//
//																//
//				Main loop for the Game							//
//																//
// ------------------------------------------------------------	//

void	MainController::MainLoop()
{
	while (1)
	{
		SDLHandler.ClearWindow(); // set the window black.

		// --------------------------------------------	//
		// For the events								//
		// --------------------------------------------	//
		if (SDL_PollEvent(&(SDLHandler.event)))
		{
			// Check for the quit message
			if (SDLHandler.event.type == SDL_QUIT)
			{
				// Quit the program
				break ;
			}
			// Check for press escape -> leave.
			if (SDLHandler.event.type == SDL_KEYDOWN)
			{
				if (SDLHandler.event.key.keysym.sym == SDLK_ESCAPE)
				{
					std::cout << "Escape pressed, quitting..." << std::endl;
					break;
				}
			}

			if (CurrentScene == MAIN_MENU
				&& MainMenu.TransitionningOut == false)
			{
				MainMenu.HandleEvents(GameDatas, SDLHandler.event,
										SDLHandler);
			}
			else if (CurrentScene == IN_GAME)
			{
				InGame.HandleEvents(GameDatas, SDLHandler.event,
										SDLHandler);
			}
		}

		// --------------------------------------------	//
		// For the MAIN_MENU SCENE						//
		// --------------------------------------------	//
		if (CurrentScene == MAIN_MENU)
		{
			if (MainMenu.TransitionningOut == false)
			{
				MainMenu.DisplayImages(SDLHandler);
				MainMenu.CheckHover(SDLHandler);
			}
			else
			{
				MainMenu.TransitionOut(SDLHandler);
			}
			if (MainMenu.TransitionEnd == true)
			{
				std::cout << "SCENE CHANGE" << std::endl;
				CurrentScene = GameDatas.SelectedScene;
			}
		}
		// --------------------------------------------	//
		// For the IN_GAME SCENE						//
		// --------------------------------------------	//
		else if (CurrentScene == IN_GAME)
		{
			InGame.GameHandle(GameDatas, SDLHandler);
		}
		SDL_RenderPresent(SDLHandler.renderer);
	}
	// SDL to clean up and shut down
	SDL_Quit();
}
