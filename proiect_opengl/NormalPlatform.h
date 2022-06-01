#pragma once

#ifndef NormalPlatform_H
#define NormalPlatform_H

#include "EntityModel.h"
#include "Utils.h"
#include <vector>

namespace pg 
{
	class NormalPlatform: public EntityModel
	{
	public:
		void handleEndCondition() override 
		{
			this->setEntityToOrigin();
		};

		game_entity::GameEntity getType() override 
		{
			return game_entity::GameEntity::FRUIT;
		};

		NormalPlatform(std::vector<GlPoint>* points, Position2D* pos)
		{
			initEntity(points, pos);
			this->setColor(0.0f, 0.0f, 1.0f);
		}
	};
};

#endif // !NormalPlatform_H
