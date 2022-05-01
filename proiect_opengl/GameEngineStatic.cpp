
#include "GameEngine.h"
#include "Utils.h"
#include <stdexcept>

namespace pg
{

	GameEngine* GameEngine::currentEngine = nullptr;
	int GameEngine::window_id = -1;
	GLuint GameEngine::texture_id = 0;
	EndScreenDeath* GameEngine::finalScreen = new EndScreenDeath();
	std::map<game_texture::GameTexture, GLuint>* GameEngine::textures = new std::map<game_texture::GameTexture, GLuint>();

	auto GameEngine::init(int argc, char** argv,const char* windowTitle, int width, int height) -> void
	{
		glutInit(&argc, argv);
		glutInitWindowSize(width, height);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		window_id =  glutCreateWindow(windowTitle);

		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);

		pg::GameEngine::loadTexture(game_texture::GameTexture::BACKGROUND, "bmp.bmp");

		glutDisplayFunc(renderFunc);

		glutReshapeFunc(reshapeFunc);

		glutKeyboardFunc(handleKeyboardFunc);
		glutKeyboardUpFunc(handleKeyboardUpFunc);
		glutTimerFunc(FPS, GameEngine::timerFunc, 0);

		glutMainLoop();
	}

	auto GameEngine::renderFunc() -> void
	{
		getCurrentEngine()->render();
	}

	void GameEngine::reshapeFunc(int x, int y)
	{
		getCurrentEngine()->reshape(x, y);
	}

	void GameEngine::handleKeyboardFunc(unsigned char k, int x, int y)
	{
		getCurrentEngine()->handleKeyboard(k ,x, y);
	}

	void GameEngine::handleKeyboardUpFunc(unsigned char key, int x, int y)
	{
		getCurrentEngine()->handleKeyboardUp(key, x, y);
	}


	auto GameEngine::getCurrentEngine() -> GameEngine*
	{
		if(currentEngine == nullptr)
		{
			throw std::runtime_error("The game engine instance was not created");
		}
		return currentEngine;
	}

	auto GameEngine::getPlayer() const -> PlayerModel* 
	{
		if(player == nullptr)
		{
			throw std::runtime_error("The game engine instance was not created");
		}

		return player;
	}

	auto GameEngine::loadTexture(game_texture::GameTexture textureName, const char* filename) -> void
	{
		Image* img = loadImage(filename);
		texture_id++;
		GameEngine::textures->insert(std::pair<game_texture::GameTexture, GLuint>(textureName, texture_id));

		glGenTextures(1, &(*textures)[textureName]);
		glBindTexture(GL_TEXTURE_2D, (*textures)[textureName]);
		glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE,img->pixels);
	}

	auto GameEngine::timerFunc(int x) -> void
	{
		getCurrentEngine()->timer(x);
	}

}