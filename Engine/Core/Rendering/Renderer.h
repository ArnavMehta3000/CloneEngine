#pragma once
#include "DirectXHeaders.h"
#include "Common/Property.h"

namespace Clone::Rendering
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool Init(HWND hWnd);
		void Resize(int width, int height);
		void Render();

		// Enable or disable VSYNC for presenting
		CLONE_AUTO_PROPERTY(bool, IsVsyncEnabled)
		// Flag for checking if the renderer is resizing
		CLONE_AUTO_PROPERTY(bool, IsResizing)

	private:
		ComPtr<ID3D11Device1> m_device;
		ComPtr<ID3D11DeviceContext1> m_context;
		ComPtr<IDXGISwapChain1> m_swapChain;
		ComPtr<ID3D11RenderTargetView> m_renderTarget;
	};
}