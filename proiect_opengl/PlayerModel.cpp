#include "PlayerModel.h"

#include <iostream>
#include <memory>

namespace pg
{
	// todo momentan resetam pozitia cel mai probabil vreau sa se modifice state-ul jocului
	void PlayerModel::handleEndCondition()
	{
		this->startJumpBool = false;
		this->onPlatform = false;
		this->setEntityToOrigin();
		this->position_ = Position2D {0 , 0};
	}

	game_entity::GameEntity PlayerModel::getType() 
	{
		return game_entity::GameEntity::PLAYER;
	}

	void PlayerModel::jump()
	{
		auto mxJump = this->positionBeforeJump.y + maxJump;

		if(startJumpBool && this->position_.y < mxJump)
		{
			startJumpBool = true;
			onPlatform = false;
			this->moveUp();
		} else
		{
			startJumpBool = false;
		}
		
	}

	void PlayerModel::fall()
	{
		//-0.8f < position_.y && startFalling
		if(-0.8f < position_.y && !startJumpBool)
		{
			this->moveDown();
		} 
	}

	void PlayerModel::fall(GLfloat stopValue)
	{
		if( stopValue < position_.y)
		{
			this->moveDown();
		} 
	}


	void PlayerModel::startJump()
	{
		positionBeforeJump = this->position_;
		this->onPlatform = false;
		this->startJumpBool = true;
		standingOn = nullptr;
	}


	auto PlayerModel::standingOnPlatform(EntityModel* entity) -> void 
	{

		GLfloat maxTop = -100;
		GLfloat maxBottom = 100;
		GLfloat maxLeft= 100;
		GLfloat maxRight= -100;

		GLfloat thisTop = -100;
		GLfloat thisBottom = 100;
		GLfloat thisLeft = 100;
		GLfloat thisRight = -100;

		for(auto &point : this->_getAlteredPositon()) 
		{
			maxTop = std::fmax(point.y, maxTop);
			maxBottom = std::fmin(point.y, maxBottom);

			maxRight = std::fmax(point.x, maxRight);
			maxLeft = std::fmin(point.x, maxLeft);
		}

		for(auto & point : entity->_getAlteredPositon())
		{
			thisTop = std::fmax(point.y, thisTop);
			thisBottom = std::fmin(point.y, thisBottom);

			thisRight = std::fmax(point.x, thisRight);
			thisLeft = std::fmin(point.x, thisLeft);
		}
		bool topCheck = thisBottom < maxTop;
		bool bottomCheck = thisTop < maxBottom;
		bool leftRight = thisLeft < maxLeft && thisRight > maxRight;

		if(thisBottom < maxTop) 
		{
			this->onPlatform = true;
			this->setAirSpeed(0.002f);
			if(standingOn == nullptr)
				canSetScore = true;
			else if (std::addressof(entity) == std::addressof(standingOn))
				canSetScore = false;
			standingOn = entity;
		} 
		else 
		{
			this->onPlatform = false;
		}

		//if(thisLeft > maxLeft )
		//if(thisRight < maxRight)
		/*if(thisTop < maxBottom)
		{

		}*/


	}
}