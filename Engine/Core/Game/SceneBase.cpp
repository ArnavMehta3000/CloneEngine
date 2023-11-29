#include "SceneBase.h"
#include "Core/Game/Entity.h"
#include "Core/Rendering/Renderer.h"

namespace Clone::Game
{
	SceneBase::SceneBase(Rendering::RendererPtr renderer)
		:
		m_renderer(renderer)
	{}

	SceneBase::~SceneBase()
	{
	}
	
	bool SceneBase::Init()
	{
		CLONE_INFO(SceneBase, "Initializing scene base");
		return true;
	}
	
	void SceneBase::Update(double deltaTime, const Input::Event& e)
	{
		CLONE_INFO(SceneBase, "Updating scene base");
		
	}

	void SceneBase::PostUpdate(double deltaTime, const Input::Event& e)
	{
		CLONE_INFO(SceneBase, "Post updating scene base");
	}
	
	bool SceneBase::Render()
	{
		CLONE_INFO(SceneBase, "Rendering scene base");		
		return false;
	}

	std::shared_ptr<Entity> SceneBase::CreateEntity(std::string_view name, std::shared_ptr<Entity> parentEntity)
	{
		ECS::EntityID id = m_world.NewEntity();
		auto entity = std::make_shared<Entity>(id, this, name);
		
		CLONE_DEBUG(ECS, "Created entity: " + entity->Name);		

		entity->AddComponent<Component::Transform>();
		entity->OnCreate();
		
		return entity;
	}
	
	void SceneBase::DestroyEntity(ECS::EntityID entityId)
	{
		
	}
	
	void SceneBase::DestroyEntity(Entity& entity)
	{
	}
	
	bool SceneBase::PreShutdown()
	{
		CLONE_INFO(SceneBase, "Pre-Shutting down scene base");		
		return false;
	}

	void SceneBase::Shutdown()
	{
		CLONE_INFO(SceneBase, "Shutting down scene base");		
	}
}