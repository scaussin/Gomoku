#include "../includes/Gomoku.hpp"

InGameController::InGameController() :
	ImagesLoaded(false),
	ImagesDisplayed(false)
{

}

InGameController::~InGameController()
{

}

// ------------------------------------------------------------	//
//																//
//	Main Method for playing the game. Will contains the			//
//	differents phases of a game turn							//
//																//
// ------------------------------------------------------------	//

void	InGameController::GameHandle(t_GameDatas &Game,
										SDLHandler &SDLHandler)
{
	(void)Game;
	Game.ActivePlayer = BLACK;
	// initializing visuals
	if (!ImagesLoaded)
	{
		// Load images into memory
		LoadImages(SDLHandler);
		UI.LoadUI(SDLHandler);

		// place images on start;
		PlaceImagesOnStart(SDLHandler);
		UI.PlaceImagesOnStart(SDLHandler);
		Goban.InitBoard(SDLHandler);

		ImagesLoaded = true;
	}
	DisplayImages(SDLHandler);
	Goban.PutDisplay(Game, SDLHandler);
	UI.UpdateUI(Game, SDLHandler);
	UI.DisplayUI(Game, SDLHandler);


	
}

// ------------------------------------------------------------	//
//																//
//	Methods of the scene										//
//																//
// ------------------------------------------------------------	//

void	InGameController::LoadImages(SDLHandler &SDLHandler)
{
	
	InGameBgImg = new GameImage(SDLHandler, "./ressources/img/in_game/in_game_bg.bmp");
	InGameTitleImg = new GameImage(SDLHandler, "./ressources/img/in_game/in_game_title.bmp");
	GameModeCaseImg = new GameImage(SDLHandler, "./ressources/img/in_game/info_back.bmp");
	GameModeText = new GameText(SDLHandler, "Playing game...", 1024);
}

void	InGameController::PlaceImagesOnStart(SDLHandler &SDLHandler)
{
	InGameBgImg->SetImgPos(0, 0);
	InGameBgImg->SetImgSize(1920, 1080);
	InGameBgImg->SetAlpha(0);

	InGameTitleImg->SetImgPos(0, 0);
	InGameTitleImg->SetImgSize(418, 85);
	InGameTitleImg->SetAlpha(0);
	InGameTitleImg->PutImage(SDLHandler);

	GameModeCaseImg->SetImgPos(10, 100);
	GameModeCaseImg->SetImgSize(406, 142);
	GameModeCaseImg->SetAlpha(255);
	GameModeCaseImg->PutImage(SDLHandler);

	GameModeText->SetTextPos(40, 130);
	GameModeText->SetTextSize(300, 60);
	GameModeText->SetAlpha(255);
	GameModeText->PutText(SDLHandler);
}

/*
**	This method will display the images at each loop turn.
*/

void	InGameController::DisplayImages(SDLHandler &SDLHandler)
{
	InGameBgImg->FadeIn();
	InGameBgImg->PutImage(SDLHandler);
	InGameTitleImg->FadeIn();
	InGameTitleImg->PutImage(SDLHandler);
	GameModeCaseImg->FadeIn();
	GameModeCaseImg->PutImage(SDLHandler);
	GameModeText->FadeIn();
	GameModeText->PutText(SDLHandler);
	
}

// ------------------------------------------------------------	//
//																//
//	Methods of the scene's events								//
//																//
// ------------------------------------------------------------	//

void	InGameController::HandleEvents(t_GameDatas &GameDatas, SDL_Event &event,
										SDLHandler &SDLHandler)
{
	t_vec2		move;

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (Goban.HandleClickEvents(GameDatas, event, SDLHandler, move) == 1)
		{
			// user clicked on a valid point of the board.
			GameDatas.ActivePlayer = BLACK;
			Game.Play(GameDatas, Goban, SDLHandler, move);
		}
		// Temp debug : WHITE pose stone.
		else if (Goban.HandleClickEvents(GameDatas, event, SDLHandler, move) == 2)
		{
			GameDatas.ActivePlayer = WHITE;
			Game.Play(GameDatas, Goban, SDLHandler, move);
		}
	}
}
