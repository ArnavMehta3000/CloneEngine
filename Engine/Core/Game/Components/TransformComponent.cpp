#include "TransformComponent.h"
#include "Core/Game/Entity.h"

namespace Clone::Component
{
	Transform::Transform(Math::Vector3 position, Math::Quaternion rotation, Math::Vector3 scale) : ComponentBase("Transform"),
		m_Position(position),
		m_Rotation(rotation),
		m_Scale(scale),
		m_parent(nullptr)
	{}

	Transform::~Transform()
	{
		if (m_parent)
		{
			m_parent = nullptr;
		}
	}

	void Transform::SetPosition(const Math::Vector3& position)
	{
		m_Position = position;
		SetAttribute(Attributes::IsDirty, true);
	}

	void Transform::SetRotation(const Math::Quaternion& rotation)
	{
		m_Rotation = rotation;
		SetAttribute(Attributes::IsDirty, true);
	}

	void Transform::SetScale(const Math::Vector3& scale)
	{
		m_Scale = scale;
		SetAttribute(Attributes::IsDirty, true);
	}

	void Transform::AddChild(ECS::EntityID id)
	{
		m_children.insert(id);
		SetAttribute(Attributes::IsDirty, true);
	}

	void Transform::RemoveChild(ECS::EntityID id)
	{
		if (m_children.contains(id))
		{
			m_children.erase(id);
		}
		SetAttribute(Attributes::IsDirty, true);
	}

	const std::unordered_set<ECS::EntityID>& Transform::GetChildren() const
	{
		return m_children;
	}
	
	Transform* Transform::GetParent() const
	{
		return m_parent;
	}

	void Transform::Translate(Math::Vector3 translation)
	{
		m_Position += translation;
		SetAttribute(Attributes::IsDirty, true);
	}
	
}