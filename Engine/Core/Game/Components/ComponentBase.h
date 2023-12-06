#pragma once
#include "Common/Includes.h"
#include "Math/SimpleMath.h"
#include "Core/Game/ECS/ECS.h"

// Forward declarations
namespace Clone::Input { class Event; }
namespace Clone::Game 
{ 
	class SceneBase; 
	class Entity;
	using EntityPtr = std::shared_ptr<Clone::Game::Entity>;
	using EntityWeakPtr = std::weak_ptr<Clone::Game::Entity>;
}

namespace Clone::Component
{
	struct Attribute
	{
		enum Attr : int
		{
			IsActive,
			IsDirty,
			NeedsDestroy,

			COMPONENT_ATTRIBUTES_COUNT
		};
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
			SetAttribute(Attribute::IsActive, true);
		}

		virtual ~ComponentBase() = default;
		virtual void OnCreate() {}
		virtual void OnUpdate([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e) {}
		virtual void OnDestroy() {}

		CLONE_CONST_GET_ONLY_PROPERTY(std::string, ComponentName);
		CLONE_GET_ONLY_PROPERTY(Game::EntityWeakPtr, Owner);

	protected:
		inline void SetAttribute(int attr, bool value) { m_attributes.set(static_cast<int>(attr), value); }
		inline bool GetAttribute(int attr) const { return m_attributes.test(static_cast<int>(attr)); }

		std::bitset<Attribute::COMPONENT_ATTRIBUTES_COUNT> m_attributes;
	};

	template <typename T>
	concept ConceptComponent = std::is_base_of_v<Clone::Component::ComponentBase, T>;
}