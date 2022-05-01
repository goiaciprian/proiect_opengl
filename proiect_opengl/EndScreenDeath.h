﻿#pragma once

#ifndef EndScreenDeath_H
#define EndScreenDeath_H

#include "EntityModel.h"
#include "Utils.h"
#include <vector>

namespace
{
	std::vector<pg::GlPoint> points
	{
		pg::GlPoint { -1.0f, -0.99f},
		pg::GlPoint { 1.0f, -0.99f},
		pg::GlPoint { 1.0f, -1.2f},
		pg::GlPoint { -1.0f, -1.2f}
	};

	pg::Position2D position { 0, 0};
}

namespace pg
{
	class EndScreenDeath: public EntityModel
	{
	public:
		EndScreenDeath()
		{
			initEntity(&points, &position);
		}

		void handleEndCondition() override {};
	};
}

#endif
