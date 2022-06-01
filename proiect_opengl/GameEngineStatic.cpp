
#include "GameEngine.h"
#include "Utils.h"
#include "picopng.h"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <fstream>


namespace pg
{

	GameEngine* GameEngine::currentEngine = nullptr;
	int GameEngine::window_id = -1;
	int GameEngine::scor = 0;
	int GameEngine::currentCombo = 0;
	bool GameEngine::isCombo = false;
	unsigned long long GameEngine::delay = 0;
	GLuint GameEngine::texture_id = 0;
	EndScreenDeath* GameEngine::finalScreen = new EndScreenDeath();
	std::map<game_texture::GameTexture, GLuint>* GameEngine::textures = new std::map<game_texture::GameTexture, GLuint>();
	std::map<game_texture::Sprites, std::vector<GLuint>>* GameEngine::sprites = new std::map<game_texture::Sprites, std::vector<GLuint>>();

	auto GameEngine::init(int argc, char** argv,const char* windowTitle, int width, int height) -> void
	{
		glutInit(&argc, argv);
		glutInitWindowSize(width, height);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		window_id =  glutCreateWindow(windowTitle);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);

		pg::GameEngine::loadTexture(game_texture::GameTexture::BACKGROUND, "bmp.bmp");

		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle1.png", 0);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle2.png", 1);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle3.png", 2);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle4.png", 3);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle5.png", 4);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle6.png", 5);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle7.png", 6);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle8.png", 7);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle9.png", 8);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle10.png", 9);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle11.png", 10);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_IDLE, "Knight/Idle/idle12.png", 11);

		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_WALK, "Knight/Walk/walk1.png", 0);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_WALK, "Knight/Walk/walk2.png", 1);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_WALK, "Knight/Walk/walk3.png", 2);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_WALK, "Knight/Walk/walk4.png", 3);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_WALK, "Knight/Walk/walk5.png", 4);
		pg::GameEngine::loadPNG(game_texture::Sprites::KNIGHT_WALK, "Knight/Walk/walk6.png", 5);

		pg::GameEngine::loadPNG(game_texture::GameTexture::ROCK, "Rocks/5.png");
		pg::GameEngine::loadPNG(game_texture::GameTexture::FRUIT, "Fruits/beer.png");

		glutDisplayFunc(renderFunc);

		glutReshapeFunc(reshapeFunc);

		glutKeyboardFunc(handleKeyboardFunc);
		glutKeyboardUpFunc(handleKeyboardUpFunc);
		glutTimerFunc(configuration::Configuration::FPS, GameEngine::timerFunc, 0);

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
	auto GameEngine::loadPNG (game_texture::GameTexture textureName, const std::string filename) -> void {
		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned long width, height;
		std::ifstream input;

		input.open(filename, std::fstream::binary);

		while(!input.eof()) {
			in.push_back(input.get());
		}

		input.clear();
		input.close();

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

		texture_id++;
		textures->insert(std::pair<game_texture::GameTexture, GLuint>(textureName, texture_id));
		glGenTextures(1, &(textures->at(textureName)));
		glBindTexture(GL_TEXTURE_2D, textures->at(textureName));

		glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());
	}

	auto GameEngine::loadPNG (game_texture::Sprites spriteName, const std::string filename, int pos) -> void {
		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned long width, height;

		std::ifstream input;

		GameEngine::sprites->insert(
			std::pair<game_texture::Sprites, std::vector<GLuint>>(spriteName, std::vector<GLuint>())
		);

		//for(int i = 1; i <= max; i++) {
			input.open(filename, std::fstream::binary);


			while(!input.eof()) {
				in.push_back(input.get());
			}

			input.clear();
			input.close();

			int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
			/*if (errorCode != 0) {
				assert(!"decodePNG failed with error: " + errorCode);*/
			texture_id++;
			GameEngine::sprites->at(spriteName).push_back(texture_id);
			glGenTextures(1, &(*GameEngine::sprites).at(spriteName).at(pos));
			glBindTexture(GL_TEXTURE_2D, (*GameEngine::sprites).at(spriteName).at(pos));

			//GameEngine::textures->insert(std::pair<game_texture::Spri, GLuint>(spriteName, texture_id));
			//glGenTextures(1, &(*textures)[textureName]);
			//glBindTexture(GL_TEXTURE_2D, (*textures)[textureName]);
			glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());
			
		//}

		return;
	}


	auto GameEngine::timerFunc(int x) -> void
	{
		getCurrentEngine()->timer(x);
		delay++;
	}

}
