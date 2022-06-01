#pragma once

#ifndef Utils_H
#define Utils_H

#include <GL/glut.h>

namespace pg
{
	namespace game_state
	{
		enum class GameState 
		{
			MAIN_MENU,
			PLAYING,
			LOST
		};
	};

	namespace game_texture
	{
		enum class GameTexture
		{
			BACKGROUND,
			PLAYER,
			ROCK,
			FRUIT
		};

		enum class Sprites 
		{
			KNIGHT_IDLE,
			KNIGHT_JUMP,
			KNIGHT_FALL,
			KNIGHT_WALK
		};
	};

	namespace game_entity
	{
		enum class GameEntity
		{
			PLAYER,
			ROCK,
			FRUIT,
			BOTTOM_SCREEN
		};
	};

	class Image
	{
	public:
		Image(char* pixels, int width, int height);

		char* pixels;
		int width, height;
	};


	Image* loadImage(const char*);


	struct GlPoint
	{
		GLfloat x = 0.0f;
		GLfloat y = 0.0f;

	public:
		GlPoint() {}
		GlPoint(GLfloat x, GLfloat y) {
			this->x = x;
			this->y = y;
		}
	};

	typedef GlPoint Position2D;

	game_entity::GameEntity randomGenerateEntity();
	
	int randomGeneratorInt(int min, int max);
	double randomGeneratorDouble(double min, double max);
}

#endif