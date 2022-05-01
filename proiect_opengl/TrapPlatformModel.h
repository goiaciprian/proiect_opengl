#pragma once

#ifndef TrapPlatformModel_H
#define TrapPlatformModel_H

#include "EntityModel.h"
#include <vector>

namespace pg
{
	class TrapPlatformModel: public EntityModel
	{
		using EntityModel::setRunSpeed;
		using EntityModel::initEntity;
	public:
		using EntityModel::moveLeft;
		using EntityModel::moveRight;
		using EntityModel::renderEntity;
		using EntityModel::operator[];

		void handleEndCondition() override;

		TrapPlatformModel(std::vector<GlPoint>* model, Position2D* pos)
		{
			this->initEntity(model, pos);
			this -> setRunSpeed(0.3f);
			this->setColor(0.0f, 1.0f, 0.0f);
		}
	};
}

#endif