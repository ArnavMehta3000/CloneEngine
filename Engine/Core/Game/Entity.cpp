#include "Entity.h"
#include "Core/Game/Scene/SceneBase.h"

namespace Clone::Game
{
	Entity::Entity(ECS::EntityID id, Game::SceneBase* scene, std::string_view name)
		:
		m_scene(scene),
		m_id(id),
		Name(name)
	{
		SetAttribute(Attribute::IsActive, true);
		SetAttribute(Attribute::NeedsDestroy, false);
	}

	Entity::~Entity()
	{
		m_scene = nullptr;
	}

	void Entity::OnCreate()
	{
	}

	void Entity::OnDestroy()
	{
	}

	void Entity::OnUpdate(double deltaTime, const Input::Event& e)
	{
	}

	void Entity::DestoryThis()
	{
		SetAttribute(Attribute::NeedsDestroy, true);
	}
}