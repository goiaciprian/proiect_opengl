#include "EntityModel.h"
#include "GameEngine.h"
#include <GL/glut.h>
#include "Utils.h"

#include <iostream>

namespace pg
{
	void EntityModel::initEntity(std::vector<GlPoint>* points, Position2D* position)
	{
		this->_entityModelPoints = *points;
		this->_alteredPosition = *points;
		this->_renderTexture = std::vector<GlPoint>();
		this->_originTexture = std::vector<GlPoint>();
		this->position_ = *position;
	}

	void EntityModel::initEntity(std::vector<GlPoint>* points, std::vector<GlPoint>* renderTexture, Position2D* position)
	{
		this->_entityModelPoints = *points;
		this->_alteredPosition = *points;
		this->_renderTexture = *renderTexture;
		this->_originTexture = *renderTexture;
		this->position_ = *position;
	}

	void EntityModel::moveLeftPoints(bool revert)
	{
		for (int i = 0; i < _alteredPosition.size(); i++)
		{
			auto elem = _alteredPosition.at(i);
			elem.x -= this->runSpeed;
			if (revert) {
				elem.x *= -1;
			}
			_alteredPosition.at(i) = elem;

			if (_renderTexture.size()) {
				auto renderElem = _renderTexture.at(i);
				renderElem.x -= this->runSpeed;
				if (revert) {
					renderElem.x *= -1;
				}
				_renderTexture.at(i) = renderElem;
			}
		}
	}

	auto EntityModel::moveLeft() -> void
	{

		this->position_.x -= this->runSpeed;
		bool revert = this->position_.x <= -1.4f;
		if (revert) this->position_.x *= -1;
		this->moveLeftPoints(revert);
	}

	void EntityModel::moveRightPoints(bool revert)
	{
		for (int i = 0; i < _alteredPosition.size(); i++)
		{
			auto elem = _alteredPosition.at(i);
			elem.x += this->runSpeed;
			if (revert) {
				elem.x *= -1;
			}
			_alteredPosition.at(i) = elem;
			
			if (_renderTexture.size()) {
				auto renderElem = _renderTexture.at(i);
				renderElem.x += this->runSpeed;
				if (revert) {
					renderElem.x *= -1;
				}
				_renderTexture.at(i) = renderElem;
			}
		}

	}

	auto EntityModel::moveRight() -> void
	{
		this->position_.x += this->runSpeed;
		bool revert = this->position_.x >= 1.4f;
		if (revert) this->position_.x *= -1;
		this->moveRightPoints(revert);
	}

	auto EntityModel::moveUpPoints()-> void
	{
		for (int i = 0; i < _alteredPosition.size(); i++)
		{
			auto elem = _alteredPosition.at(i);
			elem.y += airSpeed;
			_alteredPosition.at(i) = elem;
			if (_renderTexture.size()) {
				auto renderElem = _renderTexture.at(i);
				renderElem.y += airSpeed;
				_renderTexture.at(i) = renderElem;
			}
		}
	}

	auto EntityModel::moveDownPoints(GLfloat downSpeed) -> void
	{
		for (int i = 0; i < _alteredPosition.size(); i++)
		{
			auto elem = _alteredPosition.at(i);
			elem.y -= downSpeed;
			_alteredPosition.at(i) = elem;
			if (_renderTexture.size()) {
				auto renderElem = _renderTexture.at(i);
				renderElem.y -= downSpeed;
				_renderTexture.at(i) = renderElem;
			}
		}
	}

	auto EntityModel::moveDown() ->  void
	{
		this->position_.y -= airSpeed;
		this->moveDownPoints(this->airSpeed);
	}

	auto EntityModel::moveDown(GLfloat speed)-> void
	{

		this->position_.y -= speed;
		this->moveDownPoints(speed);
	}

	auto EntityModel::moveUp()-> void
	{
		this->position_.y += airSpeed;
		this->moveUpPoints();
	}

	void EntityModel::renderEntity()
	{
		std::vector<pg::GlPoint> spritePosLeft{
			GlPoint(1.0f,1.0f),
			GlPoint(0.0f,1.0f),
			GlPoint(0.0f,0.0f),
			GlPoint(1.0f,0.0f),
		};

		std::vector<pg::GlPoint> spritePosRight{
			GlPoint(0.0f,1.0f),
			GlPoint(1.0f,1.0f),
			GlPoint(1.0f,0.0f),
			GlPoint(0.0f,0.0f),
		};

		int i = 0;
		bool isPlayer = getType() == game_entity::GameEntity::PLAYER;
		
		glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		
		if (isPlayer) {
			maxFrames = GameEngine::sprites->at(currentPlayerAnimation).size();

			if (frame >= maxFrames) frame = 0;
			glBindTexture(GL_TEXTURE_2D, (*GameEngine::sprites).at(EntityModel::currentPlayerAnimation).at(GameEngine::delay % 10 == 0 ? frame++ : frame));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
			glBegin(chooseEntity());
			auto *directionArr = movingDirection > 0 ? &spritePosRight : &spritePosLeft; 
			for (const auto elem : this->_renderTexture) {
				auto curr = directionArr->at(i++);
				glTexCoord2f(curr.x, curr.y);
				glVertex2f(elem.x, elem.y);
			}
			glEnd();
		}
		else {

			auto texture = getType() == game_entity::GameEntity::ROCK ? game_texture::GameTexture::ROCK : game_texture::GameTexture::FRUIT;

			glBindTexture(GL_TEXTURE_2D, (*GameEngine::textures)[texture]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		

			glBegin(chooseEntity());
			for (const auto element : this->_alteredPosition)
			{
				auto curr = spritePosRight.at(i++);
				glTexCoord2f(curr.x, curr.y);

				glVertex2f(element.x, element.y);
			}
			glEnd();
		}
		

		
		glDisable(GL_BLEND);

	}

	void EntityModel::setEntityToOrigin()
	{
		this->_alteredPosition = this->_entityModelPoints;
		this->_renderTexture = this->_originTexture;
		this->position_.x = 0.0f;
		this->position_.y = 0.0f;
	}

	void EntityModel::setRunSpeed(GLfloat speed)
	{
		this->runSpeed = speed;
	}

	void EntityModel::setColor(GLfloat red, GLfloat green, GLfloat blue)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	GLenum EntityModel::chooseEntity()
	{
		switch (this->_alteredPosition.size())
		{
		case 2:
			return GL_LINE;
		case 3:
			return GL_TRIANGLES;
		case 4:
			return GL_QUADS;
		default:
			throw - 1;
		}
	}



	bool EntityModel::operator[](EntityModel* entity)
	{
		GLfloat maxTop = -100.0f;
		GLfloat maxBottom = 100.0f;
		GLfloat maxLeft = 100.0f;
		GLfloat maxRight = -100.0f;

		for (auto& thisPoint : entity->_alteredPosition)
		{
			maxTop = std::fmaxf(thisPoint.y, maxTop);
			maxBottom = std::fminf(thisPoint.y, maxBottom);

			maxLeft = std::fminf(thisPoint.x, maxLeft);
			maxRight = std::fmaxf(thisPoint.x, maxRight);
		}

		bool inXminSiXmax = false, inYminSiYmax = false, collide = false;

		//verificam daca entity s-a lovit de this
		for (auto& pointToCheck : this->_alteredPosition)
		{
			auto xValue = pointToCheck.x;
			auto yValue = pointToCheck.y;

			inXminSiXmax = (xValue >= maxLeft) && (xValue <= maxRight);
			inYminSiYmax = (yValue <= maxTop) && (yValue >= maxBottom);

			if (inXminSiXmax && inYminSiYmax)
			{
				collide = true;
			}
		}
		return collide;
	}

	auto EntityModel::_getAlteredPositon() -> std::vector<GlPoint>
	{
		return this->_alteredPosition;
	}

	auto EntityModel::_getPosition() -> Position2D
	{
		return this->position_;
	}

	void EntityModel::setAirSpeed(GLfloat airSpeed)
	{
		this->airSpeed = airSpeed;
	}
}

