#include "Testbench.h"


TestbenchClass::TestbenchClass() : Game::GameBase()
{
}

bool TestbenchClass::Init()
{
	CLONE_INFO(Testbench, "Testbench Init");
	return true;
}

void TestbenchClass::Update(double deltaTime)
{
	CLONE_INFO(Testbench, "Testbench Update");
}

void TestbenchClass::Shutdown()
{
	CLONE_INFO(Testbench, "Testbench Shutdown");
}
