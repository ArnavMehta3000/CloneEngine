#include "Entity.h"
#include <algorithm>
#include <ranges>
#include <execution>
#include "Core/Game/SceneBase.h"

namespace Clone::Game
{
	Entity::Entity(ECS::EntityID id, Game::SceneBase* scene, std::string_view name)
		:
		m_scene(scene),
		m_id(id),
		Name(name)
	{}

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
}