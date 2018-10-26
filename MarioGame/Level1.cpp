#include "Level1.h"
#include "SpriteSheet.h"
#include<sstream>

void Level1::Load()
{
	//initialize values
	xPlayer = 100;
	yPlayer =   50,dx=0;
	p = new Player(gfx,xPlayer,yPlayer);
	dx = dy = 0;
	index = 0;
	frame = 0;
	ySpeed = 0;
	ySpeedPlayer = 0;
	gravity = 10;
	walkingBack =walkingForward= false,onGround=false,jumpFoward=jumpBack=false;
	scrollX = 0;
	sb = new ScoreBlock(gfx);
	sb->Init(70, 50, 15, 15,L"scoreblock.png",32,32);
	for (int i = 0; i < 3; i++)
		g[i] = new Ground(gfx);
	g[0]->Init(0, 100, 60, 1000,L"Ground.png",236,68);
	g[1]->Init(40, 50, 15, 15, L"Ground.png", 236, 68); g[2]->Init(415, 65, 35, 15, L"Ground.png", 236, 68);
	//sprite = new SpriteSheet(L"Image.png", gfx);
	e = new Enemy(gfx);
	e->Init(30, 50);
}

void Level1::Unload()
{
	delete p;
}

void Level1::Update(double timeTotal, double timeDelta)
{
	onGround = false;
	float nextYPlayer = yPlayer;
	nextYPlayer += ySpeedPlayer;//update possible y position of player with speed
	ySpeed += gravity * timeDelta;//update player speed with gravity*tome delta
	ySpeedPlayer += gravity * timeDelta;
	if (!e->isDead())
		e->Move(timeDelta,ySpeed);
	D2D1_RECT_F pBound = p->GetBoundBox();//get the bounding box
	if(!p->isDead())
	for (int i = 0; i < 3; i++)
	{
		//for each enviroment object, check if it falls inside the players bounding box. If yes, check if player is colliding with it
		D2D1_RECT_F gmsh = g[i]->GetMesh();
		D2D1_RECT_F plmsh = D2D1::RectF(xPlayer+dx - 11, nextYPlayer - 15, xPlayer+dx, nextYPlayer);
		
		if ((gmsh.left <= pBound.left && gmsh.right >= pBound.right)||(gmsh.right<=pBound.right&&gmsh.right>=pBound.left))
		{

			if (g[i]->DetectCollision(plmsh))
			{
				
				if ((plmsh.bottom >= gmsh.top) && (plmsh.top < gmsh.top) && (plmsh.bottom < gmsh.bottom) && (plmsh.right > gmsh.left) && (plmsh.left < gmsh.right))//handle collision from top
				{
					nextYPlayer = gmsh.top;
					ySpeedPlayer = 0;
					onGround = true;
					

				}
				else if ((plmsh.top <= gmsh.bottom) && (plmsh.bottom > gmsh.top) && (plmsh.bottom > gmsh.bottom) && (plmsh.right > gmsh.left) && (plmsh.left < gmsh.right))//handle collision from bottom
				{
					nextYPlayer = gmsh.bottom + 15;
					ySpeedPlayer = 0.5;
					g[i]->MoveUp();
				}
				else if (plmsh.right >= gmsh.left&&plmsh.left < gmsh.left)//handle collision from left
					xPlayer = gmsh.left;
				else if (plmsh.left <= gmsh.right)//handle collision from right
					xPlayer = gmsh.right + 11;

			}
		}
		
	}
	for (int i = 0; i < 3; i++)
	{
		D2D1_RECT_F gmsh = g[i]->GetMesh();
		D2D1_RECT_F emsh = e->GetRect();
		if (!e->isDead())
			if (g[i]->DetectCollision(emsh))
				e->UpdateMove(timeDelta, gmsh, &ySpeed);
	}
	yPlayer = nextYPlayer; //update player's vertical position with its possible vertical position
	xPlayer += dx;
	D2D1_RECT_F plmsh = D2D1::RectF(xPlayer - 11, nextYPlayer - 15, xPlayer, nextYPlayer);
	D2D1_RECT_F	sbmsh = sb->GetMesh();
	if ((sbmsh.left <= pBound.left && sbmsh.right >= pBound.right) || (sbmsh.right <= pBound.right&&sbmsh.right >= pBound.left))
	{

		if (sb->DetectCollision(plmsh))
		{
			if ((plmsh.bottom <= sbmsh.top) && (plmsh.top < sbmsh.top) && (plmsh.bottom < sbmsh.bottom) && (plmsh.right > sbmsh.left) && (plmsh.left < sbmsh.right))//handle collision from top
			{
				nextYPlayer = sbmsh.top;
				ySpeedPlayer = 0;
					
				onGround = true;
			
			}
			else if ((plmsh.top <= sbmsh.bottom) && (plmsh.bottom > sbmsh.top) && (plmsh.bottom > sbmsh.bottom) && (plmsh.right > sbmsh.left) && (plmsh.left < sbmsh.right))//handle collision from bottom
			{
				nextYPlayer = sbmsh.bottom + 15;
				ySpeedPlayer = 0.5;
				sb->CollectPoint(&p);
			}
			else if (plmsh.right >= sbmsh.left&&plmsh.left < sbmsh.left)//handle collision from left
			{
				xPlayer = sbmsh.left;
				
			}
			else if (plmsh.left <= sbmsh.right)//handle collision from right
			{
				xPlayer = sbmsh.right + 11;
			}

		}
	}
	if (!e->isDead()&&!p->isDead())
		e->PlayerCollision(&p,ySpeedPlayer);

	if (xPlayer >= (p->GetBoundMidPoint() - 10))//check if player is near centre of the screen, if yes move the screen to right
	{
		scrollX -= 1;
		p->UpdateBoundBox(1);
		gfx->Scroll(scrollX);
	}

	
	
	if (!p->isDead())
	{
		//handle player controls
		if (GetAsyncKeyState('D'))
		{
			if (!walkingForward)
				frame = 0;
			walkingForward = true;
			frame++;
			index = (frame / 5) % 3;
			dx = 79.0f*timeDelta;
		}
		else if (walkingForward)
		{
			walkingForward = false;
			index = 0;
			dx = 0;
		}

		if (GetAsyncKeyState('A'))
		{
			if (!walkingBack)
				frame = 0;
			walkingBack = true;
			frame++;
			index = (frame / 5) % 3;
			int temp = xPlayer;
			dx = -79.0f*timeDelta;
			std::ostringstream os;
			os << temp - xPlayer << "\n";
			OutputDebugString(os.str().c_str());
		}
		else if (walkingBack)
		{
			walkingBack = false;
			index = 1;
			dx = 0;
		}
		if (GetAsyncKeyState('W') && onGround)
		{
			ySpeedPlayer = -3.5f;
			if (walkingBack)
				jumpBack = true;
			else if (walkingForward)
				jumpFoward = true;
		}
		else if (onGround)
			jumpBack = jumpFoward = false;
	}
	
}

void Level1::Render()
{
	gfx->ClearScreen(135.0/255, 206.0/255, 250.0/255);
	for (int i = 0; i < 3; i++)
		g[i]->Display();
	if (!e->isDead())
		e->Display();
	
	p->Display(index, xPlayer+2, yPlayer,walkingForward,walkingBack,jumpFoward,jumpBack);
	sb->Display();
}