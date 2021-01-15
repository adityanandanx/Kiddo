#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"
// #include "Math.hpp"

const float SCALE = 1.5f;

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	
	int getRefreshRate();
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();

	// Get(ters)
	int getWidth(){return w;}
	int getHeight(){return h;}
	SDL_Renderer* getRenderer() {return renderer;}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int w, h;
};
