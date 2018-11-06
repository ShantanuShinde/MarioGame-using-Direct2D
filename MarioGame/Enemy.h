#pragma once
#include"SpriteSheet.h"
#include"Graphics.h"
#include "Player.h"
#include<sstream>

class Enemy
{
	
	SpriteSheet *sprite;
	Graphics *gfx;
	int frame,direction;
	D2D1_RECT_F meshRect;
	ID2D1RectangleGeometry* meshGeom;
	bool Dead;
	int deadFrames;
public:
	Enemy(Graphics *graphics);
	void Display();
	void Move(double timeDelta,float ySpeed); //move goomba
	void UpdateMove(double timeDelta,D2D1_RECT_F gmsh,float *ySpeed); //check collisions
	D2D1_RECT_F GetRect() { return meshRect; }
	ID2D1RectangleGeometry* GetGeom() { return meshGeom; }
	void Init(float x, float y); //initialize position
	void PlayerCollision(Player **p,float &ySpeed);	//check for collision with player
	bool isDead() { return Dead; }
	~Enemy();
};

