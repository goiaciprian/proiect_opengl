#pragma once

#ifndef GameEngine_H
#define GameEngine_H

#include <GL/glut.h>
#include "PlayerModel.h"
#include "EndScreenDeath.h"
#include <vector>
#include <map>
#include <string>
#include <chrono>

#include "Configuration.h"

namespace pg
{
	class GameEngine
	{
		static int scor, currentCombo;
		static bool isCombo;
		static int window_id;
		static GameEngine *currentEngine;
		static EndScreenDeath* finalScreen;
		std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

		PlayerModel *player = nullptr;
		bool keyPressed[256] = {false};
		game_state::GameState _gameState;
		int previousNumber = 0;

		void handleKeyboard(unsigned char, int, int);
		void handleKeyboardUp(unsigned char, int, int);
		void reshape(int, int);
		void timer(int);
		void render();
		void movePlayer();


		static void reshapeFunc(int, int);
		static void handleKeyboardFunc(unsigned char, int, int);
		static void handleKeyboardUpFunc(unsigned char, int, int);
		static void timerFunc(int);
		
		GameEngine(PlayerModel*);
	public:
		static unsigned long long delay;

		static std::map<game_texture::GameTexture, GLuint>* textures;
		static std::map<game_texture::Sprites, std::vector<GLuint>>* sprites;
		static GLuint texture_id;
		std::vector<EntityModel*>* enemies = new std::vector<EntityModel*>();
		
		~GameEngine();
		
		static auto instantiateEngine(PlayerModel*) -> GameEngine*;

		static auto init(int, char**, const char*, int, int) -> void;

		static void renderFunc();

		static auto getCurrentEngine() -> GameEngine*;

		static auto loadTexture(game_texture::GameTexture, const char*) -> void;
		static auto loadPNG(game_texture::Sprites, const std::string, int) -> void;
		static auto loadPNG (game_texture::GameTexture textureName, const std::string filename) -> void;

		auto getPlayer() const -> PlayerModel*;

		auto updateEntities() -> void;
	};
}

#endif