#include "../includes/Gomoku.hpp"

bool	GameRules::hasDoubleThree(Board &board, t_Color color, t_vec2 move)
{
	(void)board;
	(void)color;
	(void)move;

	int				dir;
	int				nb_free_3;
	std::string		doublon_mask;

	dir = 1;
	nb_free_3 = 0;
	while (dir != 9)
	{
		if (color == BLACK)
		{
			nb_free_3 += checkDoubleThreeBlackPatterns(board, move, (t_dir)dir);
		}
		else
		{
			nb_free_3 += checkDoubleThreeWhitePatterns(board, move, (t_dir)dir);
		}
		dir++;
	}
	std::cout << "Found " << nb_free_3 << " free three(s)." << std::endl;
	if (nb_free_3 >= 2)
	{
		return (true);
	}
	return (false);
}

/*
**	Optimization todo if needed: load the patterns before checking them here.
*/

int		GameRules::checkDoubleThreeBlackPatterns(Board &board, t_vec2 move, t_dir dir)
{
	std::string		line;
	std::string		backLine;
	int				ret = 0;

	// For each direction from the given point.
	line = Tools::GetPointsLine(board, move, dir, 5);
	// and for each REVERSE direction.
	backLine = Tools::GetPointsLine(board, move, Tools::GetOppositeDir(dir), 5);
	//std::cout << "dir " << dir << "cases = " << line << std::endl;
	// The simplest free three : 01110 start or end pos.
	if (strncmp(line.c_str(), "0110", 4) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0)
	{
		ret += 1;
	}
	// free three : 01110 middle pos - can only happen on half the rotation -> symetric form.
	else if (strncmp(line.c_str(), "010", 3) == 0
		&& strncmp(backLine.c_str(), "010", 3) == 0)
	{
		if (dir < BOTTOM_RIGHT)
			ret += 1;
		else
			std::cout << KMAG "DOUBLON FREE THREE - not counted" KRESET << std::endl;
	}
	// second free three : 010110 start pos
	else if  (strncmp(line.c_str(), "00110", 5) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0) 
	{
		// the reverse free tree cant happen on the same line, its defendable.
		if (strncmp(backLine.c_str(), "00110", 5) != 0)
			ret += 1;
		else
			std::cout << KMAG "REVERSED DEFENDABLE FREE THREE - not counted" KRESET << std::endl;
	}
	// third free three : 011010 end pos
	else if (strncmp(line.c_str(), "01010", 5) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0)
	{
		ret += 1;
	}
	// thourth possibility : 011010 middle pos. one side is enough.
	// the other side will be true if it is not this one. -> not symetric form.
	else if (strncmp(line.c_str(), "0010", 3) == 0
		&& strncmp(backLine.c_str(), "010", 3) == 0)
	{
		ret += 1;
	}
	if (ret != 0)
		std::cout << KMAG "FOUND FREE THREE: " KRESET << line << " dir " << dir << std::endl;
	return (ret);
}

int		GameRules::checkDoubleThreeWhitePatterns(Board &board, t_vec2 move, t_dir dir)
{
	std::string		line;
	std::string		backLine;
	int				ret = 0;

	// For each direction from the given point.
	line = Tools::GetPointsLine(board, move, dir, 5);
	// and for each REVERSE direction.
	backLine = Tools::GetPointsLine(board, move, Tools::GetOppositeDir(dir), 5);
	//std::cout << "dir " << dir << "cases = " << line << std::endl;
	// The simplest free three : 01110 start or end pos.
	if (strncmp(line.c_str(), "0220", 4) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0)
	{
		ret += 1;
	}
	// free three : 02220 middle pos - can only happen on half the rotation -> symetric form.
	else if (strncmp(line.c_str(), "010", 3) == 0
		&& strncmp(backLine.c_str(), "010", 3) == 0)
	{
		if (dir < BOTTOM_RIGHT)
			ret += 1;
		else
			std::cout << KMAG "DOUBLON FREE THREE - not counted" KRESET << std::endl;
	}
	// second free three : 020220 start pos
	else if  (strncmp(line.c_str(), "00220", 5) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0) 
	{
		// the reverse free tree cant happen on the same line, its defendable.
		if (strncmp(backLine.c_str(), "00220", 5) != 0)
			ret += 1;
		else
			std::cout << KMAG "REVERSED DEFENDABLE FREE THREE - not counted" KRESET << std::endl;
	}
	// third free three : 022020 end pos
	else if (strncmp(line.c_str(), "02020", 5) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0)
	{
		ret += 1;
	}
	// thourth possibility : 022020 middle pos. one side is enough.
	// the other side will be true if it is not this one. -> not symetric form.
	else if (strncmp(line.c_str(), "0020", 4) == 0
		&& strncmp(backLine.c_str(), "020", 3) == 0)
	{
		ret += 1;
	}
	if (ret != 0)
		std::cout << KMAG "FOUND FREE THREE: " KRESET << line << " dir " << dir << std::endl;
	return (ret);
}