#include "../includes/Gomoku.hpp"

/*
** ---------------- BONUS ----------------
** #01 - menu (touche ESC)
** #02 - changement profondeur
** #03 - coup precedent (touche DELETE)
** #04 - affichage raisonnement (terminal)
** #05 - abandon de partie et retry (touche R)
** #06 - rejouer apres une victoire (touche RETURN)
** #07 - aucune fuite memoire.
*/

int		main(void)
{
	MainController	MainController;

	MainController.InitGomoku();
	MainController.MainLoop();
	return 0;
}

