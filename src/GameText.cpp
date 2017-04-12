#include "../includes/Gomoku.hpp"

GameText::GameText(SDLHandler &SDLHandler, std::string text, int size)
{
	if (text.empty())
	{
		std::cout << "Value required to create new text" << std::endl;
	}
	else
	{
		_fontSize = size;
		_font = TTF_OpenFont("./ressources/Dosis/Dosis-Regular.ttf", _fontSize); //this opens a font style and sets a size
		if (!_font)
		{
			std::cout << "font error: " << SDL_GetError() << std::endl;
			exit (-1);
		}
		// Default color == BLACK
		_fontColor.r = 0;
		_fontColor.g = 0;
		_fontColor.b = 0;
		_fontColor.a = 255;
		_textSurface = TTF_RenderText_Solid(_font, text.c_str(), _fontColor);
		_textTexture = SDL_CreateTextureFromSurface(SDLHandler.renderer, _textSurface);
	}
}

// EASY CODE FOR WRITING TEXT

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

GameText::~GameText()
{
	if (_textSurface)
		SDL_FreeSurface(_textSurface);
	SDL_DestroyTexture(_textTexture);
}

void		GameText::SetTextPos(int x, int y)
{
	_textRect.x = x;
	_textRect.y = y;
}

void		GameText::SetTextSize(int width, int height)
{
	_textRect.w = width;
	_textRect.h = height;
}

/*
**	Put the image on the renderer -> will be displayed at next draw.
*/

void		GameText::PutText(SDLHandler &SDLHandler)
{
	SDL_RenderCopy(SDLHandler.renderer, _textTexture, NULL, &_textRect);
}

/*
**	Set the image blending mode :
**	SDL_BLENDMODE_BLEND
**	SDL_BLENDMODE_ADD
**	SDL_BLENDMODE_MOD
*/

void		GameText::SetBlendMode(SDL_BlendMode blending)
{
    //Set blending function
    SDL_SetTextureBlendMode(_textTexture, blending);
}
        
void		GameText::SetAlpha(Uint8 alpha)
{
    //Modulate texture alpha
    _alpha = alpha;
    SDL_SetTextureAlphaMod(_textTexture, _alpha);
}

Uint8		GameText::GetAlpha()
{
	return (_alpha);
}

void		GameText::FadeIn()
{
	if (_alpha < 255)
	{
		_alpha += 1;
		SDL_SetTextureAlphaMod(_textTexture, _alpha);
	}
}

void		GameText::FadeOut()
{
	if (_alpha > 0)
	{
		_alpha -= 1;
		SDL_SetTextureAlphaMod(_textTexture, _alpha);
	}
}

bool		GameText::IsColliding(int x, int y)
{
	if (x >= _textRect.x && x <= _textRect.x + _textRect.w
		&& y >= _textRect.y && y <= _textRect.y + _textRect.h)
		return (true);
	return (false);
}

/*
**	Returns the image's SDL_Rect for reading.
**	Useful for collision checks and prints.
*/

SDL_Rect	GameText::GetRect()
{
	return (this->_textRect);
}

SDL_Texture	*GameText::GetTexture()
{
	return (this->_textTexture);
}

void	GameText::SetTexture(SDL_Texture *texture)
{
	this->_textTexture = texture;
}
