#include "Renderer.h"
#include "Tools/Logger.h"

namespace Clone::Rendering
{
	Renderer::Renderer()
		:
		m_device(nullptr),
		m_context(nullptr),
		m_swapChain(nullptr),
		m_IsVsyncEnabled(false),
		m_IsResizing(false)
	{
	}

	Renderer::~Renderer()
	{
	}

	bool Renderer::Init(HWND hWnd)
	{
		HRESULT hr = E_FAIL;
		// Define temporary pointers to a device and a device context
		ComPtr<ID3D11Device> dev11;
		ComPtr<ID3D11DeviceContext> devcon11;

		// Create the device and device context objects
		hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&dev11,
			nullptr,
			&devcon11);

		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to create D3D11 Device");
			return false;
		}

		// Convert the pointers from the DirectX 11 versions to the DirectX 11.1 versions
		hr = dev11.As(&m_device);
		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to get DX 11.1 device");
			return false;
		}

		hr = devcon11.As(&m_context);
		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to get DX11.1 context");
			return false;
		}

		// Convert ID3D11Device1 into an IDXGIDevice1
		ComPtr<IDXGIDevice1> dxgiDevice;
		hr = m_device.As(&dxgiDevice);
		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to get ID3D11Device1 as IDXGIDevice");
			return false;
		}

		// Use the IDXGIDevice1 interface to get access to the adapter
		ComPtr<IDXGIAdapter> dxgiAdapter;
		hr = dxgiDevice->GetAdapter(&dxgiAdapter);
		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to get device adapter");
			return false;
		}

		// Use the IDXGIAdapter interface to get access to the factory
		ComPtr<IDXGIFactory2> dxgiFactory;
		hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);
		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to get device adapter parent");
			return false;
		}

		// set up the swap chain description
		DXGI_SWAP_CHAIN_DESC1 scd = { 0 };
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 2;
		scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		scd.SampleDesc.Count = 1;

		hr = dxgiFactory->CreateSwapChainForHwnd(
			m_device.Get(),
			hWnd,
			&scd,
			nullptr,
			nullptr,
			&m_swapChain);

		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to create swapchain for HWND");
			return false;
		}

		// Get a pointer directly to the back buffer
		ComPtr<ID3D11Texture2D> backbuffer;
		hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backbuffer);
		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to get back buffer texture");
			return false;
		}

		// Create a render target pointing to the back buffer
		hr = m_device->CreateRenderTargetView(backbuffer.Get(), nullptr, &m_renderTarget);
		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to create render target view of back buffer");
			return false;
		}

		// Get window rect
		RECT rc{};
		GetClientRect(hWnd, &rc);

		// Set viewport
		D3D11_VIEWPORT vp;
		vp.Width = float(rc.right - rc.left);
		vp.Height = float(rc.bottom - rc.top);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_context->RSSetViewports(1, &vp);

		return true;
	}

	void Renderer::Resize(int width, int height)
	{
		if (!m_swapChain)
		{
			CLONE_ERROR(Renderer, "Invalid swapchain when trying to resize");
			return;
		}

		IsResizing = true;
		HRESULT hr = E_FAIL;

		m_context->OMSetRenderTargets(0, 0, 0);
		m_renderTarget->Release();
		// Preserve the existing buffer count and format.
		// Automatically choose the width and height to match the client rect for HWNDs.
		hr = m_swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		if (FAILED(hr))
		{
			CLONE_FATAL(Renderer, "Failed to resize DX11 swapchain buffers");
		}

		// Get a pointer directly to the back buffer
		ComPtr<ID3D11Texture2D> backbuffer;
		hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backbuffer);
		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to get back buffer texture");
		}

		// Create a render target pointing to the back buffer
		hr = m_device->CreateRenderTargetView(backbuffer.Get(), nullptr, m_renderTarget.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			CLONE_ERROR(Renderer, "Failed to create render target view of back buffer");
		}

		D3D11_VIEWPORT vp{};
		vp.Width = (float)width;
		vp.Height = (float)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_context->RSSetViewports(1, &vp);

		CLONE_DEBUG(Renderer, std::format("Successfully resized renderer swapchain. Size: {0}x{1}",
			width, height));

		IsResizing = false;
	}

	void Renderer::Render()
	{
		if (IsResizing)
			return;

		m_context->OMSetRenderTargets(1, m_renderTarget.GetAddressOf(), nullptr);

		float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
		m_context->ClearRenderTargetView(m_renderTarget.Get(), color);

		m_swapChain->Present(IsVsyncEnabled ? 1 : 0 , 0);
	}
}