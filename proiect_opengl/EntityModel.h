#pragma once

#ifndef EntityModel_H
#define EntityModel_H

#include "Utils.h"
#include <vector>

namespace pg
{
	class EntityModel
	{
		void moveLeftPoints(bool);
		void moveRightPoints(bool);
		void moveUpPoints();
		void moveDownPoints(GLfloat);
		GLenum chooseEntity();

	protected:
		GLfloat runSpeed = 0.0105f, maxJump = 0.6f, airSpeed = 0.015f, red = 0.0f, green = 0.0f, blue = 0.0f ;
		std::vector<GlPoint> _entityModelPoints, _alteredPosition;
		Position2D position_;

		void initEntity(std::vector<GlPoint>* points, Position2D* position);
		void moveLeft();
		void moveRight();
		void moveUp();
		void setEntityToOrigin();
		void setRunSpeed(GLfloat speed);



	public:
		virtual ~EntityModel() {};

		virtual void handleEndCondition() = 0;
		bool operator[] (EntityModel*);
		void moveDown();
		void moveDown(GLfloat);
		void renderEntity();
		void setColor(GLfloat, GLfloat, GLfloat);
		auto _getAlteredPositon() -> std::vector<GlPoint>;
		auto _getPosition() -> Position2D;

	};
}

#endif