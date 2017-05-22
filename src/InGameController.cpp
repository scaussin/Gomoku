#include "../includes/Gomoku.hpp"

InGameController::InGameController() :
	ImagesLoaded(false),
	TransitionningOut(false),
	TransitionEnd(false)
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

void	InGameController::GameHandle(t_GameDatas &GameDatas,
										SDLHandler &SDLHandler)
{
	// initializing visuals and GameDatas
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

		Game.ResetGame(GameDatas);
	}
	DisplayImages(SDLHandler);
	Goban.PutDisplay(GameDatas, SDLHandler);
	UI.DisplayUI(GameDatas, SDLHandler);
	if (GameDatas.IsGameOver == true)
	{
		UI.DisplayVictoryCase(SDLHandler, GameDatas.WinnerColor);
	}
	else
	{
		UI.HideVictoryCase(SDLHandler);
	}
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
	// TODO: set game mode text according to game mode.
	GameModeText = new GameText(SDLHandler, "Playing game...", 64);
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
	GameModeText->SetTextSize(280, 60);
	GameModeText->SetAlpha(255);
	GameModeText->PutText(SDLHandler);
}

/*
**	This method will display the in game scene images at each loop turn.
*/

void	InGameController::DisplayImages(SDLHandler &SDLHandler)
{
	if (InGameBgImg->GetAlpha() < 255)
		InGameBgImg->FadeIn();
	InGameBgImg->PutImage(SDLHandler);
	if (InGameTitleImg->GetAlpha() < 255)
		InGameTitleImg->FadeIn();
	InGameTitleImg->PutImage(SDLHandler);
	if (GameModeCaseImg->GetAlpha() < 255)
		GameModeCaseImg->FadeIn();
	GameModeCaseImg->PutImage(SDLHandler);
	if (GameModeText->GetAlpha() < 255)
		GameModeText->FadeIn();
	GameModeText->PutText(SDLHandler);
}

void	InGameController::TransitionOut(SDLHandler &SDLHandler)
{
	
	if (InGameBgImg->GetAlpha() > 0)
		InGameBgImg->FadeOut();
	InGameBgImg->PutImage(SDLHandler);
	if (InGameTitleImg->GetAlpha() > 0)
		InGameTitleImg->FadeOut();
	InGameTitleImg->PutImage(SDLHandler);
	if (GameModeCaseImg->GetAlpha() > 0)
		GameModeCaseImg->FadeOut();
	GameModeCaseImg->PutImage(SDLHandler);
	if (GameModeText->GetAlpha() > 0)
		GameModeText->FadeOut();
	GameModeText->PutText(SDLHandler);
	Goban.TransitionOut(SDLHandler);
	if (InGameBgImg->GetAlpha() == 0
		&& InGameTitleImg->GetAlpha() == 0
		&& GameModeCaseImg->GetAlpha() == 0
		&& GameModeText->GetAlpha() == 0
		&& Goban.GobanImg->GetAlpha() == 0)
	{
		TransitionEnd = true;
	}
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

	if (GameDatas.CanClick == true)
	{
		GameDatas.CanClick = false;
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (GameDatas.IsGameOver == false
				&& Goban.HandleClickEvents(GameDatas, event, SDLHandler, move) == 1) // LEFT CLICK
			{
				// user clicked on a valid point of the board.
				if (DEBUG_MODE == 1) // in debug, left click is always BLACK
					GameDatas.ActivePlayer = BLACK;
				Game.Play(GameDatas, Goban, SDLHandler, move);
				UI.UpdateUIValues(GameDatas, SDLHandler);
			}
			// Debug mode only: WHITE pose stone.
			else if (DEBUG_MODE == 1 && GameDatas.IsGameOver == false
				&& Goban.HandleClickEvents(GameDatas, event, SDLHandler, move) == 2) // RIGHT CLICK
			{
				GameDatas.ActivePlayer = WHITE;
				Game.Play(GameDatas, Goban, SDLHandler, move);
			}
		}
		
		if (event.type == SDL_KEYDOWN)
		{
			// IF GAME OVER, PRESS RETURN TO RESET.
			if (GameDatas.IsGameOver == true)
			{
				if (event.key.keysym.sym == SDLK_RETURN)
				{
					// std::cout << "return pressed on game over, reseting board" << std::endl;
					Goban.ResetBoardVisuals(SDLHandler);
					Game.ResetGame(GameDatas);
					UI.UpdateUIValues(GameDatas, SDLHandler);
				}
			}
			// press r to reset anytime.
			if (event.key.keysym.sym == SDLK_r)
			{
				// std::cout << "reset key pressed, reseting board" << std::endl;
				Goban.ResetBoardVisuals(SDLHandler);
				Game.ResetGame(GameDatas);
				UI.UpdateUIValues(GameDatas, SDLHandler);
			}
			// press delete to revert last move;
			if (event.key.keysym.sym == SDLK_BACKSPACE)
			{
				// std::cout << KYEL "- Reverting last move! -" KRESET << std::endl;
				Game.RevertLastMove(GameDatas, SDLHandler, Goban);
				UI.UpdateUIValues(GameDatas, SDLHandler);
			}
			// press h to display key help.
			if (event.key.keysym.sym == SDLK_h)
			{
				UI.HelpOverlay->SetAlpha(255);
				UI.HelpOverlay->PutImage(SDLHandler);
			}
			// press escape to go to main menu.
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				GameDatas.CanClick = false;
				// std::cout << "escape key pressed, back to titlescreen." << std::endl;
				Goban.ResetBoardVisuals(SDLHandler);
				Game.ResetGame(GameDatas);
				UI.UpdateUIValues(GameDatas, SDLHandler);
				TransitionningOut = true;
			}
		}
		if (event.type == SDL_KEYUP)
		{
			// hide help when h released.
			if (event.key.keysym.sym == SDLK_h)
			{
				UI.HelpOverlay->SetAlpha(0);
				UI.HelpOverlay->PutImage(SDLHandler);
			}
		}
		GameDatas.CanClick = true;
	}
}
