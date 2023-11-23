#pragma once
#include "DialogDesc.h"
#include <future>
namespace Clone::Windowing
{
	void ShowMessageBox(const MessageDesc& desc);
	std::string ShowOpenDialog(std::string_view filter, void* hWnd);
	std::future<std::string> ShowOpenDialogAsync(std::string_view filter, void* hWnd);
	std::string ShowSaveDialog(std::string_view filter, void* hWnd);
	std::future<std::string> ShowSaveDialogAsync(std::string_view filter, void* hWnd);
}