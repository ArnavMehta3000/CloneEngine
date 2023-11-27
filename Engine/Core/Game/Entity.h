#pragma once
#include "Core/Game/Components/Components.h"
#include "Core/Game/ECS/ECS.h"
#include "Core/Game/SceneBase.h"
#include "Core/Input/Event.h"
#include "Tools/Logger.h"
#include <list>

namespace Clone::Game
{
	class SceneBase;
	class Entity;
	using EntityPtr = std::shared_ptr<Clone::Game::Entity>;
	using WeakEntityPtr = std::weak_ptr<Clone::Game::Entity>;

	class Entity : public std::enable_shared_from_this<Entity>
	{
		friend class SceneBase;
	public:
		Entity(ECS::EntityID id, Game::SceneBase* scene, std::string_view name);
		~Entity();

		void OnCreate();
		void OnDestroy();
		void OnUpdate([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e);

		void AddChild(EntityPtr child);
		void RemoveChild(EntityPtr child);
		void SetParent(EntityPtr parent);
		EntityPtr GetParent();
		inline std::list<EntityPtr>& GetChildren() { return m_children; };

#pragma region ECS Routing Functions
		template<Components::ConceptComponent T, typename... Args>
		void AddComponent(Args&&... args)
		{
			if (m_scene->GetWorld().Has<T>(m_id))
			{
				CLONE_WARN(Entity, "Tried to add component, but entity already has this component!");
				return;
			}

			m_scene->GetWorld().Assign<T>(m_id, args...);
		}
		template <Components::ConceptComponent T>
		void RemoveComponent()
		{
			m_scene->GetWorld().Remove(m_id);
		}
		template <Components::ConceptComponent T>
		[[nodiscard]] T* GetComponent()
		{
			return m_scene->GetWorld().Get<T>();
		}
		template <Components::ConceptComponent T>
		bool HasComponent()
		{
			return m_name->GetWorld().Has<T>();
		}
#pragma endregion


		inline const std::string& GetName() const { return m_name; }
		inline void SetName(std::string_view name) { m_name = name; }


	private:
		SceneBase*           m_scene;
		ECS::EntityID        m_id;
		std::string          m_name;
		WeakEntityPtr        m_parent;
		std::list<EntityPtr> m_children;
	};

	

	template <typename T>
	concept ConceptEntity = std::is_base_of_v<Clone::Game::Entity, T>;

}