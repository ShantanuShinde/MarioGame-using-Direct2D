#include "ScoreBlock.h"
#include "Player.h"




ScoreBlock::ScoreBlock(Graphics* gfx):Ground(gfx)
{
	collected = false;
	frame = 0;
}


void ScoreBlock::CollectPoint(Player *p)
{
	if (!collected)
	{
		MoveUp();
		sprite = new SpriteSheet(L"collectedscoreblock.png",gfx,32,32);
		p->UpdateScore(300);
		collected = true;
		coin = new SpriteSheet(L"coin.png", gfx, 16, 32);
		coinFrame = 0;
	}
}

void ScoreBlock::Display()
{
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
	if (collected)
	{
		if (coinFrame < 12)
		{
			coinFrame++;
	
			coinRect = D2D1::RectF(mesh.left+3, mesh.top - coinFrame , mesh.right-3, mesh.top +10 - coinFrame);
			coin->Draw((coinFrame/3)%4, coinRect);
		}
		else if (coinFrame < 20)
		{
			coinFrame++;
			coin->Draw((coinFrame / 3) % 4, coinRect);
		}
		sprite->Draw(0, mesh);
	}
	else
	{
		frame++;
		sprite->Draw((frame/10)%3, mesh);
		
	}
}

ScoreBlock::~ScoreBlock()
{
}
