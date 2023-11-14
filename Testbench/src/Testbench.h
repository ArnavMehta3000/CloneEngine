#pragma once
#include <iostream>
#include "EngineAPI/EngineAPI.h"
#define API  __declspec(dllexport)


class API TestbenchClass : public Clone::Game::GameBase
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
	API Clone::Game::GameBase* CreateGame() { return new TestbenchClass(); }
	API void ReleaseGame(void* gamePtr) { delete gamePtr; }
}