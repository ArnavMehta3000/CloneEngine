#pragma once
#include <iostream>
#include "Core/Game/GameBase.h"


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
	__declspec(dllexport) Clone::Game::GameBase* CreateGame() { return new TestbenchClass(); }
	__declspec(dllexport) void ReleaseGame(void* gamePtr) { delete gamePtr; }
}