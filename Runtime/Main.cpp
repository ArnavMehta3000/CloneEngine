#include "Common/CloneWin.h"
#include "Core/Application/Application.h"
#include "Tools/Logger.h"

using namespace Clone::Application;
using namespace Clone::Tools;

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	std::unique_ptr<Application> app = std::make_unique<Application>(hInstance);
	
	app->Init();
	app->Run();

	return 0;
}