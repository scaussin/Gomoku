/*
**	Global Gomoku hpp
*/

#ifndef GOMOKU_HPP
# define GOMOKU_HPP

// General includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iterator>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <sstream>
# include <fcntl.h>
# include <list>
# include <vector>
# include <string>
# include <queue> 
# include <regex>
# include <random>
# include <algorithm>
# include <math.h>

# include <SDL2/SDL.h>

// color in text;
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define KRESET "\x1B[0m"

/*
**	Game defines
*/

typedef enum 	e_GameStage
{
	MAIN_MENU,
	IN_GAME
}				t_GameStage;

/*
**	Gomoku structures
*/

typedef	struct	s_GameDatas
{
	
}				t_GameDatas;


// class forward declarations.

class		SDLHandler;
class		MainController;

# include "SDLHandler.hpp"
# include "MainController.hpp"


/*
**	Structure containing game datas.
*/



#endif
