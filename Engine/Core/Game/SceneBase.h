#pragma once
#include "Core/Game/ECS/ECS.h"
#include "Core/Input/Event.h"
#include "Tools/Logger.h"
#include <memory>
#include <list>

// Forward declare renderer
namespace Clone::Rendering 
{
	class Renderer; 
	using RendererPtr = std::shared_ptr<Renderer>;
}

namespace Clone::Game
{
	class Entity;
	class GameBase;

	class SceneBase
	{
		friend class GameBase;
	public:
		SceneBase(Rendering::RendererPtr renderer);
		~SceneBase();

		virtual bool Init();
		virtual void Update([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e);
		virtual void Shutdown();

		inline ECS::World& GetWorld() { return m_world; }
		inline Rendering::RendererPtr GetRenderer() const { return m_renderer; }

		std::shared_ptr<Entity> CreateEntity(std::string_view name, std::shared_ptr<Entity> parentEntity = nullptr);
		void DestroyEntity(ECS::EntityID entityId);
		void DestroyEntity(Entity& entity);

	private:
		ECS::World m_world;
		Rendering::RendererPtr m_renderer{ nullptr };

		void PostUpdate([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e);
		bool Render();
		bool PreShutdown();
	};
}