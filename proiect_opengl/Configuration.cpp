#include "Configuration.h"

namespace configuration
{
	int Configuration::FPS = 1000/120;
	int Configuration::MAX_COMBO = 5;

	int Configuration::HEIGHT = 600;
	int Configuration::WIDTH = 600;
	char Configuration::TITLE[] = "Proiect OpenGL";

	std::vector<pg::GlPoint> Configuration::renderPlayerTexture {
			pg::GlPoint {-0.15f, -0.15f},
			pg::GlPoint {0.15f, -0.15f},
			pg::GlPoint {0.15f, 0.15f},
			pg::GlPoint {-0.15f, 0.15f}
	};

	std::vector<pg::GlPoint> Configuration::playerModel {
			pg::GlPoint {-0.06f, -0.06f},
			pg::GlPoint {0.06f, -0.06f},
			pg::GlPoint {0.06f, 0.06f},
			pg::GlPoint {-0.06f, 0.06f}
	};
	std::vector<pg::GlPoint> Configuration::trapPlatformModel {
			pg::GlPoint { 0.6f, 0.9f},
			pg::GlPoint { 0.4f, 0.9f},
			pg::GlPoint { 0.4f, 0.7f},
			pg::GlPoint { 0.6f, 0.7f},

	};
	std::vector<pg::GlPoint> Configuration::normalPlatformModel {
			pg::GlPoint { -0.6f, 1.1f},
			pg::GlPoint { -0.4f, 1.1f},
			pg::GlPoint { -0.4f, 0.9f},
			pg::GlPoint { -0.6f, 0.9f},

	};

	std::vector<pg::GlPoint> Configuration::position2 {
			pg::GlPoint { 0.0f, 1.1f},
			pg::GlPoint { 0.2f, 1.1f},
			pg::GlPoint { 0.2f, 0.9f},
			pg::GlPoint { 0.0f, 0.9f},

	};

}
