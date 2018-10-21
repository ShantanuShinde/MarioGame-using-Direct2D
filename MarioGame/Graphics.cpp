#include "Graphics.h"



Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
}

Graphics::~Graphics()
{
	SafeRelease(&factory);
	SafeRelease(&renderTarget);
	SafeRelease(&brush);
}

bool Graphics::Init(HWND hwnd)
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	RECT rect;
	GetClientRect(hwnd, &rect);

	if (SUCCEEDED(hr))
	{
		hr = factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				hwnd, D2D1::SizeU(rect.right, rect.bottom)
			),
			&renderTarget
		);

		if (SUCCEEDED(hr))
		{
			hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(1, 0, 0, 0), &brush);

			if (hr != S_OK)
				return false;
		}
		else
			return false;
	}
	else
		return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b,0.25f));
}

void Graphics::Scroll(float scrollX)
{
	renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(scrollX, 0));
}