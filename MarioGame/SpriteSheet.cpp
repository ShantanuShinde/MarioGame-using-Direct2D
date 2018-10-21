#include "SpriteSheet.h"
#include "Graphics.h"
#include<sstream>


SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr;

	//Create WIC factory
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,

		(LPVOID*)&wicFactory);
	if (SUCCEEDED(hr))
	{
		//Create decoder
		IWICBitmapDecoder* wicDecoder = NULL;
		hr = wicFactory->CreateDecoderFromFilename(
			filename,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&wicDecoder
		);

		if (SUCCEEDED(hr))
		{
			//Read frame from the image
			IWICBitmapFrameDecode* wicFrame = NULL;
			hr = wicDecoder->GetFrame(0, &wicFrame);
			
			if (SUCCEEDED(hr))
			{
				
				//Create a converter;
				IWICFormatConverter* wicConverter = NULL;
				hr = wicFactory->CreateFormatConverter(&wicConverter);

				if (SUCCEEDED(hr))
				{
					hr = wicConverter->Initialize(
						wicFrame,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.0,
						WICBitmapPaletteTypeCustom
					);
					
					if (SUCCEEDED(hr))
					{

						hr = gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
							wicConverter,
							NULL,
							&bmp
						);
					}
					
				}
				SafeRelease(&wicConverter);
			}
			SafeRelease(&wicFrame);
			
		}
		SafeRelease(&wicDecoder);
	}
	SafeRelease(&wicFactory);

	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
	spritesAccross = 1;

	
}

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx, float spriteWidth, float spriteHeight) :SpriteSheet(filename, gfx)
{
	this->spriteHeight = spriteHeight;
	this->spriteWidth = spriteWidth;
	this->spritesAccross = (int)bmp->GetSize().width / spriteWidth;
	
}
SpriteSheet::~SpriteSheet()
{
	SafeRelease(&bmp);
	
}

void SpriteSheet::Draw()
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_FORCE_DWORD,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height)
	);

}

void SpriteSheet::Draw(int index,D2D1_RECT_F rect)
{
	D2D1_RECT_F src = D2D1::RectF(
		(float)((index%spritesAccross)*spriteWidth),
		(float)((index / spriteHeight)*spriteHeight),
		(float)((index%spritesAccross)*spriteWidth + spriteWidth),
		(float)((index / spriteHeight)*spriteHeight + spriteHeight)
	);

	

	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		rect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		src
		);

	
}
