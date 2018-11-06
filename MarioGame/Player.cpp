#include "Player.h"
#include <sstream>
#include<windows.h>

int Player::lives;
int Player::score;
bool Player::Dead;
Player::Player(Graphics* graphics,float x, float y)
{
	gfx = graphics;
	sprite = new SpriteSheet(L"stand.png", gfx,32, 32);
	displayMesh = D2D1::RectF(x - 15, y - 15, x, y);
	collisionMesh = D2D1::RectF(x - 13, y - 15, x - 2,y );
	boundBox = D2D1::RectF(0, 0, 282, 157);
	Dead = false, onGround = false;
	ySpeed = 0, scrollX = 0;
	int walking = 0, jumping = 0,frame=0,index=0;
}
void Player::Die()
{
	Dead = true;
	sprite = new SpriteSheet(L"dead.png", gfx, 32, 32);
	
	ySpeed = -4.5f;
}
void Player::Reset()
{
	score = 0;
	lives = 3;
	Dead = false;
}
void Player::Move(float gravity,double timeDelta)
{

	if (displayMesh.right >= (GetBoundMidPoint() - 10))//check if player is near centre of the screen, if yes move the screen to right
	{
		scrollX -= 1;
		UpdateBoundBox(1);
		gfx->Scroll(scrollX);
	}
	//Player movement controls
	if (!Dead)
	{
		if (GetAsyncKeyState('D'))
		{
			if (walking != 1)
				frame = 0;
			walking = 1;
			frame++;
			index = (frame / 5) % 3;
			collisionMesh.right += 75.0f*timeDelta; collisionMesh.left += 75.0f*timeDelta;
			displayMesh.right += 75.0f*timeDelta; displayMesh.left += 75.0f*timeDelta;
		}
		else if (walking == 1)
		{
			walking = 0;
			index = 0;
		}

		if (GetAsyncKeyState('A'))
		{
			if (walking != -1)
				frame = 0;
			walking = -1;
			frame++;
			index = (frame / 5) % 3;
			if (collisionMesh.left >= boundBox.left)
			{
				collisionMesh.right -= 75.0f*timeDelta; collisionMesh.left -= 75.0f*timeDelta;
				displayMesh.right -= 75.0f*timeDelta; displayMesh.left -= 75.0f*timeDelta;
			}

		}
		else if (walking == -1)
		{
			walking = 0;
			index = 1;
		}
		if (GetAsyncKeyState('W') && onGround)
		{
			ySpeed = -4.0f;
			jumping = walking == -1 ? -1 : 1;
		}
		else if (onGround)
			jumping = 0;
	}
	onGround = false;

	ySpeed += gravity*timeDelta;
	//Move the player in y direction(i.e. simulate gravity)
	collisionMesh.top += ySpeed;
	collisionMesh.bottom += ySpeed;
	displayMesh.top += ySpeed;
	displayMesh.bottom += ySpeed;

	

}

void Player::CheckGroundAndWallCollision(Ground *g)
{
	D2D1_RECT_F gmsh = g->GetMesh();
	//for each wall and platform, check if it falls inside the players bounding box. If yes, check if player is colliding with it
	if ((gmsh.left <= boundBox.left && gmsh.right >= boundBox.right) || (gmsh.right <= boundBox.right&&gmsh.right >= boundBox.left))
	{

		if (g->DetectCollision(collisionMesh))
		{
		 if (collisionMesh.right >= gmsh.left&&collisionMesh.left < gmsh.left && ((collisionMesh.bottom - collisionMesh.top) / 2 + collisionMesh.top  > gmsh.top) && ((collisionMesh.bottom - collisionMesh.top) / 2 + collisionMesh.top < gmsh.bottom ))//handle collision from left
		{
			collisionMesh.right = gmsh.left;
			collisionMesh.left = collisionMesh.right - 11;
			displayMesh.left = collisionMesh.left - 2;
			displayMesh.right = collisionMesh.right + 2;
		}
		else if (collisionMesh.left <= gmsh.right&&collisionMesh.right > gmsh.right && ((collisionMesh.bottom - collisionMesh.top) / 2 + collisionMesh.top > gmsh.top) && ((collisionMesh.bottom - collisionMesh.top) / 2 + collisionMesh.top < gmsh.bottom ))//handle collision from right
		{
			collisionMesh.left = gmsh.right;
			collisionMesh.right = collisionMesh.left + 11;
			displayMesh.left = collisionMesh.left - 2;
			displayMesh.right = collisionMesh.right + 2;
		}
			else if ((collisionMesh.bottom >= gmsh.top) && (collisionMesh.top < gmsh.top) && (collisionMesh.bottom < gmsh.bottom) && ((collisionMesh.right - collisionMesh.left) / 2 + collisionMesh.left + 2 > gmsh.left) && ((collisionMesh.right - collisionMesh.left) / 2 + collisionMesh.left < gmsh.right + 2))//handle collision from top
			{
				collisionMesh.bottom = gmsh.top;
				collisionMesh.top = collisionMesh.bottom - 15;
				displayMesh.bottom = collisionMesh.bottom;
				displayMesh.top = collisionMesh.top;
				ySpeed = 0;
				onGround = true;
			}
			else if ((collisionMesh.top <= gmsh.bottom) && (collisionMesh.bottom > gmsh.top) && (collisionMesh.bottom > gmsh.bottom) && ((collisionMesh.right - collisionMesh.left) / 2 + collisionMesh.left + 2 > gmsh.left) && ((collisionMesh.right - collisionMesh.left) / 2 + collisionMesh.left < gmsh.right + 2))//handle collision from bottom
			{
				collisionMesh.top = gmsh.bottom;
				collisionMesh.bottom = collisionMesh.top + 15;
				displayMesh.bottom = collisionMesh.bottom;
				displayMesh.top = collisionMesh.top;
				ySpeed = 0.5;
				g->MoveUp();
			}
			

		}
	}
}

void Player::CheckScoreBlockCollision(ScoreBlock *sb)
{
	//For each scoreblock, check if the block falls in the bounding block of the player. If yes, check its collision
	D2D1_RECT_F	sbmsh = sb->GetMesh();
	if ((sbmsh.left <= boundBox.left && sbmsh.right >= boundBox.right) || (sbmsh.right <= boundBox.right&&sbmsh.right >= boundBox.left))
	{

		if (sb->DetectCollision(collisionMesh))
		{
			if ((collisionMesh.bottom >= sbmsh.top) && (collisionMesh.top < sbmsh.top) && (collisionMesh.bottom < sbmsh.bottom) && ((collisionMesh.right - collisionMesh.left) / 2 + collisionMesh.left + 2 > sbmsh.left) && ((collisionMesh.right - collisionMesh.left) / 2 + collisionMesh.left < sbmsh.right + 2))//handle collision from top
			{
				collisionMesh.bottom = sbmsh.top;
				collisionMesh.top = collisionMesh.bottom - 15;
				displayMesh.bottom = collisionMesh.bottom;
				displayMesh.top = collisionMesh.top;
				ySpeed = 0;

				onGround = true;

			}
			else if ((collisionMesh.top <= sbmsh.bottom) && (collisionMesh.bottom > sbmsh.top) && (collisionMesh.bottom > sbmsh.bottom) && ((collisionMesh.right - collisionMesh.left) / 2 + collisionMesh.left + 2 > sbmsh.left) && ((collisionMesh.right - collisionMesh.left) / 2 + collisionMesh.left < sbmsh.right + 2))//handle collision from bottom
			{
				collisionMesh.top = sbmsh.bottom;
				collisionMesh.bottom = collisionMesh.top + 15;
				displayMesh.bottom - collisionMesh.bottom;
				displayMesh.top = collisionMesh.top;
				ySpeed = 0.5;
				sb->CollectPoint(this);
			}
			else if (collisionMesh.right >= sbmsh.left&&collisionMesh.left < sbmsh.left && ((collisionMesh.bottom - collisionMesh.top) / 2 + collisionMesh.top + 2 > sbmsh.top) && ((collisionMesh.bottom - collisionMesh.top) / 2 + collisionMesh.top < sbmsh.bottom + 2))//handle collision from left
			{
				collisionMesh.right = sbmsh.left;
				collisionMesh.left = collisionMesh.right - 11;
				displayMesh.left = collisionMesh.left - 2;
				displayMesh.right = collisionMesh.right + 2;

			}
			else if (collisionMesh.left <= sbmsh.right&&collisionMesh.right > sbmsh.right && ((collisionMesh.bottom - collisionMesh.top) / 2 + collisionMesh.top + 2 > sbmsh.top) && ((collisionMesh.bottom - collisionMesh.top) / 2 + collisionMesh.top < sbmsh.bottom + 2))//handle collision from right
			{
				collisionMesh.left = sbmsh.right;
				collisionMesh.right = collisionMesh.left + 11;
				displayMesh.left = collisionMesh.left - 2;
				displayMesh.right = collisionMesh.right + 2;
			}

		}
	}
}


void Player::Display()
{
	if (Dead)
		sprite->Draw(0, displayMesh);
	else if (jumping==1)
	{
		sprite = new SpriteSheet(L"jump.png", gfx, 32, 32);

		sprite->Draw(0, displayMesh);
	}
	else if (jumping==-1)
	{
		sprite = new SpriteSheet(L"jump.png", gfx, 32, 32);
		sprite->Draw(1, displayMesh);
	}
	else if (walking==1)
	{
		sprite = new SpriteSheet(L"walk.png", gfx, 32, 32);
		sprite->Draw(index, displayMesh);
	}
	else if (walking==-1)
	{
		sprite = new SpriteSheet(L"walk.png", gfx, 32, 32);
		sprite->Draw(index + 3, displayMesh);
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
