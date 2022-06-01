#pragma once

#ifndef PlayerModel_H
#define PlayerModel_H

#include "EntityModel.h"
#include <vector>

namespace pg
{
	class PlayerModel: public EntityModel
	{
		using EntityModel::_renderTexture;
		using EntityModel::initEntity;
		using EntityModel::_alteredPosition;
		bool startJumpBool = false, onPlatform = false;
		EntityModel *standingOn = nullptr;
		Position2D positionBeforeJump;
		
	public:
		using EntityModel::renderEntity;
		using EntityModel::moveLeft;
		using EntityModel::moveRight;
		using EntityModel::moveDown;
		using EntityModel::setEntityToOrigin;
		using EntityModel::operator[];

		bool canSetScore = false;

		void handleEndCondition() override;
		game_entity::GameEntity getType() override;
		void jump();
		void startJump();
		void fall();
		void fall(GLfloat);
		auto standingOnPlatform(EntityModel*) -> void;

		bool isInAir()
		{
			return  (startJumpBool && !onPlatform);
 		}

		bool isOnPlatform()
		{
			return onPlatform;
		}

		PlayerModel(std::vector<GlPoint>* points, std::vector<GlPoint>* textures,  Position2D* pos)
		{
			this->initEntity(points, textures, pos);
			this->setColor(1.0f, 0.0f, 0.0f);
		}
	};

}

#endif