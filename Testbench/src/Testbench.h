#pragma once
#include "Core/Game/GameBase.h"

using namespace Clone;

class CLONE_EXPORT TestbenchClass : public Game::GameBase
{
public:
	TestbenchClass();
	~TestbenchClass() override = default;
	bool Init() override;
	void Update(double deltaTime) override;
	void Shutdown() override;
};


extern "C"
{
	CLONE_EXPORT Clone::Game::GameBase* CreateGame() { return new TestbenchClass(); }
	CLONE_EXPORT void ReleaseGame(void* gamePtr) { delete gamePtr; }
}