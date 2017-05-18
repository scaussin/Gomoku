#include "../includes/Gomoku.hpp"

MainMenuController::MainMenuController() :
	ImagesPlaced(false),
	TransitionningOut(false),
	TransitionEnd(false)
{

}

MainMenuController::~MainMenuController()
{

}


// ------------------------------------------------------------	//
//																//
//	Init methods for the main menu scene						//
//																//
// ------------------------------------------------------------	//
/*
**	Before we actually see the main menu, we load and stock
**	the images we will need.
**	This is a preload method.
*/

void	MainMenuController::LoadImages(SDLHandler &SDLHandler)
{
	bg_1 = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_bg.bmp");
	title_1 = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_title_1.bmp");
	btn_play_ia = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_btn_play_ia.bmp");
	btn_play_p2 = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_btn_play_p2.bmp");
	btn_quit = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_btn_quit.bmp");
	depth_select_txt = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_depth_txt.bmp");
	depth_value_txt = new GameText(SDLHandler, "3", 64);
	depth_select_left_arrow = new GameImage(SDLHandler, "./ressources/img/main_menu/arrow_left.bmp");
	depth_select_right_arrow = new GameImage(SDLHandler, "./ressources/img/main_menu/arrow_right.bmp");
	credits = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_credit_txt.bmp");
	on_hover = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_hover_selected.bmp");
}

/*
**	Here, we will put our image on the sdl screen buffer.
**	Used in the game's main loop.
*/

void	MainMenuController::DisplayImages(SDLHandler &SDLHandler)
{
	if (ImagesPlaced == false)
	{
		ImagesPlaced = true;
		PlaceImagesOnStart(SDLHandler);
	}
	// everything being hidden, we will make em appear.
	bg_1->FadeIn();
	bg_1->PutImage(SDLHandler);

	title_1->FadeIn();
	title_1->PutImage(SDLHandler);

	btn_play_ia->FadeIn();
	btn_play_ia->PutImage(SDLHandler);

	btn_play_p2->FadeIn();
	btn_play_p2->PutImage(SDLHandler);

	btn_quit->FadeIn();
	btn_quit->PutImage(SDLHandler);

	depth_select_txt->FadeIn();
	depth_select_txt->PutImage(SDLHandler);

	depth_value_txt->FadeIn();
	depth_value_txt->PutText(SDLHandler);

	depth_select_left_arrow->FadeIn();
	depth_select_left_arrow->PutImage(SDLHandler);

	depth_select_right_arrow->FadeIn();
	depth_select_right_arrow->PutImage(SDLHandler);

	credits->FadeIn();
	credits->PutImage(SDLHandler);
}

void	MainMenuController::PlaceImagesOnStart(SDLHandler &SDLHandler)
{
	// Put every image of the scene on the screen, but hidden.
	bg_1->SetImgPos(0, 0);
	bg_1->SetImgSize(1920, 1080);
	bg_1->SetAlpha(0);
	bg_1->PutImage(SDLHandler);

	title_1->SetImgPos(655, 140);
	title_1->SetImgSize(600, 125);
	title_1->SetAlpha(0);
	title_1->PutImage(SDLHandler);

	btn_play_ia->SetImgPos(655, 380);
	btn_play_ia->SetImgSize(600, 125);
	btn_play_ia->SetAlpha(0);
	btn_play_ia->PutImage(SDLHandler);

	on_hover->SetImgPos(750, 402);
	on_hover->SetImgSize(80, 80);
	on_hover->SetAlpha(0);
	on_hover->PutImage(SDLHandler);

	btn_play_p2->SetImgPos(655, 490);
	btn_play_p2->SetImgSize(600, 125);
	btn_play_p2->SetAlpha(0);
	btn_play_p2->PutImage(SDLHandler);

	btn_quit->SetImgPos(655, 650);
	btn_quit->SetImgSize(600, 125);
	btn_quit->SetAlpha(0);
	btn_quit->PutImage(SDLHandler);

	depth_select_txt->SetImgPos(1730, 520);
	depth_select_txt->SetImgSize(148, 47);
	depth_select_txt->SetAlpha(0);
	depth_select_txt->PutImage(SDLHandler);

	depth_value_txt->SetTextPos(1795, 600);
	depth_value_txt->SetTextSize(34, 57);
	depth_value_txt->SetAlpha(255);
	depth_value_txt->PutText(SDLHandler);

	depth_select_left_arrow->SetImgPos(1725, 600);
	depth_select_left_arrow->SetImgSize(33, 66);
	depth_select_left_arrow->SetAlpha(0);
	depth_select_left_arrow->PutImage(SDLHandler);

	depth_select_right_arrow->SetImgPos(1860, 600);
	depth_select_right_arrow->SetImgSize(33, 68);
	depth_select_right_arrow->SetAlpha(0);
	depth_select_right_arrow->PutImage(SDLHandler);

	credits->SetImgPos(1640, 840);
	credits->SetImgSize(250, 182);
	credits->SetAlpha(0);
	credits->PutImage(SDLHandler);
}

// ------------------------------------------------------------	//
//																//
//	Methods of the scene's events								//
//																//
// ------------------------------------------------------------	//

void	MainMenuController::HandleEvents(t_GameDatas &GameDatas, SDL_Event &event,
			SDLHandler &SDLHandler)
{
	(void)SDLHandler;
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (btn_play_ia->IsColliding(event.button.x,
						event.button.y))
			{
				std::cout << "Onclick play ia" << std::endl;
				GameDatas.SelectedGameMode = VS_IA;
				GameDatas.SelectedScene = IN_GAME;
				TransitionningOut = true;  // give the order to change scene.
			}
			else if (btn_play_p2->IsColliding(event.button.x,
						event.button.y))
			{
				std::cout << "Onclick play p2" << std::endl;
				GameDatas.SelectedGameMode = VS_P2;
				GameDatas.SelectedScene = IN_GAME;
				TransitionningOut = true; // give the order to change scene.
			}
			else if (btn_quit->IsColliding(event.button.x,
						event.button.y))
			{
				std::cout << "Onclick quit" << std::endl;
				SDL_Quit();
				exit (0);
			}
			else if (depth_select_left_arrow->IsColliding(event.button.x,
						event.button.y))
			{
				// std::cout << "Onclick lower IA DEPTH" << std::endl;
				if (GameDatas.IA_Depth > MIN_DEPTH)
					GameDatas.IA_Depth -= 1; 
				depth_value_txt->SetText(SDLHandler, std::to_string(GameDatas.IA_Depth));
				depth_value_txt->PutText(SDLHandler);
			}
			else if (depth_select_right_arrow->IsColliding(event.button.x,
						event.button.y))
			{
				// std::cout << "Onclick up IA DEPTH" << std::endl;
				if (GameDatas.IA_Depth < MAX_DEPTH)
					GameDatas.IA_Depth += 1;
				depth_value_txt->SetText(SDLHandler, std::to_string(GameDatas.IA_Depth));
				depth_value_txt->PutText(SDLHandler);
			}

		}
	}
}

/*
**	For each hoverable button, will check if the mouse is on it.
**	If it is, displace the hover cursor and make it appear.
*/

void	MainMenuController::CheckHover(SDLHandler &SDLHandler)
{
	SDL_GetMouseState(&MouseX, &MouseY);
	if (btn_play_ia->IsColliding(MouseX, MouseY))
	{
		on_hover->SetImgPos(750, 402);
		on_hover->SetAlpha(255);
	}
	else if (btn_play_p2->IsColliding(MouseX, MouseY))
	{
		on_hover->SetImgPos(700, 512);
		on_hover->SetAlpha(255);
	}
	else if (btn_quit->IsColliding(MouseX, MouseY))
	{
		on_hover->SetImgPos(760, 672);
		on_hover->SetAlpha(255);
	}
	else
	{
		on_hover->SetAlpha(0);
	}
	on_hover->PutImage(SDLHandler);
}

void	MainMenuController::TransitionOut(SDLHandler &SDLHandler)
{
	bg_1->FadeOut();
	bg_1->PutImage(SDLHandler);
	title_1->FadeOut();
	title_1->PutImage(SDLHandler);
	btn_play_ia->FadeOut();
	btn_play_ia->PutImage(SDLHandler);
	btn_play_p2->FadeOut();
	btn_play_p2->PutImage(SDLHandler);
	btn_quit->FadeOut();
	btn_quit->PutImage(SDLHandler);
	credits->FadeOut();
	credits->PutImage(SDLHandler);
	if (bg_1->GetAlpha() == 0
		&& title_1->GetAlpha() == 0
		&& btn_play_ia->GetAlpha() == 0
		&& btn_play_p2->GetAlpha() == 0
		&& btn_quit->GetAlpha() == 0
		&& credits->GetAlpha() == 0)
	{
		TransitionEnd = true;
	}

}
