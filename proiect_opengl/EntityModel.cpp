#include "EntityModel.h"
#include "GameEngine.h"
#include <GL/glut.h>

#include <iostream>

namespace pg
{

	void EntityModel::initEntity(std::vector<GlPoint>* points, Position2D* position)
	{
		this->_entityModelPoints = *points;
		this->_alteredPosition = *points;
		this->position_ = *position;
	}


	void EntityModel::moveLeftPoints(bool revert)
	{
		for(int i = 0; i < _alteredPosition.size(); i++)
		{
			auto elem = _alteredPosition.at(i);
			elem.x -= this->runSpeed;
			if(revert) elem.x *= -1;
			_alteredPosition.at(i) = elem;
		}
	}


	auto EntityModel::moveLeft() -> void
	{
		
		this->position_.x -= this->runSpeed;
		bool revert = this->position_.x <= -1.4f;
		if(revert) this->position_.x *= -1;
		this->moveLeftPoints(revert);
	}

	void EntityModel::moveRightPoints(bool revert)
	{
		for(int i = 0; i < _alteredPosition.size(); i++)
		{
			auto elem = _alteredPosition.at(i);
			elem.x += this->runSpeed;
			if(revert) elem.x *= -1;
			_alteredPosition.at(i) = elem;
		}

	}


	auto EntityModel::moveRight() -> void
	{
		this->position_.x += this->runSpeed;
		bool revert = this->position_.x >= 1.4f;
		if(revert) this->position_.x *= -1;
		this->moveRightPoints(revert);
	}

	auto EntityModel::moveUpPoints()-> void
	{
		for(int i = 0; i < _alteredPosition.size(); i++)
		{
			auto elem = _alteredPosition.at(i);
			elem.y += airSpeed;
			_alteredPosition.at(i) = elem;
		}
	}

	auto EntityModel::moveDownPoints(GLfloat downSpeed) -> void
	{
		for(int i = 0; i < _alteredPosition.size(); i++)
		{
			auto elem = _alteredPosition.at(i);
			elem.y -= downSpeed;
			_alteredPosition.at(i) = elem;
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
		
		glColor3f(red, green, blue);
		glBegin(chooseEntity());
		for (const auto element : this->_alteredPosition)
		{
			glVertex2f(element.x, element.y);
		}
		glEnd();
	}

	void EntityModel::setEntityToOrigin()
	{
		this->_alteredPosition = this->_entityModelPoints;
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
		}
	}



	bool EntityModel::operator[](EntityModel* entity)
	{
		GLfloat maxTop = -100.0f;
		GLfloat maxBottom = 100.0f;
		GLfloat maxLeft = 100.0f;
		GLfloat maxRight = -100.0f;

		for(auto& thisPoint : entity->_alteredPosition) 
		{
			maxTop = std::fmaxf(thisPoint.y, maxTop);
			maxBottom= std::fminf(thisPoint.y, maxBottom);
			
			maxLeft = std::fminf(thisPoint.x, maxLeft);
			maxRight= std::fmaxf(thisPoint.x, maxRight);
		}

		bool inXminSiXmax = false, inYminSiYmax = false, collide = false;

		//verificam daca entity s-a lovit de this
		for (auto& pointToCheck: this->_alteredPosition)
		{
			auto xValue = pointToCheck.x;
			auto yValue = pointToCheck.y;

			inXminSiXmax = (xValue >= maxLeft) && (xValue <= maxRight);
			inYminSiYmax = (yValue <= maxTop) && (yValue >= maxBottom);

			if(inXminSiXmax && inYminSiYmax) 
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
}

