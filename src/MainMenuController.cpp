#include "../includes/Gomoku.hpp"

MainMenuController::MainMenuController()
{

}

MainMenuController::~MainMenuController()
{

}

void	MainMenuController::LoadImages(SDLHandler &SDLHandler)
{
	// load first surface and texture -> background 1.
	if (!(surface = SDL_LoadBMP("./ressources/img/main_menu/main_menu_bg.bmp")))
		std::cerr << "Error loading bmp: " << SDL_GetError() << std::endl;
	bg_1_texture = SDL_CreateTextureFromSurface(SDLHandler.renderer, surface);
	SDL_FreeSurface(surface);
	if (!(surface = SDL_LoadBMP("./ressources/img/main_menu/main_menu_title_1.bmp")))
		std::cerr << "Error loading bmp: " << SDL_GetError() << std::endl;
	title_1_texture = SDL_CreateTextureFromSurface(SDLHandler.renderer, surface);
	SDL_FreeSurface(surface);
}

void	MainMenuController::DisplayImages(SDLHandler &SDLHandler)
{
	SDL_RenderCopy(SDLHandler.renderer, bg_1_texture, NULL, NULL);

	SDL_Rect temp_rect; //create a rect
	temp_rect.x = 340;  //controls the rect's x coordinate 
	temp_rect.y = 60; // controls the rect's y coordinte
	temp_rect.w = 600 * (1980 / WINDOW_WIDTH); // controls the width of the rect
	temp_rect.h = 125 * (1080 / WINDOW_HEIGHT); // controls the height of the rect

	SDL_RenderCopy(SDLHandler.renderer, title_1_texture, NULL, &temp_rect);

 	
	// if(!TTF_WasInit() && TTF_Init()==-1) {
	//     printf("TTF_Init: %s\n", TTF_GetError());
	//     exit(1);
	// }

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
