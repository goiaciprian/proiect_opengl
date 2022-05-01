#pragma once

#ifndef GameEngine_H
#define GameEngine_H

#include <GL/glut.h>
#include "PlayerModel.h"
#include "EndScreenDeath.h"
#include <vector>
#include <map>

namespace pg
{
	class GameEngine
	{
		const static int FPS = 1000/120;
		static int window_id;
		static GameEngine *currentEngine;
		static EndScreenDeath* finalScreen;

		PlayerModel *player = nullptr;
		bool keyPressed[256] = {false};
		game_state::GameState _gameState;

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
		static std::map<game_texture::GameTexture, GLuint>* textures;
		static GLuint texture_id;
		std::vector<EntityModel*>* enemies = new std::vector<EntityModel*>();
		
		~GameEngine();
		
		static auto instantiateEngine(PlayerModel*) -> GameEngine*;

		static auto init(int, char**, const char*, int, int) -> void;

		static void renderFunc();

		static auto getCurrentEngine() -> GameEngine*;

		static auto loadTexture(game_texture::GameTexture, const char*) -> void;

		auto getPlayer() const -> PlayerModel*;
	};
}

#endif