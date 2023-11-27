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
		m_name(name)
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

	void Entity::AddChild(EntityPtr child)
	{
		// Check if the child already has a parent
		if (child->m_parent.lock()) 
		{
			CLONE_WARN(Entity, "Child entity already has a parent. Remove it from the current parent before adding to a new one!");
			return;
		}

		// Set the parent for the child
		child->m_parent = shared_from_this();

		// Add the child to the internal list
		m_children.push_back(child);
	}

	void Entity::RemoveChild(EntityPtr child)
	{
		m_children.remove(child);

		// Remove the parent reference in the child
		if (child->m_parent.lock() == shared_from_this()) 
		{
			child->m_parent.reset();
		}
	}

	void Entity::SetParent(EntityPtr parent)
	{
		if (parent)
		{
			m_parent = parent;
			parent->m_children.push_back(shared_from_this());
		}
		else
		{
			// Remove parent
			if (auto parentSharedPtr = m_parent.lock())
			{
				// Remove the child from the parent's list
				parentSharedPtr->m_children.remove(shared_from_this());

				// Remove the parent reference
				m_parent.reset();
			}
		}
	}

	EntityPtr Entity::GetParent() 
	{
		return m_parent.lock();
	}
}