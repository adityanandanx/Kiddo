#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

struct Vector2f
{
	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	void add_to(Vector2f p_vec)
	{
		x += p_vec.x;
		y += p_vec.y;
	}
	void subtract_from(Vector2f p_vec)
	{
		x -= p_vec.x;
		y -= p_vec.y;
	}

	float x, y;
};

struct Vector2i
{
	Vector2i()
	:x(0), y(0)
	{}

	Vector2i(int p_x, int p_y)
	:x(p_x), y(p_y)
	{}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	Vector2i add_to(Vector2i p_vec)
	{
		return Vector2i(x + p_vec.x, y + p_vec.y);
	}
	Vector2i subtract_from(Vector2i p_vec)
	{
		return Vector2i(x - p_vec.x, y - p_vec.y);
	}

	int x, y;
};