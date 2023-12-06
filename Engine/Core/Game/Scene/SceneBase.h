#pragma once
#include "Common/Includes.h"
#include "Core/Game/ECS/ECS.h"
#include "Core/Input/Event.h"
#include "Config/AppConfig.h"
#include "Core/Game/Camera.h"

// Forward declare renderer
namespace Clone::Rendering 
{
	class Renderer; 
	using RendererPtr = std::shared_ptr<Renderer>;
}

namespace Clone::Game
{
	// Forward declarations
	class GameBase;
	class Entity;
	using EntityPtr = std::shared_ptr<Clone::Game::Entity>;
	using EntityWeakPtr = std::weak_ptr<Clone::Game::Entity>;


	class SceneBase
	{
		friend class GameBase;
	public:
		SceneBase(Rendering::RendererPtr renderer, const Config::AppConfig& config);
		~SceneBase();

		virtual bool Init();
		virtual void Update([[maybe_unused]] const double deltaTime, [[maybe_unused]] const Input::Event& e);
		virtual void FixedUpdate([[maybe_unused]] const double fixedDeltaTime);
		virtual void OnWindowResize(int width, int height);
		virtual void Shutdown();

		EntityPtr GetEntityFromId(ECS::EntityID id);
		inline ECS::World& GetWorld() { return m_world; }
		inline const Config::AppConfig& GetConfig() const { return m_appConfig; }
		inline Rendering::RendererPtr GetRenderer() const { return m_renderer; }

		[[nodiscard]]
		EntityPtr CreateEntity(std::string_view name, std::shared_ptr<Entity> parentEntity = nullptr);
		void DestroyEntity(EntityPtr entity);

		CLONE_CONST_PROPERTY(Camera, MainCamera);

	private:
		ECS::World m_world;
		const Config::AppConfig& m_appConfig;
		std::vector<EntityPtr> m_entities;
		Rendering::RendererPtr m_renderer{ nullptr };

		void PostUpdate([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e);
		bool Render();
		bool PreShutdown();
	};
}