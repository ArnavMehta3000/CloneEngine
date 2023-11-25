#include "Testbench.h"

TestbenchClass::TestbenchClass() : Game::GameBase()
{
	// Configure application here
	auto& config = GetAppConfig();
	config.WindowDesc.Title = "Testbench ";
	config.WindowDesc.CanFullscreen = false;
	config.WindowDesc.IsResizable = true;
	config.WindowDesc.Width = 1280;
	config.WindowDesc.Height = 720;
	config.RendererConfig.IsVsyncEnabled = false;
}

bool TestbenchClass::Init()
{
	CLONE_DEBUG(Testbench, "Started Testbench initialization");
		
	CLONE_DEBUG(Testbench, "Finished Testbench initialization");
	return true;
}

void TestbenchClass::Update(double deltaTime, const Input::Event& e)
{
}
 
void TestbenchClass::Shutdown()
{
	CLONE_DEBUG(Testbench, "Testbench Shutdown");
}
