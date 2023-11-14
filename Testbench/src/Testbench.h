#pragma once
#include "Common/Defines.h"
#include "Core/Game/GameBase.h"

using namespace Clone;

class __declspec(dllexport) TestbenchClass : public Clone::Game::GameBase
{
public:
	TestbenchClass() = default;
	~TestbenchClass() override = default;
	bool Init() override;
	void Update(double deltaTime) override;
	void Render() override;
	void Shutdown() override;
};


extern "C"
{
	CLONE_EXPORT Clone::Game::GameBase* CreateGame() { return new TestbenchClass(); }
	CLONE_EXPORT void ReleaseGame(void* gamePtr) { delete gamePtr; }
}