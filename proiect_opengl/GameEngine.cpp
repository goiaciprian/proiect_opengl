#include "GameEngine.h"
#include "TrapPlatformModel.h"
#include "NormalPlatform.h"

#include <algorithm>
#include <iostream>
#include <string>


namespace pg
{

	auto GameEngine::instantiateEngine(pg::PlayerModel *player) -> GameEngine*
	{
		if(currentEngine == nullptr)
		{
			currentEngine = new GameEngine(player);
			std::fill_n(currentEngine->keyPressed, 256, false);
			currentEngine->_gameState = game_state::GameState::PLAYING;
		}

		return currentEngine;
	}

	GameEngine::GameEngine(PlayerModel *player): player(player)
	{
	}

	GameEngine::~GameEngine()
	{
		delete this->player;
	}

	void renderBackgroundImage() 
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, (*GameEngine::textures)[game_texture::GameTexture::BACKGROUND]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBegin(GL_QUADS);
		
		glTexCoord2f(0.0f,0.0f);
		glVertex2f(-1.0f,-1.0f);

		glTexCoord2f(1.0f,0.0f);
		glVertex2f(1.0f,-1.0f);

		glTexCoord2f(1.0f,1.0f);
		glVertex2f(1.0f,1.0f);

		glTexCoord2f(0.0f,1.0f);
		glVertex2f(-1.0f,1.0f);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	void GameEngine::render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();		
		
		renderBackgroundImage();

		
		if(currentEngine->_gameState == game_state::GameState::PLAYING) 
		{
			this->getPlayer()->renderEntity();
			finalScreen->renderEntity();

			for(auto enemy: *enemies)
				enemy->renderEntity();

			glRasterPos2f(-0.9f, 0.9f);
			for(const char ch : "Scor: " + std::to_string(GameEngine::scor))
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
			}

			glRasterPos2f(-0.9f, 0.8f);
			for(const char ch : "Combo: " + std::to_string(GameEngine::currentCombo))
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
			}

			this->getCurrentEngine()->updateEntities();
		}
		glFlush();

		glLineWidth(1.0f);

		glutSwapBuffers();

	}

	void GameEngine::reshape(int w, int h)
	{
		glViewport(0, 0, 600, 600);
		this->render();
	}


	void GameEngine::handleKeyboard(const unsigned char key, int x , int y)
	{
		switch (key)
		{
		case 27:
			glutDestroyWindow(window_id);
			//exit(0);
			break;
		case 97:
			keyPressed[97] = true;
			break;
		case 100:
			keyPressed[100] = true;
			break;
		case 32:
			keyPressed[32] = true;
			break;
		default:
			break;
		}
	}

	void GameEngine::handleKeyboardUp(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 97:
			keyPressed[97] = false;
			break;
		case 100:
			keyPressed[100] = false;
			break;
		case 32:
			keyPressed[32] = false;
			break;
		default:
			break;
		}
	}


	auto GameEngine::timer(int x) -> void
	{
		//renderBackgroundImage();

		//this->getPlayer()->setRunSpeed(0.0105f);

		auto _engine = this->getCurrentEngine();
		auto _player = this->getPlayer();

		if(_engine->_gameState == game_state::GameState::PLAYING) 
		{
			_engine->movePlayer();

			for(auto enemy: *enemies)
			{
				enemy->moveDown(0.002f);
				if((*enemy)[finalScreen])
				{
					enemy->handleEndCondition();
					
					if(enemy->getType() == game_entity::GameEntity::FRUIT) {
						GameEngine::scor -= 100;
						isCombo = false;
						currentCombo = 0;
					}
				}
				if((*player)[enemy])
				{
					if(enemy->getType() == game_entity::GameEntity::FRUIT)
					{
						scor += 1 + currentCombo;
						if(currentCombo < configuration::Configuration::MAX_COMBO)
							currentCombo++;
						if(currentCombo > 1)
							isCombo = true;
						enemy->handleEndCondition();
						//std::cout << scor << " " << isCombo << " " << currentCombo << std::endl;
					}else 
					{
						_player->handleEndCondition();
						scor /= 2;
						isCombo = false;
						currentCombo = 0;
					}
				} else 
				{
					_player->setAirSpeed(0.015f);
				}
				if((*_player)[finalScreen]) 
				{
					_player->handleEndCondition();
				}
			}
		}
		

		glutPostRedisplay();
		glutTimerFunc(configuration::Configuration::FPS, GameEngine::timerFunc, x);
	}

	void GameEngine::movePlayer()
	{
		auto _player = getPlayer();
		_player->jump();
		_player->fall();

		_player->currentPlayerAnimation = game_texture::Sprites::KNIGHT_IDLE;
		_player->movingDirection = 0;

		if(keyPressed[100]) {
			_player->currentPlayerAnimation = game_texture::Sprites::KNIGHT_WALK;
			_player->moveRight();
			_player->movingDirection = 1;
		}
		if(keyPressed[97]) {
			_player->currentPlayerAnimation = game_texture::Sprites::KNIGHT_WALK;
			_player->moveLeft();
			_player->movingDirection = -1;
		}
		if(keyPressed[32] && !(_player->isInAir())) 
			_player->startJump();
	}

	auto GameEngine::updateEntities() -> void
	{
		auto time = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(time - currentTime).count();
		
		if(elapsed > 2 && enemies->size() < 12)
		{
			currentTime = time;
			int number = 0;
			do {
				number = pg::randomGeneratorInt(1, 3);
			} while (number == previousNumber);
			previousNumber = number;
			std::vector<GlPoint> *position;
			if(number == 1) position = &configuration::Configuration::normalPlatformModel;
			else if (number == 2) position = &configuration::Configuration::trapPlatformModel;
			else position = &configuration::Configuration::position2;

			auto shouldBe = randomGenerateEntity();
			if(shouldBe == game_entity::GameEntity::FRUIT)
				enemies->push_back(new NormalPlatform(position, new pg::Position2D()));
			else 
				enemies->push_back(new TrapPlatformModel(position, new pg::Position2D()));
		}
	}
}
