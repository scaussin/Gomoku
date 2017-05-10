#include "../includes/Gomoku.hpp"

int		main(void)
{
	MainController	MainController;

	MainController.InitGomoku();
	MainController.MainLoop();
	return 0;
}

