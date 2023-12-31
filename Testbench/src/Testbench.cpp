#include "Testbench.h"

TestbenchClass::TestbenchClass() : Game::GameBase()
{
	// Configure application here
	auto& config = GetAppConfig();

	config.WindowDesc.Title              = "Testbench ";
	config.WindowDesc.CanFullscreen      = false;
	config.WindowDesc.IsResizable        = true;
	config.WindowDesc.Width              = 1280;
	config.WindowDesc.Height             = 720;
	config.RendererConfig.IsVsyncEnabled = true;
}

bool TestbenchClass::Init()
{
	CLONE_DEBUG(Testbench, "Started Testbench initialization");
	m_activeScene = std::make_unique<TestScene>(GetRenderer(), GetAppConfig());
	m_activeScene->Init();
	CLONE_DEBUG(Testbench, "Finished Testbench initialization");
	return true;
}

void TestbenchClass::Update(const double deltaTime, const Input::Event& e)
{
	if (m_activeScene)
	{
		m_activeScene->Update(deltaTime, e);
	}
}

void TestbenchClass::FixedUpdate(const double fixedDeltaTime)
{
	GameBase::FixedUpdate(fixedDeltaTime);
}
 
void TestbenchClass::Shutdown()
{
	CLONE_DEBUG(Testbench, "Testbench Shutdown");
}
