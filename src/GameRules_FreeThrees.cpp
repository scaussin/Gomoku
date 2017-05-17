#include "../includes/Gomoku.hpp"

/*
**	Optimization todo if needed: load the patterns before checking them here.
*/

int		GameRules::checkDoubleThreePatterns(Board &board,
												t_vec2 move, t_dir dir,
												char *line, char *backLine)
{
	int				ret = 0;

	// broken three : 011010 end pos
	if (strncmp(line, "01010", 5) == 0
		&& strncmp(backLine, "00", 2) == 0)
	{
		ret += 1;
	}
	// special case -> undefendable reversed dual broken threes.
	else if (strncmp(line, "01010", 5) == 0
		&& strncmp(backLine, "01010", 5) == 0)
	{
		ret += 1;
	}
	// The simplest free three : 01110 start or end pos.
	else if (strncmp(line, "0110", 4) == 0
		&& strncmp(backLine, "00", 2) == 0)
	{
		ret += 1;
	}
	// free three : 01110 middle pos 
	else if (strncmp(line, "010", 3) == 0
		&& strncmp(backLine, "010", 3) == 0)
	{
		if (dir < BOTTOM_RIGHT) // - can only happen on half the rotation -> symetric form.
			ret += 1;
		// else
			// std::cout << KMAG "DOUBLON FREE THREE - not counted" KRESET << std::endl;
	}
	// second free three : 010110 start pos
	else if  (strncmp(line, "00110", 5) == 0
		&& strncmp(backLine, "00", 2) == 0) 
	{
		// the reverse free tree cant happen on the same line, its defendable.
		if (strncmp(backLine, "00110", 5) != 0)
			ret += 1;
		// else
			// std::cout << KMAG "REVERSED DEFENDABLE FREE THREE - not counted" KRESET << std::endl;
	}
	// thourth possibility : 011010 middle pos. one side is enough.
	// the other side will be true if it is not this one. -> not symetric form.
	else if (strncmp(line, "0010", 4) == 0
		&& strncmp(backLine, "010", 3) == 0)
	{
		ret += 1;
	}
	// if (ret != 0)
		// std::cout << KMAG "FOUND FREE THREE: " KRESET << line << " dir " << dir << std::endl;
	return (ret);
}
