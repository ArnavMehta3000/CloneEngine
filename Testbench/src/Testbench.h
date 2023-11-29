#pragma once
#include "Core/Game/GameBase.h"
#include "TestScene.h"
using namespace Clone;

class CLONE_EXPORT TestbenchClass : public Game::GameBase
{
public:
	TestbenchClass();
	~TestbenchClass() override = default;

	bool Init() override;
	void Update([[maybe_unused]] const double deltaTime, [[maybe_unused]] const Input::Event& e) override;
	void FixedUpdate([[maybe_unused]] const double fixedDeltaTime) override;
	void Shutdown() override;
};


extern "C"
{
	CLONE_EXPORT Clone::Game::GameBase* CreateGame() { return new TestbenchClass(); }
	CLONE_EXPORT void ReleaseGame(void* gamePtr) { delete gamePtr; }
}