#include "TrapPlatformModel.h"

namespace pg
{
	void TrapPlatformModel::handleEndCondition()
	{
		this->setEntityToOrigin();
	}

	game_entity::GameEntity TrapPlatformModel::getType()
	{
		return game_entity::GameEntity::ROCK;
	}

}
