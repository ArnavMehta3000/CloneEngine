#include "SceneBase.h"
#include "Core/Game/Entity.h"
#include "Core/Rendering/Renderer.h"

namespace Clone::Game
{
	SceneBase::SceneBase(Rendering::RendererPtr renderer, const Config::AppConfig& config)
		:
		m_renderer(renderer),
		m_appConfig(config)
	{}

	SceneBase::~SceneBase()
	{
	}
	
	bool SceneBase::Init()
	{
		// Create base camera
		const auto& desc = GetConfig().WindowDesc;
		m_MainCamera.CreatePerspective(desc.Width, desc.Height, 45.0f, 0.1f, 100.0f);
		return true;
	}
	
	void SceneBase::Update(const double deltaTime, const Input::Event& e)
	{
	}

	void SceneBase::FixedUpdate(const double fixedDeltaTime)
	{
	}

	void SceneBase::OnWindowResize(int width, int height)
	{
	}

	void SceneBase::PostUpdate(double deltaTime, const Input::Event& e)
	{
		std::erase_if(m_entities, [this] (const EntityPtr& entity) 
		{
			if (entity->GetAttribute(Entity::Attribute::NeedsDestroy))
			{
				CLONE_DEBUG(ECS, "Destroying entity: " + entity->Name);
				entity->OnDestroy();
		
				auto transform = entity->GetComponent<Component::Transform>();
		
				if (auto parent = transform->GetParent())
				{
					parent->RemoveChild(entity->GetId());
					transform->SetParent(nullptr);
				}
		
				m_world.DestroyEntity(entity->GetId());
		
				return true;  // Remove the entity
			}
			return false;     // Keep the entity
		});
	}
	
	bool SceneBase::Render()
	{
		return false;
	}

	EntityPtr SceneBase::CreateEntity(std::string_view name, std::shared_ptr<Entity> parentEntity)
	{
		ECS::EntityID id = m_world.NewEntity();
		auto entity = std::make_shared<Entity>(id, this, name);
		m_entities.push_back(entity);

		CLONE_DEBUG(ECS, "Created entity: " + entity->Name);		

		Component::Transform* transform =  entity->AddComponent<Component::Transform>();
		if (parentEntity)
		{
			transform->SetParent(parentEntity->GetComponent<Component::Transform>());
		}
		
		entity->OnCreate();
		
		return entity;
	}
	
	void SceneBase::DestroyEntity(EntityPtr entity)
	{
		entity->SetAttribute(Entity::Attribute::NeedsDestroy, true);
	}

	void SceneBase::SetMainCamera(const Camera& value)
	{
		m_MainCamera = value;
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

	EntityPtr SceneBase::GetEntityFromId(ECS::EntityID id)
	{
		auto it = std::ranges::find_if(m_entities, [id](const EntityPtr& e)
		{
			return e->GetId() == id;
		});

		return it == std::end(m_entities) ? nullptr : *it;
	}
}