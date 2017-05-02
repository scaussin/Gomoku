#ifndef GAMEUI_HPP
# define GAMEUI_HPP

#include "Gomoku.hpp"

class GameUI
{
	public:
		GameUI();
		~GameUI();

		GameImage	*PlayerTurnCaseImg;
		GameText	*PlayerTurnText;

		void 	LoadUI(SDLHandler &SDLHandler);
		void	PlaceImagesOnStart(SDLHandler &SDLHandler);
		
		void	DisplayUI(t_GameDatas &GameDatas, SDLHandler &SDLHandler);
		void	UpdateUI(t_GameDatas &GameDatas, SDLHandler &SDLHandler);
};

#endif
