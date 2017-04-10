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
		SDL_Surface		*surface;
		SDL_Texture		*bg_1_texture;
		SDL_Texture		*title_1_texture;



		// class methods.
		void		LoadImages(SDLHandler &SDLHandler);
		void		DisplayImages(SDLHandler &SDLHandler);


};

#endif
