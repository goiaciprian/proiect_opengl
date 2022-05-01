#include "PlayerModel.h"

#include <iostream>

namespace pg
{
	// todo momentan resetam pozitia cel mai probabil vreau sa se modifice state-ul jocului
	void PlayerModel::handleEndCondition()
	{
		this->startJumpBool = false;
		this->startFalling = false;
		this->onPlatform = false;
		this->setEntityToOrigin();
		this->position_ = Position2D {0 , 0};
	}

	void PlayerModel::jump()
	{
		auto mxJump = this->positionBeforeJump.y + maxJump;

		if(startJumpBool && this->position_.y < mxJump)
		{
			this->moveUp();
		} else if (!onPlatform || startJumpBool)
		{
			startJumpBool = false;
			startFalling = true;
		}
		
	}

	void PlayerModel::fall()
	{
		//-0.988f < position_.y &&
		if( startFalling)
		{
			this->moveDown();
		} 
		else
		{
			startFalling = false;
		}
	}

	void PlayerModel::startJump()
	{
		positionBeforeJump = this->position_;
		this->startJumpBool = true;
	}


	auto PlayerModel::standingOnPlatform(EntityModel* entity) -> void 
	{
		this->onPlatform = true;
		this->startFalling = false;
	}
}