#pragma once

// DX11 includes
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11_4.h>
#include <wrl/client.h>

template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// Library links;
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3DCompiler.lib")

// Rendering aliases
namespace Clone::Rendering
{
	using GraphicsDevice = ComPtr<ID3D11Device1>;
	using GraphicsContext = ComPtr<ID3D11DeviceContext1>;
	using GraphicsSwapChain = ComPtr<IDXGISwapChain1>;
	using GraphicsRenderTargetView = ComPtr<ID3D11RenderTargetView>;
}