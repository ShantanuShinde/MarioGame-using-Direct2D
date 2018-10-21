#include "Player.h"

int Player::lives;
int Player::score;
Player::Player(Graphics* graphics,float x, float y)
{
	gfx = graphics;
	sprite = new SpriteSheet(L"stand.png", gfx,32, 32);
	mesh = D2D1::RectF(x - 15, y - 15, x, y);
	lives = 3;
	boundBox = D2D1::RectF(0, 0, 282, 157);
	score = 0;
}

void Player::Display(int index, float x, float y, bool walkingForward, bool walkingBack,bool jumpForward,bool jumpBack)
{
	if (jumpForward)
	{
		sprite = new SpriteSheet(L"jump.png", gfx, 32, 32);
		mesh = D2D1::RectF(x - 15, y - 15, x, y);
		sprite->Draw(0, mesh);
	}
	else if (jumpBack)
	{
		sprite = new SpriteSheet(L"jump.png", gfx, 32, 32);
		mesh = D2D1::RectF(x - 15, y - 15, x, y);
		sprite->Draw(1, mesh);
	}
	else if (walkingForward)
	{
		sprite = new SpriteSheet(L"walk.png", gfx, 32, 32);
		mesh = D2D1::RectF(x - 15, y - 15, x, y);
		sprite->Draw(index, mesh);
	}
	else if (walkingBack)
	{
		sprite = new SpriteSheet(L"walk.png", gfx, 32, 32);
		mesh = D2D1::RectF(x - 15, y - 15, x, y);
		sprite->Draw(index+3, mesh);
	}
	else
	{
		sprite = new SpriteSheet(L"stand.png", gfx, 32, 32);
		mesh = D2D1::RectF(x - 15, y - 15, x, y);
		sprite->Draw(index, mesh);

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
