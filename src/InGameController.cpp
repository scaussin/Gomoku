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
		LoadImages(SDLHandler);
		PlaceImagesOnStart(SDLHandler);
		Goban.InitBoard(SDLHandler);
		ImagesLoaded = true;
	}
	DisplayImages(SDLHandler);
	Goban.PutDisplay(Game, SDLHandler);


	
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

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (Goban.HandleClickEvents(GameDatas, event, SDLHandler, move) == 1)
		{
			if (GameDatas.ActivePlayer == BLACK)
			{
				std::cout << "Black tries to play move in " << move.x
				<< "x " << move.y << "y" << std::endl;
				// Is move authorized ??
				if (GameRules.IsMoveAuthorized(GameDatas, move))
				{
					// If yes, apply captures and update board 
					GameRules.CheckCaptures(GameDatas, move);
					Goban.SetPointDisplay(move.x, move.y, BLACK, SDLHandler);
					Goban.UpdateBoard(GameDatas, SDLHandler);
				}
				if (GameDatas.SelectedGameMode == VS_IA)
				{
					t_vec2 IaMove;
					// Start timer.
					IaMove = IA.DecideMove(GameDatas);
					//IaMove = IA.DecideRandomMove();
					// End timer.
					//GameRules.IsMoveAuthorized(IaMove);
					GameRules.CheckCaptures(GameDatas, IaMove);
					Goban.UpdateBoard(GameDatas, SDLHandler);
				}
				else if (GameDatas.SelectedGameMode == VS_P2)
				{
					t_vec2 IaMoveSuggestion;

					IaMoveSuggestion = IA.DecideMove(GameDatas);
					Goban.SetPointDisplay(IaMoveSuggestion.x, IaMoveSuggestion.y, SUGGESTION, SDLHandler);
					//GameDatas.ActivePlayer = WHITE;
				}
				GameRules.CheckVictory(GameDatas);
			}
		}
	}
}
