#include "Dialogs.h"
#include "Tools/StringHelper.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>  // Cannot use clone win here (prsht.h errors)
#include <commdlg.h>
namespace Clone::Windowing
{
	void ShowMessageBox(const MessageDesc& desc)
	{
		UINT flags = MB_APPLMODAL | MB_SETFOREGROUND | MB_OK;

		// Set icon based on type
		if (desc.Type == MessageType::Info)
			flags |= MB_ICONINFORMATION;
		else if (desc.Type == MessageType::Warning)
			flags |= MB_ICONWARNING;
		else if (desc.Type == MessageType::Error)
			flags |= MB_ICONERROR;

		MessageBoxA(nullptr, desc.Text.data(), desc.Title.data(), flags);
	}

	std::string ShowOpenDialog(std::string_view filter, void* hWnd)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = (HWND)hWnd;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter.data();
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn))
		{
			return ofn.lpstrFile;
		}

		return std::string();
	}

	std::future<std::string> ShowOpenDialogAsync(std::string_view filter, void* hWnd)
	{
		return std::async(std::launch::async, [filter, hWnd] {return ShowOpenDialog(filter, hWnd); });
	}

	std::string ShowSaveDialog(std::string_view filter, void* hWnd)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = (HWND)hWnd;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter.data();
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileNameA(&ofn))
		{
			return ofn.lpstrFile;
		}

		return std::string();
	}

	std::future<std::string> ShowSaveDialogAsync(std::string_view filter, void* hWnd)
	{
		return std::async(std::launch::async, [filter, hWnd] {return ShowSaveDialog(filter, hWnd); });
	}

}