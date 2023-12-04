#pragma once
#include "Core/Game/Scene/SceneBase.h"

using namespace Clone;

class TestScene : public Game::SceneBase
{
public:
	TestScene(Rendering::RendererPtr renderer);

	bool Init() override;
	void Update([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e) override;
	void FixedUpdate([[maybe_unused]] double fixedDeltaTime) override;
	void Shutdown() override;
};