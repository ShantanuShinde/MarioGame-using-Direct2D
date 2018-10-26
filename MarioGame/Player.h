#pragma once
#include"SpriteSheet.h"
#include "Graphics.h"
class Player
{
	template <class T> void SafeRelease(T **ppT)
	{
		if (*ppT)
		{
			(*ppT)->Release();
			*ppT = NULL;
		}
	}
	bool Dead;
	static int lives;
	static int score;
	SpriteSheet* sprite;
	Graphics* gfx;
	D2D1_RECT_F displayMesh,collisionMesh,boundBox;
	float scrollX = 0;
public:
	Player(Graphics* graphics,float x, float y);
	void Display(int index, float x, float y,bool walkingForward,bool walkingBack,bool jumpForward,bool jumpBack);
	inline D2D1_RECT_F GetCollisionMesh() { return collisionMesh; };
	D2D1_RECT_F GetBoundBox();
	float GetBoundMidPoint();
	void UpdateBoundBox(float x);
	static int GetScore() { return score; }
	static void Reset();
	void UpdateScore(int score);
	void Die(float &ySpeed);
	bool isDead() { return Dead; }
	~Player();
};

