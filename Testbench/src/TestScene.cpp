#include "TestScene.h"
#include "Core/Game/Entity.h"

TestScene::TestScene(Rendering::RendererPtr renderer, const Config::AppConfig& config) : SceneBase(renderer, config)
{
    CLONE_INFO(TEST, "Created test scene");
}

bool TestScene::Init()
{
    SceneBase::Init();
    const auto& wndDesc = GetConfig().WindowDesc;



    CLONE_INFO(TEST, "Initialized test scene");
    return true;
}

void TestScene::Update(double deltaTime, const Input::Event& e)
{
    SceneBase::Update(deltaTime, e);
}

void TestScene::FixedUpdate(double fixedDeltaTime)
{
    SceneBase::FixedUpdate(fixedDeltaTime);
}

void TestScene::OnWindowResize(int width, int height)
{
    SceneBase::OnWindowResize(width, height);
}

void TestScene::Shutdown()
{
    SceneBase::Shutdown();
}
