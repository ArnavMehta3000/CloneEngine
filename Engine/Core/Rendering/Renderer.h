#pragma once
#include "Common/Includes.h"
#include "DirectXHeaders.h"

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

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }

		// Enable or disable VSYNC for presenting
		CLONE_AUTO_PROPERTY(bool, IsVsyncEnabled)
		// Flag for checking if the renderer is resizing
		CLONE_AUTO_PROPERTY(bool, IsResizing)

	private:
		GraphicsDevice           m_device;
		GraphicsContext          m_context;
		GraphicsSwapChain        m_swapChain;
		GraphicsRenderTargetView m_renderTarget;

		int m_width;
		int m_height;
	};

	using RendererPtr = std::shared_ptr<Renderer>;
}