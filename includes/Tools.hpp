#ifndef TOOLS_HPP
# define TOOLS_HPP

# include "Gomoku.hpp"

class Tools
{
	public:
		static bool		RectCollision(int x, int y, SDL_Rect Rect);
		static int		Clamp(int n, int lower, int upper);
};

#endif
