#pragma once
#include "Core/Game/ECS/ECS.h"
#include <memory>
#include <list>

namespace Clone::Game
{
	class Entity;
	class SceneBase
	{
	public:
		SceneBase();
		~SceneBase();

		inline ECS::World& GetWorld() { return m_world; }

		std::shared_ptr<Entity> CreateEntity(std::string_view name, std::shared_ptr<Entity> parentEntity = nullptr);
		void DestroyEntity(ECS::EntityID entityId);
		void DestroyEntity(Entity& entity);

	private:
		ECS::World m_world;
	};
}