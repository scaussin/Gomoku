#include "../includes/Gomoku.hpp"

MainController::MainController() : CurrentScene(IN_GAME)
{
	GameDatas.IA_Depth = DEFAULT_IA_DEEP;
	GameDatas.ActivePlayer = BLACK; // black always start the game.
	GameDatas.LastSuggestion.x = 0;
	GameDatas.LastSuggestion.y = 0;
	GameDatas.CanClick = true;
	if (DEBUG_MODE == 0)
	{
		CurrentScene = MAIN_MENU;
	}
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
		if (SDL_PollEvent(&(SDLHandler.event))
			&& MainMenu.TransitionningOut == false
			&& InGame.TransitionningOut == false)
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
					if (CurrentScene == MAIN_MENU)
					{
						// std::cout << "Escape pressed in main menu, quitting..." << std::endl;
						break;
					}
				}
			}
			// MAIN MENU EVENTS -> click, keys, ... etc
			if (CurrentScene == MAIN_MENU
				&& MainMenu.TransitionningOut == false)
			{
				MainMenu.HandleEvents(GameDatas, SDLHandler.event,
										SDLHandler);
			}
			// IN GAME EVENTS -> click, keys, ... etc
			else if (CurrentScene == IN_GAME)
			{
				InGame.HandleEvents(GameDatas, SDLHandler.event,
										SDLHandler);
			}
		}

		// --------------------------------------------	//
		//												//
		// GLOBAL DISPLAY - TRANSITIONS AND DISPLAYING	//
		//												//
		// --------------------------------------------	//

		// --------------------------------------------	//
		// For the MAIN_MENU SCENE -> INGAME			//
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
				// std::cout << "SCENE CHANGE" << std::endl;
				MainMenu.TransitionningOut = false;
				MainMenu.TransitionEnd = false;
				CurrentScene = GameDatas.SelectedScene;
			}
		}
		// --------------------------------------------	//
		// For the IN_GAME SCENE -> MAIN_MENU			//
		// --------------------------------------------	//
		else if (CurrentScene == IN_GAME)
		{
			if (InGame.TransitionningOut == false)
			{
				InGame.GameHandle(GameDatas, SDLHandler);
			}
			else
			{
				InGame.TransitionOut(SDLHandler);
			}
			if (InGame.TransitionEnd == true)
			{
				// std::cout << "SCENE CHANGE" << std::endl;
				InGame.TransitionningOut = false;
				InGame.TransitionEnd = false;
				CurrentScene = MAIN_MENU;
			}
			
		}
		SDL_RenderPresent(SDLHandler.renderer);
	}
	// SDL to clean up and shut down
	SDL_Quit();
}
