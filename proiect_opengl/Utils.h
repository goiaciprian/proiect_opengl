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
			TRAP_PLATFORM,
			PLATFORM
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
	};

	typedef GlPoint Position2D;

}

#endif