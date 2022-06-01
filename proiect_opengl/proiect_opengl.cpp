#include <iostream>
//#include <Windows.h>

#include "GameEngine.h"
#include "Utils.h"
#include "TrapPlatformModel.h"
#include "NormalPlatform.h"
#include <vector>

#include "Configuration.h"


auto main(int argc, char** argv) -> int
{
	auto *danutz = new pg::PlayerModel(&configuration::Configuration::playerModel, &configuration::Configuration::renderPlayerTexture, new pg::Position2D());
	auto *trapPlatform = new pg::TrapPlatformModel(&configuration::Configuration::trapPlatformModel, new pg::Position2D());
	auto *normalPlatform = new pg::NormalPlatform(&configuration::Configuration::normalPlatformModel, new pg::Position2D());

	auto* engine = pg::GameEngine::instantiateEngine(danutz);

	engine->enemies->push_back(trapPlatform);
	engine->enemies->push_back(normalPlatform);

	pg::GameEngine::init(argc, argv, configuration::Configuration::TITLE, configuration::Configuration::WIDTH, configuration::Configuration::HEIGHT);
	pg::GameEngine::renderFunc();

	delete pg::GameEngine::getCurrentEngine();
	delete trapPlatform;
	delete danutz;
	return 0;
}


