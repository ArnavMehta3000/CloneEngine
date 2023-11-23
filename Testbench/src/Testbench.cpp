#include "Testbench.h"

TestbenchClass::TestbenchClass() : Game::GameBase()
{
}

bool TestbenchClass::Init()
{
	CLONE_DEBUG(Testbench, "Started Testbench initialization");
	
	
	CLONE_DEBUG(Testbench, "Finished Testbench initialization");
	return true;
}

void TestbenchClass::Update(double deltaTime)
{
}

void TestbenchClass::Shutdown()
{
	CLONE_DEBUG(Testbench, "Testbench Shutdown");
}
