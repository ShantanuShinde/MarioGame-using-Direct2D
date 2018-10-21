#pragma once
#include "Graphics.h"
#include<wincodec.h>

	class SpriteSheet
	{
		template <class T> void SafeRelease(T **ppT)
		{
			if (*ppT)
			{
				(*ppT)->Release();
				*ppT = NULL;
			}
		}

		Graphics* gfx;
		ID2D1Bitmap* bmp;
		float spriteWidth, spriteHeight;
		int spritesAccross;

	public:
		SpriteSheet(const wchar_t* filename, Graphics* gfx);
		SpriteSheet(const wchar_t* filename, Graphics* gfx, float spriteWidth, float spriteHeight);
		~SpriteSheet();

		void Draw();
		void Draw(int index,D2D1_RECT_F rect);
		//void Draw(int index, float x, float y);
	};

