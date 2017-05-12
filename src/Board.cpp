#include "../includes/Gomoku.hpp"

Board::Board()
{
	lastMove.y = -1;
	lastMove.x = -1;
	parent = NULL;
	isVictory = false;
	heuristic = 0;
	preheuristic = 0;
}

Board::Board(Board &rhs, Board *parent, t_vec2 move, t_Color player)
{
	*this = rhs;
	this->parent = parent;
	this->lastMove = move;
	setPoint(move, player);
}

Board::~Board()
{
	for (vector<Board *>::iterator it = next.begin() ; it != next.end() ; ++it)
	{
		delete *it;
	}
	next.clear();
}

Board			&Board::operator=(const Board& other)
{
	BlackCaptures = other.BlackCaptures;
	WhiteCaptures = other.WhiteCaptures;
	
	isVictory = false;
	heuristic = 0;
	preheuristic = 0;
	points = other.points;
	memcpy(&this->map, other.map, 19*19);
	return (*this);
}

char	Board::getPoint(t_vec2 at)
{
	if (at.y < 0 || at.y > 19 || at.x < 0 || at.x > 19)
		return (-1);
	return (map[at.y][at.x]);
}

char	Board::getPoint(int y, int x)
{
	if (y < 0 || y > 19 || x < 0 || x > 19)
		return (-1);
	return (map[y][x]);
}

bool	Board::setPoint(t_vec2 at, t_Color color)
{
	if (at.y < 0 || at.y > 19 || at.x < 0 || at.x > 19)
	{
		PERROR("t_vec2 out of range", ERR);
		cout << ": " << at.x << "x " << at.y << "y" << std::endl;
		return (false);
	}
	vector<t_vec2>::iterator it;
	for (it = points.begin() ; it != points.end(); ++it)
	{
		if (it->x == at.x && it->y == at.y)
			break;
	}
	if (it != points.end()) //exist
	{
		if (color == NONE)
			points.erase(it);
	}
	else if (color == WHITE || color == BLACK)
		points.push_back(at);

	/*::map<char *, t_vec2>::iterator it = points.find(&map[at.y][at.x]);
	if (it != points.end()) //exist
	{
		if (color == NONE)
			points.erase(it);
		else
			it->second = at;
	}
	else
		points[&map[at.y][at.x]] = at;*/
	map[at.y][at.x] = color;
	return (true);
}

bool 	Board::setPoint(int y, int x, t_Color color)
{
	if (y < 0 || y > 19 || x < 0 || x > 19)
	{
		PERROR("t_vec2 out of range", ERR);
		std::cout << ": " << x << "x " << y << "y" << std::endl;
		return (false);
	}
	vector<t_vec2>::iterator it;
	for (it = points.begin() ; it != points.end(); ++it)
	{
		if (it->x == x && it->y == y)
			break;
	}
	if (it != points.end()) //exist
	{
		if (color == NONE)
			points.erase(it);
	}
	else if (color == WHITE || color == BLACK)
	{
		t_vec2 p;
		p.y = y;
		p.x = x;
		points.push_back(p);
	}
	/*t_vec2 p;
	p.y = y;
	p.x = x;
	::map<char *, t_vec2>::iterator it = points.find(&map[y][x]);
	if (it != points.end()) //exist
	{
		if (color == NONE)
			points.erase(it);
		else
			it->second = p;
	}
	else
		points[&map[y][x]] = p;*/
	map[y][x] = color;
	return (true);
}