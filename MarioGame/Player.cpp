#include "Player.h"
#include <sstream>
#include<windows.h>

int Player::lives;
int Player::score;
Player::Player(Graphics* graphics,float x, float y)
{
	gfx = graphics;
	sprite = new SpriteSheet(L"stand.png", gfx,32, 32);
	displayMesh = D2D1::RectF(x - 15, y - 15, x, y);
	collisionMesh = D2D1::RectF(x - 13, y - 15, x - 2,y );
	boundBox = D2D1::RectF(0, 0, 282, 157);
	Dead = false;
}
void Player::Die(float &ySpeed)
{
	Dead = true;
	lives--;
	sprite = new SpriteSheet(L"dead.png", gfx, 32, 32);
	
	ySpeed = -4.5f;
}
void Player::Reset()
{
	score = 0;
	lives = 3;
}

void Player::Display(int index, float x, float y, bool walkingForward, bool walkingBack,bool jumpForward,bool jumpBack)
{
	displayMesh = D2D1::RectF(x - 15, y - 15, x, y);
	
	collisionMesh = D2D1::RectF(x - 13, y - 15, x - 2, y - 2);
	if (Dead)
		sprite->Draw(0, displayMesh);
	else if (jumpForward)
	{
		sprite = new SpriteSheet(L"jump.png", gfx, 32, 32);
		
		sprite->Draw(0, displayMesh);
	}
	else if (jumpBack)
	{
		sprite = new SpriteSheet(L"jump.png", gfx, 32, 32);
		sprite->Draw(1, displayMesh);
	}
	else if (walkingForward)
	{
		sprite = new SpriteSheet(L"walk.png", gfx, 32, 32);
		sprite->Draw(index, displayMesh);
	}
	else if (walkingBack)
	{
		sprite = new SpriteSheet(L"walk.png", gfx, 32, 32);
		sprite->Draw(index+3, displayMesh);
	}
	else
	{
		sprite = new SpriteSheet(L"stand.png", gfx, 32, 32);
		sprite->Draw(index, displayMesh);

	}
}
D2D1_RECT_F Player::GetBoundBox() { return boundBox;}

void Player::UpdateScore(int newScore)
{
	score += newScore;
}
float Player::GetBoundMidPoint()
{
	return((boundBox.right - boundBox.left) / 2)+boundBox.left;
}

void Player::UpdateBoundBox(float x)
{
	boundBox.left += x;
	boundBox.right += x;
}
Player::~Player()
{
	delete sprite;
	delete gfx;
}
