#ifndef GAMEUI_HPP
# define GAMEUI_HPP

#include "Gomoku.hpp"

class GameUI
{
	public:
		GameUI();
		~GameUI();

		GameImage			*PlayerTurnCaseImg;
		GameText			*PlayerTurnText;

		GameImage			*IATimerCaseImg;
		GameText			*IATimerText;
		GameText			*IATimerValueText;

		GameImage			*BlackStoneImg;
		GameImage			*BlackCapturesCaseImg;
		GameText			*BlackCapturesText;
		GameText			*BlackCapturesTextValue;

		GameImage			*WhiteStoneImg;
		GameImage			*WhiteCapturesCaseImg;
		GameText			*WhiteCapturesText;
		GameText			*WhiteCapturesTextValue;

		GameImage			*VictoryCaseImg;
		GameText			*VictoryText;
		GameText			*VictorySubText;

		void				LoadUI(SDLHandler &SDLHandler);
		void				PlaceImagesOnStart(SDLHandler &SDLHandler);

		void				DisplayUI(t_GameDatas &GameDatas, SDLHandler &SDLHandler);
		void				UpdateUIValues(t_GameDatas &GameDatas, SDLHandler &SDLHandler);
};

#endif
