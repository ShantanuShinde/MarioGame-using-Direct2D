#include "Level1.h"
#include "GameController.h"
#include "SpriteSheet.h"
#include<sstream>

void Level1::Load()
{
	
	//initialize values
	p = new Player(gfx,60,125);
	ySpeed = 0;
	gravity = 10;

	for (int i = 0; i < 20; i++)
	{
		sb[i] = new ScoreBlock(gfx);
		e[i] = new Enemy(gfx);
	}
	for (int i = 0; i < 50; i++)
	{
		g[i] = new Ground(gfx);
		g[i]->Init(i*15, 125, 15, 15, L"Ground.png", 32, 32);
	}
	for (int i = 50; i < 80; i++)
	{
		g[i] = new Ground(gfx);
		g[i]->Init(45 + i * 15, 125, 15, 15, L"Ground.png", 32, 32);
	}
	for (int i = 80; i < 150; i++)
	{
		g[i] = new Ground(gfx);
		g[i]->Init(90+ i * 15, 125, 15, 15, L"Ground.png", 32, 32);
	}
	for (int i = 0; i < 200; i++)
		g1[i] = new Ground(gfx);
	//first row 
	g1[0]->Init(100, 75, 15, 15, L"Bricks.png", 32, 32); g1[1]->Init(115, 75, 15, 15, L"Bricks.png", 32, 32); sb[0]->Init(130, 75, 15, 15, L"scoreblock.png", 32, 32); g1[2]->Init(145, 75, 15, 15, L"Bricks.png", 32, 32);
	//first enemy
	e[0]->Init(200, 125);
	//second row of bricks
	g1[3]->Init(250, 75, 15, 15, L"Bricks.png", 32, 32), sb[1]->Init(265, 75, 15, 15, L"scoreblock.png", 32, 32), g1[4]->Init(280, 75, 15, 15, L"Bricks.png", 32, 32); g1[5]->Init(295, 75, 15, 15, L"Bricks.png", 32, 32);
	//row above second
	g1[6]->Init(280, 40, 15, 15, L"Bricks.png", 32, 32); g1[7]->Init(295, 40, 15, 15, L"Bricks.png", 32, 32); g1[8]->Init(310, 40, 15, 15, L"Bricks.png", 32, 32); g1[9]->Init(325, 40, 15, 15, L"Bricks.png", 32, 32);
	
	e[0]->Init(200, 125), e[1]->Init(290, 40), e[2]->Init(300, 40);

}

void Level1::Unload()
{
	/*delete p;
	delete g;
	delete sb;
	//delete e;*/
}

void Level1::Update(double timeTotal, double timeDelta)
{

	std::ostringstream os;

	ySpeed += gravity * timeDelta;//update player speed with gravity*tome delta
/*	if (!e->isDead())
		e->Move(timeDelta, ySpeed);*/

	p->Move(gravity, timeDelta);
	D2D1_RECT_F bbox = p->GetBoundBox();
	for (int i = 0; i < 3; i++)
	{
		D2D1_RECT_F emsh = e[i]->GetRect();
		e[i]->PlayerCollision(&p, ySpeed);
		if (bbox.right > emsh.left&&bbox.left < emsh.right)
			e[i]->Move(timeDelta, ySpeed);
	}
	if(!p->isDead())
	for (int i = 0; i < 150; i++)
	{
		p->CheckGroundAndWallCollision(g[i]);
		for (int j = 0; j < 3; j++)
		{
			if (g[i]->DetectCollision(e[j]->GetMesh()))
				e[j]->UpdateMove(timeDelta, g[i]->GetMesh(), &ySpeed);
		}
	}
	
	
	
	/*if (p->GetBoundBox().bottom <= p->GetCollisionMesh().top)
	{
		OutputDebugString("Load level\n");
		GameController::ReloadonPlayerDead();
	}*/
	/*for (int i = 0; i < 150; i++)
	{
		D2D1_RECT_F gmsh = g[i]->GetMesh();
		D2D1_RECT_F emsh = e->GetRect();
		if (!e->isDead())
			if (g[i]->DetectCollision(emsh))
				e->UpdateMove(timeDelta, gmsh, &ySpeed);
	}*/
	for(int i=0;i<2;i++)
		p->CheckScoreBlockCollision(sb[i]);
	for (int i = 0; i < 10; i++)
	{
		p->CheckGroundAndWallCollision(g1[i]);
		for (int j = 0; j < 3; j++)
		{
			if (g1[i]->DetectCollision(e[j]->GetMesh()))
			
				e[j]->UpdateMove(timeDelta, g1[i]->GetMesh(), &ySpeed);
		}
	}
	/*if (!e->isDead()&&!p->isDead())
		e->PlayerCollision(&p,ySpeedPlayer);*/
	
}

void Level1::Render()
{
	gfx->ClearScreen(135.0/255, 206.0/255, 250.0/255);
	for (int i = 0; i < 150; i++)
		g[i]->Display();
	for (int i = 0; i < 3; i++)
		e[i]->Display();
	p->Display();
	for (int i = 0; i < 2; i++)
		sb[i]->Display();
	for (int i = 0; i < 10; i++)
		g1[i]->Display();
}