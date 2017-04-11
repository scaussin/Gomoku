#ifndef MAINMENUCONTROLLER_HPP
# define MAINMENUCONTROLLER_HPP

# include "Gomoku.hpp"

/*
**	Class for controlling the "MAIN_MENU" scene.
*/

class MainMenuController
{
	public:
		MainMenuController();
		~MainMenuController();
	
		// class variables
		GameImage		*bg_1;
		GameImage		*title_1;

		GameImage		*btn_play_ia;
		GameImage		*btn_play_p2;
		GameImage		*btn_quit;

		GameImage		*credits;

		GameImage		*on_hover;

		// Main menu scene states
		bool			ImagesPlaced;


		// class methods.
		void		LoadImages(SDLHandler &SDLHandler);
		void		DisplayImages(SDLHandler &SDLHandler);
		void		PlaceImagesOnStart(SDLHandler &SDLHandler);
};

#endif
