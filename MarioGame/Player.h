#pragma once
#include"SpriteSheet.h"
#include "Graphics.h"
class Player
{
	static int lives;
	static int score;
	SpriteSheet* sprite;
	Graphics* gfx;
	D2D1_RECT_F mesh,boundBox;
	float scrollX = 0;
public:
	Player(Graphics* graphics,float x, float y);
	void Display(int index, float x, float y,bool walkingForward,bool walkingBack,bool jumpForward,bool jumpBack);
	inline D2D1_RECT_F GetMesh() { return mesh; };
	D2D1_RECT_F GetBoundBox();
	float GetBoundMidPoint();
	void UpdateBoundBox(float x);
	int GetScore() { return score; }
	void UpdateScore(int score);
	~Player();
};

