#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"


RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL), w(p_w), h(p_h)
{
	window = SDL_CreateWindow(
		p_title, 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		p_w, p_h, 
		SDL_WINDOW_SHOWN);

	if (window==NULL)
	{
		std::cout << "WINDOW failed to init! \n" << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "IMG/Texture Failed to Load! \n" << SDL_GetError() << std::endl;

	return texture;
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x * SCALE;
	dst.y = p_entity.getPos().y * SCALE;
	dst.w = p_entity.getCurrentFrame().w * SCALE;
	dst.h = p_entity.getCurrentFrame().h * SCALE;

	// if the object is visible, draw it ;)
	if (p_entity.pos.x > -p_entity.getWidth() && 
		p_entity.pos.y > -p_entity.getHeight() && 
		p_entity.pos.x < w + p_entity.getWidth() && 
		p_entity.pos.y < h + p_entity.getHeight())
	{
		if (p_entity.getAngle() == 0 && p_entity.mirrored == SDL_FLIP_NONE)
		{
			SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
		} 
		else
		{
			SDL_Point center = {(int)(p_entity.getRotCenter().x * SCALE), 
								(int)(p_entity.getRotCenter().y * SCALE)};
	    	SDL_RenderCopyEx(
	    		renderer, 
	    		p_entity.getTexture(), 
	    		&src, 
	    		&dst, 
	    		p_entity.getAngle(), 
	    		&center, 
	    		p_entity.mirrored);
		}
	}
	
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
