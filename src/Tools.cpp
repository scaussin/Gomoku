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

/*
**	to clamp, you give a value, a min and a max.
**	the value n will never be greater or smaller
**	than those max and min.
*/

int			Tools::Clamp(int n, int lower, int upper)
{
	return std::max(lower, std::min(n, upper));
}

/*
**	This method will look x points from the given point
**	in the given direction and return the points' values.
**	It will return back a string with the values in it.
**	It will give back x characters.
**
**	For example : "00121"
**	0 being the value for the NONE color, 1 being BLACK,
**	and 2 being WHITE.
*/


/*
**	Ths version gets the values on a line WITHOUT converting the color white to black.
**	-> not for PATTERN checking, but for VALUE checking.
*/

void		Tools::GetPointsLine(char *line, Board &board, t_vec2 &point,
				t_dir dir, int nb_points)
{
	static int				mod_x;
	static int				mod_y;
	static int				x_watch;
	static int				y_watch;
	static int				i;

	// we set the modifiers to move on our line.
	SetMoveModifiers(mod_x, mod_y, dir);
	// we look into the asked number of point to make our line
	for (i = 0; i != nb_points; ++i)
	{
		y_watch = point.y + mod_y * i;
		x_watch = point.x + mod_x * i;
		// we dont want to look out of the board.
		if (y_watch >= 0 && y_watch < 19
			&& x_watch >= 0 && x_watch < 19)
		{
			if (board.map[y_watch][x_watch] == 1)
				line[i] = '1';	// black
			else if (board.map[y_watch][x_watch] == 2)
				line[i] = '2';	// white
			else 
				line[i] = '0';	// none.
		}
		else
		{
			line[i] = 0; // out of board.
			return ;
		}
	}
}

/*
**	For a given point and direction, fill the line with the values, converting
**	white to black and black to white IF we are currently being white.
*/

void		Tools::GetPatternPointsLine(char *line, Board &board, t_vec2 &point,
				t_dir dir, int nb_points, t_Color color)
{
	static int				mod_x;
	static int				mod_y;
	static int				x_watch;
	static int				y_watch;
	static int				i;

	// we set the modifiers to move on our line.
	SetMoveModifiers(mod_x, mod_y, dir);
	// we look into the asked number of point to make our line
	for (i = 0; i != nb_points; ++i)
	{
		y_watch = point.y + mod_y * i;
		x_watch = point.x + mod_x * i;
		// we dont want to look out of the board.
		if (y_watch >= 0 && y_watch < 19
			&& x_watch >= 0 && x_watch < 19)
		{
			if (board.map[y_watch][x_watch] == 1) // black
			{
				if (color == BLACK)
					line[i] = '1';
				else
					line[i] = '2';
			}
			else if (board.map[y_watch][x_watch] == 2) // white
			{
				if (color == BLACK)
					line[i] = '2';
				else
					line[i] = '1';
			}
			else 
				line[i] = '0';
		}
		else
		{
			line[i] = 0;
			return ;
		}
	}
}

/*
**	Get the lines of values in both directions -> only one call.
*/

void				Tools::GetDualPatternPointsLine(char *line, char *BackLine, Board &board, t_vec2 &point,
									t_dir dir, int nb_points, t_Color color)
{
	static int				mod_x;
	static int				mod_y;
	static int				x_watch;
	static int				y_watch;
	static int				i;

	// we set the modifiers to move on our line.
	SetMoveModifiers(mod_x, mod_y, dir);
	// we look into the asked number of point to make our line
	for (i = 0; i != nb_points; ++i)
	{
		y_watch = point.y + mod_y * i;
		x_watch = point.x + mod_x * i;
		// we dont want to look out of the board.
		if (y_watch >= 0 && y_watch < 19
			&& x_watch >= 0 && x_watch < 19)
		{
			if (board.map[y_watch][x_watch] == 1) // black
			{
				if (color == BLACK)
					line[i] = '1';
				else
					line[i] = '2';
			}
			else if (board.map[y_watch][x_watch] == 2) // white
			{
				if (color == BLACK)
					line[i] = '2';
				else
					line[i] = '1';
			}
			else 
				line[i] = '0';
		}
		else
		{
			line[i] = 0;
		}
		// reverse side.
		y_watch = point.y - mod_y * i;
		x_watch = point.x - mod_x * i;
		if (y_watch >= 0 && y_watch < 19
			&& x_watch >= 0 && x_watch < 19)
		{
			if (board.map[y_watch][x_watch] == 1) // black
			{
				if (color == BLACK)
					BackLine[i] = '1';
				else
					BackLine[i] = '2';
			}
			else if (board.map[y_watch][x_watch] == 2) // white
			{
				if (color == BLACK)
					BackLine[i] = '2';
				else
					BackLine[i] = '1';
			}
			else 
				BackLine[i] = '0';
		}
		else
		{
			BackLine[i] = 0;
		}
	}

}

void		Tools::ReversePatternColors(char *line, char *backLine, int nb_points)
{
	static int i = 0;

	for (i = 0; i != nb_points; ++i)
	{
		if (line[i] == '1')
			line[i] = '2';
		else if (line[i] == '2')
			line[i] = '1';
		if (backLine[i] == '1')
			backLine[i] = '2';
		else if (backLine[i] == '2')
			backLine[i] = '1';
	}
}

void		Tools::ReversePatternColorsOneLine(char *line, int nb_points)
{
	static int i = 0;

	for (i = 0; i != nb_points; ++i)
	{
		if (line[i] == '1')
			line[i] = '2';
		else if (line[i] == '2')
			line[i] = '1';
	}
}

/*
**	We take two ints, and we set them according to the direction.
**	With these ints, we can move in a given direction as many time
**	as we wish.
*/

void		Tools::SetMoveModifiers(int &mod_x, int &mod_y, t_dir dir)
{
	if (dir == CURRENT)
	{
		mod_x = 0;
		mod_y = 0;
	}
	else if (dir == TOP_LEFT)
	{
		mod_x = -1;
		mod_y = 1;
	}
	else if (dir == TOP)
	{
		mod_x = 0;
		mod_y = 1;
	}
	else if (dir == TOP_RIGHT)
	{
		mod_x = 1;
		mod_y = 1;
	}
	else if (dir == RIGHT)
	{
		mod_x = 1;
		mod_y = 0;
	}
	else if (dir == BOTTOM_RIGHT)
	{
		mod_x = 1;
		mod_y = -1;
	}
	else if (dir == BOTTOM)
	{
		mod_x = 0;
		mod_y = -1;
	}
	else if (dir == BOTTOM_LEFT)
	{
		mod_x = -1;
		mod_y = -1;
	}
	else if (dir == LEFT)
	{
		mod_x = -1;
		mod_y = 0;
	}
}

void	Tools::printError(string file, int line, string function, string msg, int errorLevel)
{
	if (errorLevel == ERR)
	{
		cout << "\e[41m[ERROR]\e[0m " << file << ":" << line << " in " << function << "()" << endl << "\t" << msg << endl;
		exit(1);
	}
	else if (errorLevel == WARN)
		cout << "\e[43m[WARNING]\e[0m " << file << ":" << line << " in " << function << "()" << endl << "\t" << msg << endl;
	else
		cout << "\e[44m[INFO]\e[0m " << file << ":" << line << " in " << function << "()" << endl << "\t" << msg << endl;
	//printf ("[ERROR]\n\t%s:%d (%s) -> %s\n", file.c_str(), line, function.c_str(), msg.c_str());
}

t_Color	Tools::inverseColorPlayer(t_Color player)
{
	if (player == BLACK)
		return (WHITE);
	else if (player == WHITE)
		return (BLACK);
	PERROR("not expected t_Color", ERR);
	return (NONE);
}

t_dir	Tools::GetOppositeDir(t_dir dir)
{
	if (dir == CURRENT)
		return (CURRENT);
	else if (dir == TOP_LEFT)
		return (BOTTOM_RIGHT);
	else if (dir == TOP)
		return (BOTTOM);
	else if (dir == TOP_RIGHT)
		return (BOTTOM_LEFT);
	else if (dir == RIGHT)
		return (LEFT);
	else if (dir == BOTTOM_RIGHT)
		return (TOP_LEFT);
	else if (dir == BOTTOM)
		return (TOP);
	else if (dir == BOTTOM_LEFT)
		return (TOP_RIGHT);
	else if (dir == LEFT)
		return (RIGHT);
	else
		return (CURRENT);
}

std::string		Tools::printColor(t_Color color)
{
	if (color == BLACK)
		return ("BLACK");
	else if (color == WHITE)
		return ("WHITE");
	else if (color == SUGGESTION)
		return ("SUGGESTION");
	return ("NONE");
}
