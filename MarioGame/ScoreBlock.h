#pragma once
#include "Ground.h"
class Player;

class ScoreBlock :
	public Ground
{
	bool collected;
	int frame;
	SpriteSheet *coin;
	D2D1_RECT_F coinRect;
	int coinFrame;
public:
	ScoreBlock(Graphics* gfx);
	void CollectPoint(Player *p);	//update player score and update scoreblock
	void Display() override;	//Display scoreblock
	~ScoreBlock();
};

