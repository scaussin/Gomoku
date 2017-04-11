#include "../includes/Gomoku.hpp"

MainMenuController::MainMenuController()
{

}

MainMenuController::~MainMenuController()
{

}

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
	credits = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_credit_txt.bmp");
	on_hover = new GameImage(SDLHandler, "./ressources/img/main_menu/main_menu_hover_selected.bmp");
}

/*
**	Here, we will put our image on the sdl screen buffer.
**	Used in the game's main loop.
*/

void	MainMenuController::DisplayImages(SDLHandler &SDLHandler)
{
	// Put every image of the scene on the screen.
	bg_1->SetImgPos(0, 0);
	bg_1->SetImgSize(1920, 1080);
	bg_1->SetAlpha(255);
	bg_1->PutImage(SDLHandler);

	title_1->SetImgPos(655, 140);
	title_1->SetImgSize(600, 125);
	title_1->SetAlpha(255);
	title_1->PutImage(SDLHandler);

	btn_play_ia->SetImgPos(655, 380);
	btn_play_ia->SetImgSize(600, 125);
	btn_play_ia->SetAlpha(255);
	btn_play_ia->PutImage(SDLHandler);

	on_hover->SetImgPos(750, 402);
	on_hover->SetImgSize(80, 80);
	on_hover->SetAlpha(255);
	on_hover->PutImage(SDLHandler);

	btn_play_p2->SetImgPos(655, 470);
	btn_play_p2->SetImgSize(600, 125);
	btn_play_p2->SetAlpha(255);
	btn_play_p2->PutImage(SDLHandler);

	btn_quit->SetImgPos(655, 650);
	btn_quit->SetImgSize(600, 125);
	btn_quit->SetAlpha(255);
	btn_quit->PutImage(SDLHandler);

	credits->SetImgPos(800, 800);
	credits->SetImgSize(250, 182);
	credits->SetAlpha(255);
	credits->PutImage(SDLHandler);

	// TTF_Font* Sans = TTF_OpenFont("./ressources/Dosis/Dosis-Regular.ttf", 24); //this opens a font style and sets a size
	// if (!Sans)
	// {
	// 	std::cout << "font error: " << SDL_GetError() << std::endl;
	// 	exit (-1);
	// }

	// SDL_Color White = {255, 255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	// SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	// SDL_Texture* Message = SDL_CreateTextureFromSurface(SDLHandler.renderer, surfaceMessage); //now you can convert it into a texture

	// SDL_Rect Message_rect; //create a rect
	// Message_rect.x = 0;  //controls the rect's x coordinate 
	// Message_rect.y = 0; // controls the rect's y coordinte
	// Message_rect.w = 400; // controls the width of the rect
	// Message_rect.h = 400; // controls the height of the rect

	// //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	// //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	// SDL_RenderCopy(SDLHandler.renderer, Message, NULL, &Message_rect);
}
