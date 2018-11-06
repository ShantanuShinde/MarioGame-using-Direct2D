#pragma once
#include "GameLevel.h"
#include "Player.h"
#include "Enemy.h"
#include "Ground.h"
#include "ScoreBlock.h"
class Level1:public GameLevel
{
	float xPlayer,yPlayer,ySpeed,ySpeedPlayer,gravity;
	Player* p;
	Enemy* e[20];
	Ground *g[150];
	Ground *g1[200];
	ScoreBlock *sb[20];
	SpriteSheet* sprite;
	D2D1_RECT_F plmsh;
public:
	void Load() override;
	void Unload() override;
	void Update(double timeTotal, double timeDelta) override;
	void Render() override;
};

