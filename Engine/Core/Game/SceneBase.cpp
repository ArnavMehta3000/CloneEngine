#include "SceneBase.h"
#include "Core/Game/Entity.h"

namespace Clone::Game
{
	SceneBase::SceneBase()
	{
		auto e = CreateEntity("Poo poo");
		auto e2 = CreateEntity("Pee pee");

		e2->SetParent(e);
		e2->SetParent(nullptr);
		e->AddChild(e2);
		e->AddChild(e2);

		int x = 0;
	}

	SceneBase::~SceneBase()
	{
	}

	std::shared_ptr<Entity> SceneBase::CreateEntity(std::string_view name, std::shared_ptr<Entity> parentEntity)
	{
		ECS::EntityID id = m_world.NewEntity();
		auto entity = std::make_shared<Entity>(id, this, name);
		
		if (parentEntity != nullptr)
			entity->SetParent(parentEntity);

		entity->AddComponent<Components::TransformComponent>();
		entity->OnCreate();

		return entity;
	}
	
	void SceneBase::DestroyEntity(ECS::EntityID entityId)
	{
	}
	
	void SceneBase::DestroyEntity(Entity& entity)
	{
	}
}