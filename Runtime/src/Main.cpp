#include "Common/CloneWin.h"
#include "Core/Application/Application.h"
#include "Utilities/Logger.h"

using namespace Clone::Application;
using namespace Clone::Utls;

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	// Init logger
	Logger::Get().AddSink(std::make_unique<VSOutputSink>());

	Application app(hInstance);
	app.Run();

	
	return 0;
}