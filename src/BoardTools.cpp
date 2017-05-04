#include "../includes/Gomoku.hpp"

t_Color		BoardTools::GetPointValue(Board &board, t_vec2 coord)
{
	return ((t_Color)(board.map[coord.y][coord.x]));
}

t_Color		BoardTools::GetPointValue(Board &board, int x, int y)
{
	return ((t_Color)(board.map[y][x]));
}

void		BoardTools::SetPointValue(Board &board, t_vec2 coord, t_Color newVal)
{
	board.map[coord.y][coord.x] = newVal;
}

void		BoardTools::SetPointValue(Board &board, int x, int y, t_Color newVal)
{
	board.map[y][x] = newVal;
}

/*
**	Simple check: is the point in the board ? -> segfault avoid;
*/

bool		BoardTools::IsPointIn(const t_vec2 point)
{
	if (point.x < 0 || point.x > 18 || point.y < 0 || point.y > 18)
		return false;
	return true;
}

/*
**	Print the board in the terminal. Black are O, White are X.
*/

void		BoardTools::DisplayBoardChars(Board &board)
{
	int			x = 0;
	int			y = 18;
	t_Color		value;

	for (; y != -1; y--)
	{
		for (x = 0; x < 19; x++)
		{
			value = (t_Color)board.map[y][x];
			if (value == NONE)
				cout << "◯ ";
			else if (value == BLACK)
			{
				if (board.lastMove.y == y && board.lastMove.x == x)
					cout << "\e[4m⚫ \e[24m";
				else
					cout << "⚫ ";
			}
			else if (value == WHITE)
			{
				if (board.lastMove.y == y && board.lastMove.x == x)
					cout << "\e[4m⚪ \e[24m";
				else
					cout << "⚪ ";
			}
		}
		cout << endl;
	}
}

/*
**	Are those two board identical ? true or false.
*/

bool		BoardTools::IsIdentical(const Board &board_a, const Board &board_b)
{
	static int			x;
	static int			y;

	for (y = 18; y != -1; y--)
	{
		for(x = 0; x < 19; x++)
		{
			if (board_a.map[y][x] != board_b.map[y][x])
				return (false);
		}
	}
	return (true);
}

/*
**	Is that board in that list of board?
*/

bool		BoardTools::IsInList(const Board &board, std::vector<Board*> &boardList)
{
	static int i = 0;
	static int size;

	size = boardList.size();
	i = 0;
	while (i != size)
	{
		if (IsIdentical(board, *boardList[i]))
			return (true);
		i++;
	}
	return (false);
}

int		BoardTools::countChild(Board *board)
{
	static int i;

	i = 0;
	for (std::vector<Board *>::iterator it = board->next.begin(); it != board->next.end() ; ++it)
	{
		i += BoardTools::countChild(*it);
	}
	return (i + 1);
}

void	BoardTools::printParents(Board *board)
{
	if (board && board->parent)
	{
		BoardTools::printParents(board->parent);
	}
	cout << "--------------------" << endl << "heuristic: " << board->heuristic << endl;
	BoardTools::DisplayBoardChars(*board);
	cout << endl;
}

t_vec2	BoardTools::getFistMove(Board *board)
{
	if (board && board->parent && board->parent->parent == NULL)
	{
		return (board->lastMove);
	}
	else if (board && board->parent)
		return (BoardTools::getFistMove(board->parent));
	t_vec2 err;
	PERROR("last move not found", ERR);
	return (err);
}