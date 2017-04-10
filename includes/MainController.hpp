#ifndef MAIN_CONTROLLER_HPP
# define MAIN_CONTROLLER_HPP

# include "Gomoku.hpp"

/*
**	This class is the main controller for the WHOLE game.
**	This class will link all sub classes and their datas together,
**	and handle the initialization and the main loop of the game.
*/

class MainController
{
	public:
		MainController();
		~MainController();

		// This struct will stock all required game datas.
		t_GameDatas				GameDatas;

		// This Handler will take care of all SDL related calls.
		SDLHandler				SDLHandler;

		// Variable stocking which stage of the game we're in.
		t_GameStage				CurrentStage;

		// As long as we are in the main menu, this class will act.
		MainMenuController		MainMenu;

		// MainController methods.
		void			InitGomoku();
		void			MainLoop();
};

#endif
