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
	if (!ImagesLoaded)
	{
		LoadImages(SDLHandler);
		PlaceImagesOnStart(SDLHandler);
		ImagesLoaded = true;
	}
	DisplayImages(SDLHandler);

	// Game turn stages:
	// attendre player move// 
	// move authorized ??
	// update board
	// check captures
	// p2 plays. Start IA timer.
	// update board.
	// check captures.
}

// ------------------------------------------------------------	//
//																//
//	Methods of the scene										//
//																//
// ------------------------------------------------------------	//

void	InGameController::LoadImages(SDLHandler &SDLHandler)
{
	GobanImg = new GameImage(SDLHandler, "./ressources/img/in_game/goban.bmp");
	InGameBgImg = new GameImage(SDLHandler, "./ressources/img/in_game/in_game_bg.bmp");
	InGameTitleImg = new GameImage(SDLHandler, "./ressources/img/in_game/in_game_title.bmp");
	GameModeCaseImg = new GameImage(SDLHandler, "./ressources/img/in_game/info_back.bmp");
	GameModeText = new GameText(SDLHandler, "Playing game...", 200);
}

void	InGameController::DisplayImages(SDLHandler &SDLHandler)
{
	InGameBgImg->FadeIn();
	InGameBgImg->PutImage(SDLHandler);
	GobanImg->FadeIn();
	GobanImg->PutImage(SDLHandler);
	InGameTitleImg->FadeIn();
	InGameTitleImg->PutImage(SDLHandler);
	GameModeCaseImg->FadeIn();
	GameModeCaseImg->PutImage(SDLHandler);
	GameModeText->FadeIn();
	GameModeText->PutText(SDLHandler);
}

void InGameController::PlaceImagesOnStart(SDLHandler &SDLHandler)
{
	InGameBgImg->SetImgPos(0, 0);
	InGameBgImg->SetImgSize(1920, 1080);
	InGameBgImg->SetAlpha(0);

	GobanImg->SetImgPos(420, 0);
	GobanImg->SetImgSize(1080, 1080);
	GobanImg->SetAlpha(0);
	GobanImg->PutImage(SDLHandler);

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
