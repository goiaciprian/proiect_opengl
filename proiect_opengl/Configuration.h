#pragma once
#include <vector>
#include "Utils.h"


namespace configuration
{
	class Configuration
	{
	public:
		static int FPS, MAX_COMBO;

		static int WIDTH;
		static int HEIGHT;

		static char TITLE[];

		static std::vector<pg::GlPoint> playerModel;
		static std::vector<pg::GlPoint> renderPlayerTexture;

		static std::vector<pg::GlPoint> trapPlatformModel;
		static std::vector<pg::GlPoint> normalPlatformModel;
		static std::vector<pg::GlPoint> position2;
	};
}
