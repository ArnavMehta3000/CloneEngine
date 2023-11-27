#pragma once
#include "Core/Game/Components/ComponentBase.h"
#include <list>



namespace Clone::Components
{
	struct TransformComponent : public ComponentBase
	{
		TransformComponent();

		Math::Vector3 Position;
		Math::Quaternion Rotation;
		Math::Vector3 Scale;
		Math::Matrix WorldMatrix;
	};
}