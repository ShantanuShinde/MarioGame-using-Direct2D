#pragma once
#include "HPTimer.h"
#include "GameLevel.h"
#include "Player.h"
#include "Level1.h"

class GameController
{
	GameController() {}
	static GameLevel* currentLevel;
	static bool loading;
	static HPTimer* hpTimer;
public:
	static void Init();

	static void LoadInitialLevel(GameLevel* lvl);
	static void SwitchLevel(GameLevel* lvl);

	static void Update();
	static void Render();

	static void ReloadonPlayerDead();
};


