#pragma once
#include "GameLevel.h"
#include "Player.h"
#include "Enemy.h"
#include "Ground.h"
#include "ScoreBlock.h"
class Level1:public GameLevel
{
	int frame, index;
	float xPlayer,yPlayer,ySpeed,ySpeedPlayer,gravity,nextYPlayer;
	Player* p;
	Enemy* e;
	Ground *g[3];
	ScoreBlock *sb;
	SpriteSheet* sprite;
	bool walkingBack,walkingForward, onGround,jumpFoward,jumpBack;
	float scrollX;

public:
	void Load() override;
	void Unload() override;
	void Update(double timeTotal, double timeDelta) override;
	void Render() override;
};

