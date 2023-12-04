#include "TestScene.h"
#include "Core/Game/Entity.h"

TestScene::TestScene(Rendering::RendererPtr renderer) : SceneBase(renderer)
{
    CLONE_INFO(TEST, "Created test scene");
}

bool TestScene::Init()
{
    SceneBase::Init();
    auto e1 = CreateEntity("Test1");
    auto e2 = CreateEntity("Test2");
    auto e3 = CreateEntity("Test3");
    auto e4 = CreateEntity("Test4");
    e1->DestoryThis();
    e2->DestoryThis();
    e3->DestoryThis();
    e4->DestoryThis();
    
    CLONE_INFO(TEST, "Initialized test scene");
    return true;
}

void TestScene::Update(double deltaTime, const Input::Event& e)
{
    SceneBase::Update(deltaTime, e);
    CLONE_INFO(TEST, "Updated test scene");
}

void TestScene::FixedUpdate(double fixedDeltaTime)
{
    SceneBase::FixedUpdate(fixedDeltaTime);
    CLONE_INFO(TEST, "Test scene Fixed Update");
}

void TestScene::Shutdown()
{
    SceneBase::Shutdown();
    CLONE_INFO(TEST, "Shutting down test scene");
}
