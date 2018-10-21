#pragma once
#include"SpriteSheet.h"
#include"Graphics.h"

class Enemy
{
	SpriteSheet *sprite;
	Graphics *gfx;
	int frame,direction;
	D2D1_RECT_F meshRect;
	ID2D1RectangleGeometry* meshGeom;
public:
	Enemy(Graphics *graphics);
	void Display();
	void Move(double timeDelta,float ySpeed);
	void UpdateMove(double timeDelta,D2D1_RECT_F gmsh,float *ySpeed);
	D2D1_RECT_F GetRect() { return meshRect; }
	ID2D1RectangleGeometry* GetGeom() { return meshGeom; }
	void Init(float x, float y);
	bool PlayerCollision(D2D1_RECT_F plmsh);
	~Enemy();
};

