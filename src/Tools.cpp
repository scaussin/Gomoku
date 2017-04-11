#include "../includes/Gomoku.hpp"

/*
**	Does the x y point collide with the rect ?
**	Return true if it does, false otherwise.
*/

bool		Tools::RectCollision(int x, int y, SDL_Rect rect)
{
	if (x >= rect.x && x <= rect.x + rect.w
		&& y >= rect.y && y <= rect.y + rect.h)
		return (true);
	return (false);
}
