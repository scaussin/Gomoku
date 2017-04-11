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
		// Check for messages
		if (SDL_PollEvent(&(SDLHandler.event)))
		{
			// Check for the quit message
			if (SDLHandler.event.type == SDL_QUIT)
			{
				// Quit the program
				break ;
			}
			if (CurrentScene == MAIN_MENU
				&& MainMenu.TransitionningOut == false)
			{
				MainMenu.HandleEvents(GameDatas, SDLHandler.event, SDLHandler);
			}
		}

		// Permanent game loop methods
		if (CurrentScene == MAIN_MENU)
		{
			if (!MainMenu.TransitionningOut)
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
		SDL_RenderPresent(SDLHandler.renderer);
	}
	// SDL to clean up and shut down
	SDL_Quit();
}
