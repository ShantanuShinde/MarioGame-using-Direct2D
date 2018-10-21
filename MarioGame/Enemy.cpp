#include "Enemy.h"


Enemy::Enemy(Graphics* gfx)
{
	this->gfx = gfx;
	sprite = new SpriteSheet(L"enemy.png", gfx,32,32);
	frame = 0;
	direction = 1;
}

void Enemy::Init(float x, float y)
{
	meshRect = D2D1::RectF(x - 15, y - 15, x, y);
	HRESULT hr = gfx->GetFactory()->CreateRectangleGeometry(meshRect, &meshGeom);
}
void Enemy::Move(double timeDelta,float ySpeed)
{
	meshRect.left += float(direction*30.0f)*timeDelta;
	meshRect.right += float(direction*30.0f)*timeDelta;
	meshRect.top += ySpeed;
	meshRect.bottom += ySpeed;
	HRESULT hr = gfx->GetFactory()->CreateRectangleGeometry(meshRect, &meshGeom);
}
void Enemy::UpdateMove(double timeDelta,D2D1_RECT_F gmsh,float *ySpeed)
{
	if (meshRect.bottom>=gmsh.top&&meshRect.bottom<gmsh.bottom&&meshRect.top<gmsh.top)
	{
		meshRect.bottom =gmsh.top;
		meshRect.top =gmsh.top-15;
		
		*ySpeed = 0;
	}
	else
	{
		direction *= -1;
		meshRect.left += float(direction*30.0f)*timeDelta;
		meshRect.right += float(direction*30.0f)*timeDelta;
	}
	
	HRESULT hr  = gfx->GetFactory()->CreateRectangleGeometry(meshRect, &meshGeom);
}
bool Enemy::PlayerCollision(D2D1_RECT_F plmsh)
{
	ID2D1RectangleGeometry* pGeom;
	HRESULT hr = gfx->GetFactory()->CreateRectangleGeometry(plmsh, &pGeom);
	D2D1_GEOMETRY_RELATION relation;
	hr = pGeom->CompareWithGeometry(meshGeom, D2D1::IdentityMatrix(), &relation);
	if (relation == D2D1_GEOMETRY_RELATION_OVERLAP)
	{
		if (plmsh.bottom >= meshRect.top&&plmsh.top < meshRect.top)
			return true;
			
	}
	return false;
}
void Enemy::Display()
{
	frame++;
	sprite->Draw((frame/10)%2, meshRect);
}

Enemy::~Enemy()
{
	delete gfx;
	delete sprite;
}
