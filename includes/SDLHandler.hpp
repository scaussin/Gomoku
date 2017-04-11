#ifndef SDLHANDLER_HPP
# define SDLHANDLER_HPP

# include "Gomoku.hpp"

class SDLHandler
{
	public:
		SDLHandler();
		~SDLHandler();

		// class variables
		SDL_Window		*pWindow;
		SDL_Renderer	*renderer;
		SDL_Event		event;

		// class methods
		int		InitWindow();
		int		InitSDL_ttf();
		void	ClearWindow();
};

#endif
