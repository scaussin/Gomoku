#include "../includes/Gomoku.hpp"

GameUI::GameUI()
{

}

GameUI::~GameUI()
{

}

void		GameUI::LoadUI(SDLHandler &SDLHandler)
{
	// Black or white turn display
	PlayerTurnCaseImg = new GameImage(SDLHandler, "./ressources/img/in_game/info_back.bmp");
	PlayerTurnText = new GameText(SDLHandler, "Black turn", 124);

	// IA decision timer display
	IATimerCaseImg = new GameImage(SDLHandler, "./ressources/img/in_game/info_back.bmp");
	IATimerText  = new GameText(SDLHandler, "IA time for last move:", 124);
	IATimerValueText  = new GameText(SDLHandler, "0.000s", 124);

	// Black captures display
	BlackCapturesCaseImg = new GameImage(SDLHandler, "./ressources/img/in_game/info_back.bmp");
	BlackStoneImg = new GameImage(SDLHandler, "./ressources/img/in_game/go_stone_black.bmp");
	BlackCapturesText  = new GameText(SDLHandler, "Black captures:", 124);
	BlackCapturesTextValue  = new GameText(SDLHandler, "0", 124);

	// White captures display
	WhiteCapturesCaseImg = new GameImage(SDLHandler, "./ressources/img/in_game/info_back.bmp");
	WhiteStoneImg = new GameImage(SDLHandler, "./ressources/img/in_game/go_stone_white.bmp");
	WhiteCapturesText = new GameText(SDLHandler, "White captures:", 124);
	WhiteCapturesTextValue  = new GameText(SDLHandler, "0", 124);

	// victory display
	VictoryCaseImg = new GameImage(SDLHandler, "./ressources/img/in_game/info_back.bmp");
	VictoryText = new GameText(SDLHandler, "Victory for XXXXX!", 124);
	VictorySubText = new GameText(SDLHandler, "Press Enter to reset board", 124);
}

void		GameUI::PlaceImagesOnStart(SDLHandler &SDLHandler)
{
	// Black or white turn display
	PlayerTurnCaseImg->SetImgPos(1510, 50);
	PlayerTurnCaseImg->SetImgSize(406, 142);
	PlayerTurnCaseImg->SetAlpha(0);
	PlayerTurnCaseImg->PutImage(SDLHandler);

	PlayerTurnText->SetTextPos(1580, 80);
	PlayerTurnText->SetTextSize(180, 60);
	PlayerTurnText->SetAlpha(0);
	PlayerTurnText->PutText(SDLHandler);

	// IA decision timer display
	IATimerCaseImg->SetImgPos(1510, 205);
	IATimerCaseImg->SetImgSize(406, 142);
	IATimerCaseImg->SetAlpha(0);
	IATimerCaseImg->PutImage(SDLHandler);

	IATimerText->SetTextPos(1535, 215);
	IATimerText->SetTextSize(350, 50);
	IATimerText->SetAlpha(0);
	IATimerText->PutText(SDLHandler);

	IATimerValueText->SetTextPos(1640, 265);
	IATimerValueText->SetTextSize(120, 50);
	IATimerValueText->SetAlpha(0);
	IATimerValueText->PutText(SDLHandler);

	// Black captures display
	BlackCapturesCaseImg->SetImgPos(1510, 505);
	BlackCapturesCaseImg->SetImgSize(406, 142);
	BlackCapturesCaseImg->SetAlpha(0);
	BlackCapturesCaseImg->PutImage(SDLHandler);

	BlackStoneImg->SetImgPos(1520, 515);
	BlackStoneImg->SetImgSize(56, 56);
	BlackStoneImg->SetAlpha(0);
	BlackStoneImg->PutImage(SDLHandler);

	BlackCapturesText->SetTextPos(1590, 518);
	BlackCapturesText->SetTextSize(250, 50);
	BlackCapturesText->SetAlpha(0);
	BlackCapturesText->PutText(SDLHandler);

	BlackCapturesTextValue->SetTextPos(1680, 565);
	BlackCapturesTextValue->SetTextSize(30, 50);
	BlackCapturesTextValue->SetAlpha(0);
	BlackCapturesTextValue->PutText(SDLHandler);

	// White captures display
	WhiteCapturesCaseImg->SetImgPos(1510, 705);
	WhiteCapturesCaseImg->SetImgSize(406, 142);
	WhiteCapturesCaseImg->SetAlpha(0);
	WhiteCapturesCaseImg->PutImage(SDLHandler);

	WhiteStoneImg->SetImgPos(1520, 715);
	WhiteStoneImg->SetImgSize(56, 56);
	WhiteStoneImg->SetAlpha(0);
	WhiteStoneImg->PutImage(SDLHandler);

	WhiteCapturesText->SetTextPos(1590, 718);
	WhiteCapturesText->SetTextSize(250, 50);
	WhiteCapturesText->SetAlpha(0);
	WhiteCapturesText->PutText(SDLHandler);

	WhiteCapturesTextValue->SetTextPos(1680, 765);
	WhiteCapturesTextValue->SetTextSize(30, 50);
	WhiteCapturesTextValue->SetAlpha(0);
	WhiteCapturesTextValue->PutText(SDLHandler);

	// Victory display
	VictoryCaseImg->SetImgPos(10, 600);
	VictoryCaseImg->SetImgSize(406, 142);
	VictoryCaseImg->SetAlpha(255);
	VictoryCaseImg->PutImage(SDLHandler);

	VictoryText->SetTextPos(30, 610);
	VictoryText->SetTextSize(350, 60);
	VictoryText->SetAlpha(255);
	VictoryText->PutText(SDLHandler);

	VictorySubText->SetTextPos(35, 665);
	VictorySubText->SetTextSize(330, 45);
	VictorySubText->SetAlpha(255);
	VictorySubText->PutText(SDLHandler);
}

void		GameUI::UpdateUIValues(t_GameDatas &GameDatas, SDLHandler &SDLHandler)
{
	BlackCapturesTextValue->SetText(SDLHandler, std::to_string(GameDatas.Board.BlackCaptures));
	WhiteCapturesTextValue->SetText(SDLHandler, std::to_string(GameDatas.Board.WhiteCaptures));
	IATimerValueText->SetText(SDLHandler, std::to_string(GameDatas.LastTurnIATime) + " ms");
}

void		GameUI::DisplayUI(t_GameDatas &GameDatas, SDLHandler &SDLHandler)
{
	// Black or white turn display
	if (PlayerTurnCaseImg->GetAlpha() < 255)
		PlayerTurnCaseImg->FadeIn();
	PlayerTurnCaseImg->PutImage(SDLHandler);
	if (PlayerTurnText->GetAlpha() < 255)
		PlayerTurnText->FadeIn();
	PlayerTurnText->PutText(SDLHandler);

	// IA decision timer display
	if (IATimerCaseImg->GetAlpha() < 255)
		IATimerCaseImg->FadeIn();
	IATimerCaseImg->PutImage(SDLHandler);
	if (IATimerText->GetAlpha() < 255)
		IATimerText->FadeIn();
	IATimerText->PutText(SDLHandler);
	if (IATimerValueText->GetAlpha() < 255)
		IATimerValueText->FadeIn();
	IATimerValueText->PutText(SDLHandler);

	// Black captures display
	if (BlackCapturesCaseImg->GetAlpha() < 255)
		BlackCapturesCaseImg->FadeIn();
	BlackCapturesCaseImg->PutImage(SDLHandler);
	if (BlackStoneImg->GetAlpha() < 255)
		BlackStoneImg->FadeIn();
	BlackStoneImg->PutImage(SDLHandler);
	if (BlackCapturesText->GetAlpha() < 255)
		BlackCapturesText->FadeIn();
	BlackCapturesText->PutText(SDLHandler);
	if (BlackCapturesTextValue->GetAlpha() < 255)
		BlackCapturesTextValue->FadeIn();
	BlackCapturesTextValue->PutText(SDLHandler);

	// White captures display
	if (WhiteCapturesCaseImg->GetAlpha() < 255)
		WhiteCapturesCaseImg->FadeIn();
	WhiteCapturesCaseImg->PutImage(SDLHandler);
	if (WhiteStoneImg->GetAlpha() < 255)
		WhiteStoneImg->FadeIn();
	WhiteStoneImg->PutImage(SDLHandler);
	if (WhiteCapturesText->GetAlpha() < 255)
		WhiteCapturesText->FadeIn();
	WhiteCapturesText->PutText(SDLHandler);
	if (WhiteCapturesTextValue->GetAlpha() < 255)
		WhiteCapturesTextValue->FadeIn();
	WhiteCapturesTextValue->PutText(SDLHandler);

	// Victory display
	if (VictoryCaseImg->GetAlpha() < 255)
		VictoryCaseImg->FadeIn();
	VictoryCaseImg->PutImage(SDLHandler);
	if (VictoryText->GetAlpha() < 255)
		VictoryText->FadeIn();
	VictoryText->PutText(SDLHandler);
	if (VictorySubText->GetAlpha() < 255)
		VictorySubText->FadeIn();
	VictorySubText->PutText(SDLHandler);
}
