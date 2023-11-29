#include "TestScene.h"

TestScene::TestScene(Rendering::RendererPtr renderer) : SceneBase(renderer)
{
    CLONE_INFO(TEST, "Created test scene");
}

bool TestScene::Init()
{
    SceneBase::Init();
    CreateEntity("Test1");
    CreateEntity("Test2");
    CreateEntity("Test3");
    CreateEntity("Test4");
    CLONE_INFO(TEST, "Initialized test scene");
    return true;
}

void TestScene::Update(double deltaTime, const Input::Event& e)
{
    SceneBase::Update(deltaTime, e);
    CLONE_INFO(TEST, "Updated test scene");
}

void TestScene::Shutdown()
{
    SceneBase::Shutdown();
    CLONE_INFO(TEST, "Shutting down test scene");
}
