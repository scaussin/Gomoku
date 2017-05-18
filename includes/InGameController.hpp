#ifndef INGAMECONTROLLER_HPP
# define INGAMECONTROLLER_HPP

#include "Gomoku.hpp"

class InGameController
{
	public:
		InGameController();
		~InGameController();
	
		// class controllers
		GobanController		Goban; // control interactions between go board and players

		GameController		Game;

		GameUI				UI;

		// class variables
		bool				ImagesLoaded;

		// images
		GameImage			*InGameBgImg;
		GameImage			*InGameTitleImg;

		GameImage			*GameModeCaseImg;
		GameText			*GameModeText;

		bool				TransitionningOut;
		bool				TransitionEnd;

		// class methods
		void		GameHandle(t_GameDatas &Game, SDLHandler &SDLHandler);
		void		LoadImages(SDLHandler &SDLHandler);
		void		PlaceImagesOnStart(SDLHandler &SDLHandler);
		void		DisplayImages(SDLHandler &SDLHandler);
		void		HandleEvents(t_GameDatas &GameDatas, SDL_Event &event,
						SDLHandler &SDLHandler);
		void		TransitionOut(SDLHandler &SDLHandler);
};

#endif
