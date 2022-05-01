#pragma once

#ifndef PlayerModel_H
#define PlayerModel_H

#include "EntityModel.h"
#include <vector>

namespace pg
{
	class PlayerModel: public EntityModel
	{
		using EntityModel::initEntity;
		using EntityModel::_alteredPosition;
		bool startJumpBool = false, startFalling = false, onPlatform = false;
		Position2D positionBeforeJump;
		
	public:
		using EntityModel::renderEntity;
		using EntityModel::moveLeft;
		using EntityModel::moveRight;
		using EntityModel::moveDown;
		using EntityModel::setEntityToOrigin;
		using EntityModel::operator[];

		void handleEndCondition() override;
		void jump();
		void startJump();
		void fall();
		auto standingOnPlatform(EntityModel*) -> void;

		bool isInAir()
		{
			return this-> startFalling || startJumpBool;
		}

		PlayerModel(std::vector<GlPoint>* points, Position2D* pos)
		{
			this->initEntity(points, pos);
			this->setColor(1.0f, 0.0f, 0.0f);
		}
	};

}

#endif