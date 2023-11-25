#pragma once
#include "DirectXHeaders.h"
#include "Common/Property.h"
#include "Common/Defines.h"

namespace Clone::Rendering
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool Init(HWND hWnd);
		void Resize(int width, int height);
		
		void Clear(float r, float g, float b, float a = 1.0f);
		void RenderFrame();

		// Enable or disable VSYNC for presenting
		CLONE_AUTO_PROPERTY(bool, IsVsyncEnabled)
		// Flag for checking if the renderer is resizing
		CLONE_AUTO_PROPERTY(bool, IsResizing)

	private:
		GraphicsDevice m_device;
		GraphicsContext m_context;
		GraphicsSwapChain m_swapChain;
		GraphicsRenderTargetView m_renderTarget;
	};

}