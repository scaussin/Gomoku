#include "../includes/Gomoku.hpp"

/*
**	Optimization todo if needed: load the patterns before checking them here.
*/

int		GameRules::checkDoubleThreeBlackPatterns(Board &board,
												t_vec2 move, t_dir dir,
												std::string &line, std::string &backLine)
{
	int				ret = 0;

	// broken three : 011010 end pos
	if (strncmp(line.c_str(), "01010", 5) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0)
	{
		ret += 1;
	}
	// special case -> undefendable reversed dual broken threes.
	else if (strncmp(line.c_str(), "01010", 5) == 0
		&& strncmp(backLine.c_str(), "01010", 5) == 0)
	{
		ret += 1;
	}
	// The simplest free three : 01110 start or end pos.
	else if (strncmp(line.c_str(), "0110", 4) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0)
	{
		ret += 1;
	}
	// free three : 01110 middle pos 
	else if (strncmp(line.c_str(), "010", 3) == 0
		&& strncmp(backLine.c_str(), "010", 3) == 0)
	{
		if (dir < BOTTOM_RIGHT) // - can only happen on half the rotation -> symetric form.
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

int		GameRules::checkDoubleThreeWhitePatterns(Board &board,
												t_vec2 move, t_dir dir,
												std::string &line, std::string &backLine)
{
	int				ret = 0;

	// broken three : 011010 end pos
	if (strncmp(line.c_str(), "02020", 5) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0)
	{
		ret += 1;
	}
	// special case -> undefendable reversed dual broken threes.
	else if (strncmp(line.c_str(), "02020", 5) == 0
		&& strncmp(backLine.c_str(), "02020", 5) == 0)
	{
		ret += 1;
	}
	// The simplest free three : 01110 start or end pos.
	else if (strncmp(line.c_str(), "0220", 4) == 0
		&& strncmp(backLine.c_str(), "00", 2) == 0)
	{
		ret += 1;
	}
	// free three : 02220 middle pos 
	else if (strncmp(line.c_str(), "010", 3) == 0
		&& strncmp(backLine.c_str(), "010", 3) == 0)
	{
		if (dir < BOTTOM_RIGHT) // - can only happen on half the rotation -> symetric form.
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