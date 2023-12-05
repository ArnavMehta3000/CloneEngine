#include "TestScene.h"
#include "Core/Game/Entity.h"

TestScene::TestScene(Rendering::RendererPtr renderer) : SceneBase(renderer)
{
    CLONE_INFO(TEST, "Created test scene");
}

bool TestScene::Init()
{
    SceneBase::Init();
    auto e1 = CreateEntity("Camera");
    auto c = e1->AddComponent<Component::Camera>();
    CLONE_INFO(TEST, "Initialized test scene");
    return true;
}

void TestScene::Update(double deltaTime, const Input::Event& e)
{
    SceneBase::Update(deltaTime, e);
    auto roster = ECS::RosterView<Component::Camera>(GetWorld());

    for (const ECS::EntityID& id : roster)
    {
        auto tf = GetWorld().Get<Component::Transform>(id);
        auto cam = GetWorld().Get<Component::Camera>(id);
        int x = 0;
    }
}

void TestScene::FixedUpdate(double fixedDeltaTime)
{
    SceneBase::FixedUpdate(fixedDeltaTime);
}

void TestScene::Shutdown()
{
    SceneBase::Shutdown();
}
