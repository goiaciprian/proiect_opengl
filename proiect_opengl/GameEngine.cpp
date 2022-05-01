#include "GameEngine.h"

#include <algorithm>
#include <iostream>

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

		}
		glFlush();
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

		if(getCurrentEngine()->_gameState == game_state::GameState::PLAYING) 
		{
			this->getCurrentEngine()->movePlayer();

			for(auto enemy: *enemies)
			{
				enemy->moveDown(0.002f);
				if((*enemy)[finalScreen])
				{
					std::cout<<"enemy should respawn" << std::endl;
					enemy->handleEndCondition();
				}
				if((*getPlayer())[enemy])
				{
					getPlayer()->handleEndCondition();
				}
				if((*getPlayer())[finalScreen]) 
				{
					std::cout << "should be safe" << std::endl;
					getPlayer()->standingOnPlatform(finalScreen);
				}
			}
		}
		

		glutPostRedisplay();
		glutTimerFunc(FPS, GameEngine::timerFunc, x);
	}

	void GameEngine::movePlayer()
	{
		this->getPlayer()->jump();
		this->getPlayer()->fall();

		if(keyPressed[100])
			this->getPlayer()->moveRight();
		if(keyPressed[97])
			this->getPlayer()->moveLeft();
		if(keyPressed[32] && !getPlayer()->isInAir()) 
			this->getPlayer()->startJump();
	}



}
