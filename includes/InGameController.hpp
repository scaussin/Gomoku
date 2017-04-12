#ifndef INGAMECONTROLLER_HPP
# define INGAMECONTROLLER_HPP

#include "Gomoku.hpp"

class InGameController
{
	public:
		InGameController();
		~InGameController();
	
		// class variables
		bool		ImagesLoaded;
		bool		ImagesDisplayed;

		// images
		GameImage	*GobanImg;
		GameImage	*InGameBgImg;
		GameImage	*InGameTitleImg;

		GameImage	*GameModeCaseImg;
		GameText	*GameModeText;

		// class methods
		void		GameHandle(t_GameDatas &Game, SDLHandler &SDLHandler);
		void		LoadImages(SDLHandler &SDLHandler);
		void		PlaceImagesOnStart(SDLHandler &SDLHandler);
		void		DisplayImages(SDLHandler &SDLHandler);
};

#endif
