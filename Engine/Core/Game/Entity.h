#pragma once
#include "Core/Game/Components/Components.h"
#include "Core/Game/Scene/SceneBase.h"
#include "Core/Input/Event.h"
#include "Tools/Logger.h"
#include <bitset>

namespace Clone::Game
{
	class SceneBase;
	class Entity;
	using EntityPtr = std::shared_ptr<Clone::Game::Entity>;
	using WeakEntityPtr = std::weak_ptr<Clone::Game::Entity>;

	class Entity : public std::enable_shared_from_this<Entity>
	{
		friend class SceneBase;
	private:
		enum class Attributes : int
		{ 
			IsActive, 
			NeedsDestroy,

			ENTITY_ATRRIBUTES_COUNT
		};
	public:
		Entity(ECS::EntityID id, Game::SceneBase* scene, std::string_view name);
		~Entity();

		void OnCreate();
		void OnDestroy();
		void OnUpdate([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e);

		inline const ECS::EntityID& GetId() const { return m_id; }
		void DestoryThis();

		std::string Name;
		
#pragma region ECS Routing Functions
		template<Component::ConceptComponent T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			if (m_scene->GetWorld().Has<T>(m_id))
			{
				CLONE_WARN(Entity, "Tried to add component, but entity already has this component!");
				return nullptr;
			}

			T* component = m_scene->GetWorld().Assign<T>(m_id, args...);
			component->m_OwnerID = m_id;

			return component;
		}

		template <Component::ConceptComponent T>
		void RemoveComponent()
		{
			m_scene->GetWorld().Remove(m_id);
		}

		template <Component::ConceptComponent T>
		[[nodiscard]] T* GetComponent()
		{
			return m_scene->GetWorld().Get<T>(m_id);
		}

		template <Component::ConceptComponent T>
		bool HasComponent()
		{
			return m_scene->GetWorld().Has<T>();
		}
#pragma endregion

	private:
		inline void SetAttribute(Entity::Attributes attr, bool value) { m_attributes.set(static_cast<int>(attr), value); }
		inline bool GetAttribute(Entity::Attributes attr) const { return m_attributes.test(static_cast<int>(attr)); }

		std::bitset<(int)Attributes::ENTITY_ATRRIBUTES_COUNT> m_attributes;

		SceneBase*     m_scene;
		ECS::EntityID  m_id;
	};

	

	template <typename T>
	concept ConceptEntity = std::is_base_of_v<Clone::Game::Entity, T>;

}