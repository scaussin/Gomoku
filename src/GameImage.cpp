#include "../includes/Gomoku.hpp"

GameImage::GameImage(SDLHandler &SDLHandler, std::string imgPath)
{
	if (imgPath.empty())
	{
		std::cout << "image path required." << std::endl;
	}
	else
	{
		if (!(_imgSurface = SDL_LoadBMP(imgPath.c_str())))
		{
			std::cerr << "Error loading bmp: " << SDL_GetError() << std::endl;
		}
		_imgTexture = SDL_CreateTextureFromSurface(SDLHandler.renderer, _imgSurface);
		SDL_FreeSurface(_imgSurface);
		SetBlendMode(SDL_BLENDMODE_BLEND);
		SetAlpha(255);
	}
}

GameImage::~GameImage()
{
	if (_imgSurface)
		SDL_FreeSurface(_imgSurface);
	SDL_DestroyTexture(_imgTexture);
}

void		GameImage::SetImgPos(int x, int y)
{
	_imgRect.x = x;
	_imgRect.y = y;
}

void		GameImage::SetImgSize(int width, int height)
{
	_imgRect.w = width;
	_imgRect.h = height;
}

/*
**	Put the image on the renderer -> will be displayed at next draw.
*/

void		GameImage::PutImage(SDLHandler &SDLHandler)
{
	SDL_RenderCopy(SDLHandler.renderer, _imgTexture, NULL, &_imgRect);
}

/*
**	Set the image blending mode :
**	SDL_BLENDMODE_BLEND
**	SDL_BLENDMODE_ADD
**	SDL_BLENDMODE_MOD
*/

void		GameImage::SetBlendMode(SDL_BlendMode blending)
{
    //Set blending function
    SDL_SetTextureBlendMode(_imgTexture, blending);
}
        
void		GameImage::SetAlpha(Uint8 alpha)
{
    //Modulate texture alpha
    _alpha = alpha;
    SDL_SetTextureAlphaMod(_imgTexture, _alpha);
}

Uint8		GameImage::GetAlpha()
{
	return (_alpha);
}

void		GameImage::FadeIn()
{
	if (_alpha < 255)
	{
		_alpha += 1;
		SDL_SetTextureAlphaMod(_imgTexture, _alpha);
	}
}

void		GameImage::FadeOut()
{
	if (_alpha > 0)
	{
		_alpha -= 1;
		SDL_SetTextureAlphaMod(_imgTexture, _alpha);
	}
}

bool		GameImage::IsColliding(int x, int y)
{
	if (x >= _imgRect.x && x <= _imgRect.x + _imgRect.w
		&& y >= _imgRect.y && y <= _imgRect.y + _imgRect.h)
		return (true);
	return (false);
}

/*
**	Returns the image's SDL_Rect for reading.
**	Useful for collision checks and prints.
*/

SDL_Rect	GameImage::GetRect()
{
	return (this->_imgRect);
}

SDL_Texture	*GameImage::GetTexture()
{
	return (this->_imgTexture);
}

void	GameImage::SetTexture(SDL_Texture *texture)
{
	this->_imgTexture = texture;
}
