#include "../includes/Gomoku.hpp"

int		main(void)
{
	MainController	MainController;

	std::cout << "Hello gomoku" << std::endl;
	MainController.InitGomoku();
	MainController.MainLoop();
	return 0;
}
