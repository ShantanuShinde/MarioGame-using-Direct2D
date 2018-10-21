#pragma once
#include<Windows.h>
#include<d2d1.h>
class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

	template <class T> void SafeRelease(T **ppT)
	{
		if (*ppT)
		{
			(*ppT)->Release();
			*ppT = NULL;
		}
	}

public:
	Graphics();
	~Graphics();

	bool Init(HWND hwnd);
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	inline ID2D1HwndRenderTarget* GetRenderTarget() { return renderTarget; }
	inline ID2D1SolidColorBrush* GetBrush() { return brush; }
	inline ID2D1Factory* GetFactory() { return factory; }

	void Scroll(float scrollX);
	void Retarget() { renderTarget->SetTransform(D2D1::IdentityMatrix()); }
};

