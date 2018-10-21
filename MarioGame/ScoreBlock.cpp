#include "ScoreBlock.h"



ScoreBlock::ScoreBlock(Graphics* gfx):Ground(gfx)
{
	collected = false;
	frame = 0;
}


void ScoreBlock::CollectPoint(Player **p)
{
	if (!collected)
	{
		MoveUp();
		sprite = new SpriteSheet(L"collectedscoreblock.png",gfx,32,32);
		(*p)->UpdateScore(300);
		collected = true;
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
