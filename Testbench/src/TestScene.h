#pragma once
#include "Core/Game/SceneBase.h"
using namespace Clone;

class TestScene : public Game::SceneBase
{
public:
	TestScene(Rendering::RendererPtr renderer);

	bool Init() override;
	void Update([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e) override;
	void Shutdown() override;
};