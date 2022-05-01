#include <iostream>
//#include <Windows.h>

#include <GL/glut.h>
#include "GameEngine.h"
#include "Utils.h"
#include "TrapPlatformModel.h"
#include <vector>

constexpr auto WIDTH = 600;
constexpr auto HEIGHT = 600;

constexpr auto TITLE = "Proiect OpenGL";

std::vector<pg::GlPoint> playerModel {
	pg::GlPoint {-0.06f, -0.06f},
	pg::GlPoint {0.06f, -0.06f},
	pg::GlPoint {0.06f, 0.06f},
	pg::GlPoint {-0.06f, 0.06f}
} ;

std::vector<pg::GlPoint> trapPlatformModel {
	pg::GlPoint { 0.6f, 0.2f},
	pg::GlPoint { 0.4f, 0.2f},
	pg::GlPoint { 0.4f, 0.4f},
	pg::GlPoint { 0.6f, 0.4f},

};


auto main(int argc, char** argv) -> int
{
	auto *model = new pg::PlayerModel(&playerModel, new pg::Position2D());
	auto *trapPlatform = new pg::TrapPlatformModel(&trapPlatformModel, new pg::Position2D());

	auto* engine = pg::GameEngine::instantiateEngine(model);

	engine->enemies->push_back(trapPlatform);

	pg::GameEngine::init(argc, argv, TITLE, WIDTH, HEIGHT);
	pg::GameEngine::renderFunc();

	delete pg::GameEngine::getCurrentEngine();
	delete trapPlatform;
	delete model;
	return 0;
}


