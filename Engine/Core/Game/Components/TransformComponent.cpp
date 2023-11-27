#include "TransformComponent.h"
#include "Core/Game/Entity.h"

namespace Clone::Components
{
	TransformComponent::TransformComponent() : ComponentBase("Transform"),
		Position(0.0f, 0.0f, 0.0f),
		Rotation(0.0f, 0.0f, 0.0f, 0.0f),
		Scale(1.0f),
		WorldMatrix(Math::Matrix::Identity)
	{}
}