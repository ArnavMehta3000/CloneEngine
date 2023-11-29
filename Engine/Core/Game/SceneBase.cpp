#include "SceneBase.h"
#include "Core/Game/Entity.h"

namespace Clone::Game
{
	SceneBase::SceneBase()
	{
		auto e = CreateEntity("Poo poo");
		auto e2 = CreateEntity("Pee pee");
		auto e3 = CreateEntity("Poo pee");
		auto e4 = CreateEntity("Pee poo");

		struct X
		{
			float p;
		};

		auto t = e->AddComponent<Component::Transform>();
		auto t2 = e2->AddComponent<Component::Transform>();
		auto t3 = e3->AddComponent<Component::Transform>();
		auto t4 = e4->AddComponent<Component::Transform>();

		int x = 0;
	}

	SceneBase::~SceneBase()
	{
	}

	std::shared_ptr<Entity> SceneBase::CreateEntity(std::string_view name, std::shared_ptr<Entity> parentEntity)
	{
		ECS::EntityID id = m_world.NewEntity();
		auto entity = std::make_shared<Entity>(id, this, name);
		

		//entity->AddComponent<Components::Transform>();
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