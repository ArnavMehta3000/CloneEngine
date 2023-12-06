#pragma once
#include "Core/Game/Components/ComponentBase.h"
#include <unordered_set>

namespace Clone::Component
{
	class Transform : public ComponentBase
	{
	public:
		Transform(Math::Vector3 position = Math::Vector3::Zero,
			Math::Quaternion rotation = Math::Quaternion::Identity,
			Math::Vector3 scale = Math::Vector3::One);
		~Transform() override;
		
		void AddChild(ECS::EntityID id);
		void RemoveChild(ECS::EntityID id);
		const std::unordered_set<ECS::EntityID>& GetChildren() const;
		Transform* GetParent() const;
		void SetParent(Transform* parent);

		// TODO: add world or local space param
		void Translate(Math::Vector3 translation);

		CLONE_CONST_PROPERTY(Math::Vector3, Position);
		CLONE_CONST_PROPERTY(Math::Quaternion, Rotation);
		CLONE_CONST_PROPERTY(Math::Vector3, Scale);
		CLONE_CONST_GET_ONLY_PROPERTY(Math::Matrix, WorldMatrix);

	private:
		Transform* m_parent;
		std::unordered_set<ECS::EntityID> m_children;
	};
}