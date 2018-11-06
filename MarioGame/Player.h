#pragma once
#include"SpriteSheet.h"
#include "Graphics.h"
#include "Ground.h"
#include "ScoreBlock.h"


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
	static bool Dead;
	static int lives;
	static int score;
	int walking, jumping,frame,index;
	bool onGround;
	SpriteSheet* sprite;
	Graphics* gfx;
	D2D1_RECT_F displayMesh,collisionMesh,boundBox;
	float scrollX, ySpeed;
public:
	Player(Graphics* graphics,float x, float y);
	void Display(); //Display the player
	inline D2D1_RECT_F GetCollisionMesh() { return collisionMesh; }; //Returns RECTF object for collision detection
	D2D1_RECT_F GetBoundBox(); //returns player's bounding box
	float GetBoundMidPoint();	//returns midpoint of the bounding box
	void UpdateBoundBox(float x); //change boundbox as player moves
	static int GetScore() { return score; } //Returns current player score
	static void Reset();	//reset score ad lives
	void UpdateScore(int score);	//update score
	void Die();//float &ySpeed);
	bool isDead() { return Dead; }
	void Move(float gravity,double timeDelta); //Move player
	void CheckGroundAndWallCollision(Ground *g);  //check collisions
	void CheckScoreBlockCollision(ScoreBlock *sb);
	void ChangeY(float ySpeed) { this->ySpeed = ySpeed; }
	static void DecreaseLife() { lives--; }
	~Player();
};

