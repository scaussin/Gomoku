#include "../includes/Gomoku.hpp"

GameUI::GameUI()
{

}

GameUI::~GameUI()
{

}

void		GameUI::LoadUI(SDLHandler &SDLHandler)
{
	PlayerTurnCaseImg = new GameImage(SDLHandler, "./ressources/img/in_game/info_back.bmp");
	PlayerTurnText = new GameText(SDLHandler, "Black turn", 1024);
}

void		GameUI::PlaceImagesOnStart(SDLHandler &SDLHandler)
{
	PlayerTurnCaseImg->SetImgPos(100, 100);
	PlayerTurnCaseImg->SetImgSize(406, 142);
	PlayerTurnCaseImg->SetAlpha(255);
	PlayerTurnCaseImg->PutImage(SDLHandler);

	PlayerTurnText->SetTextPos(140, 130);
	PlayerTurnText->SetTextSize(200, 60);
	PlayerTurnText->SetAlpha(255);
	PlayerTurnText->PutText(SDLHandler);
}

void		GameUI::UpdateUI(t_GameDatas &GameDatas, SDLHandler &SDLHandler)
{

}

void		GameUI::DisplayUI(t_GameDatas &GameDatas, SDLHandler &SDLHandler)
{
	if (PlayerTurnCaseImg->GetAlpha() < 255)
	{
		PlayerTurnCaseImg->FadeIn();
	}
	PlayerTurnCaseImg->PutImage(SDLHandler);
	if (PlayerTurnText->GetAlpha() < 255)
	{
		PlayerTurnText->FadeIn();
	}
	PlayerTurnText->PutText(SDLHandler);
}
