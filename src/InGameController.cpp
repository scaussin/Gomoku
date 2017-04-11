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
		ImagesLoaded = true;
	}
}

void	InGameController::LoadImages(SDLHandler &SDLHandler)
{
	GobanImg = new GameImage(SDLHandler, "./ressources/img/in_game/goban.bmp");
}

void	InGameController::DisplayImages(SDLHandler &SDLHandler)
{
	(void)SDLHandler;
}
