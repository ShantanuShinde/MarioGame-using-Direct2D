#include "Ground.h"

Ground::Ground(Graphics* graphics)
{
	gfx = graphics;
	movingUp = false;
	moveUpFrames = 0;
	

}

void Ground::Init(float x,float y,float height,float width,const wchar_t* filename, int fx,int fy)
{
	sprite = new SpriteSheet(filename, gfx, fx, fy);
	mesh = D2D1::RectF(x, y, x + width, y + height);
	gfx->GetFactory()->CreateRectangleGeometry(mesh, &boundary);
}


Ground::~Ground()
{
	delete sprite, gfx;
}

bool Ground::DetectCollision(D2D1_RECT_F other)
{
	ID2D1RectangleGeometry* obj;
	D2D1_GEOMETRY_RELATION relation;
	gfx->GetFactory()->CreateRectangleGeometry(other, &obj);
	
	HRESULT hr = boundary->CompareWithGeometry(obj, D2D1::IdentityMatrix(), &relation);
	return(relation !=D2D1_GEOMETRY_RELATION_DISJOINT);
	delete obj;
}
void Ground::MoveUp()
{
	movingUp = true;
	mesh.top -= 5.0f;
	mesh.bottom -= 5.0f;
}

void Ground::Display()//float x, float y,float width,float height)
{
	//HRESULT hr = gfx->GetFactory()->CreateRectangleGeometry(D2D1::RectF(x, y, x + width, y + height), &mesh);
	if (movingUp)
	{
		moveUpFrames++;
	}
	if (moveUpFrames > 1)
	{
		movingUp = false;
		moveUpFrames = 0;
		mesh.top += 5.0f;
		mesh.bottom += 5.0f;
	}
	sprite->Draw(0, mesh);
}