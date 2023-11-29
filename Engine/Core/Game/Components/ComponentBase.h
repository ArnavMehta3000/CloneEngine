#pragma once
#include "Math/SimpleMath.h"
#include "Common/Property.h"
#include "Core/Game/ECS/ECS.h"
#include <string>
#include <memory>
#include <type_traits>
#include <bitset>

namespace Clone::Game { class Entity; class SceneBase; }

namespace Clone::Component
{
	enum class Attributes : int
	{
		IsActive,
		IsDirty,
		NeedsDestroy,

		COMPONENT_ATTRIBUTES_COUNT
	};

	class ComponentBase
	{
		friend class Clone::Game::Entity;
		friend class Clone::Game::SceneBase;
	public:
		ComponentBase(std::string_view name)
			:
			m_ComponentName(name)
		{
			m_OwnerID = CLONE_INVALID_ENTITY;
			SetAttribute(Attributes::IsActive, true);
		}

		virtual ~ComponentBase() {}

		CLONE_CONST_GET_ONLY_PROPERTY(std::string, ComponentName);
		CLONE_CONST_GET_ONLY_PROPERTY(ECS::EntityID, OwnerID);

	protected:
		inline void SetAttribute(Component::Attributes attr, bool value) { m_attributes.set(static_cast<int>(attr), value); }
		inline bool GetAttribute(Component::Attributes attr) const { return m_attributes.test(static_cast<int>(attr)); }

		std::bitset<(int)Attributes::COMPONENT_ATTRIBUTES_COUNT> m_attributes;
	};

	template <typename T>
	concept ConceptComponent = std::is_base_of_v<Clone::Component::ComponentBase, T>;
}