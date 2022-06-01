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
		std::vector<GlPoint> _entityModelPoints, _alteredPosition, _renderTexture, _originTexture;
		Position2D position_;

		void initEntity(std::vector<GlPoint>* points, Position2D* position);
		void initEntity(std::vector<GlPoint>* points, std::vector<GlPoint>* texture, Position2D* position);
		void moveLeft();
		void moveRight();
		void moveUp();
		void setEntityToOrigin();
		int frame = 0;
		std::size_t maxFrames = 0;


	public:
		virtual ~EntityModel() {};

		virtual void handleEndCondition() = 0;
		virtual game_entity::GameEntity getType() = 0;

		game_texture::Sprites currentPlayerAnimation = game_texture::Sprites::KNIGHT_IDLE;
		int movingDirection = 0;


		bool operator[] (EntityModel*);
		
		void setRunSpeed(GLfloat);
		void setAirSpeed(GLfloat);
		void moveDown();
		void moveDown(GLfloat);
		void renderEntity();
		void setColor(GLfloat, GLfloat, GLfloat);
		auto _getAlteredPositon() -> std::vector<GlPoint>;
		auto _getPosition() -> Position2D;

	};
}

#endif