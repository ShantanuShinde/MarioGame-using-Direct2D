#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::loading;
HPTimer* GameController::hpTimer;

void GameController::Init()
{
	loading = true;
	currentLevel = 0;
	hpTimer = new HPTimer();
}

void GameController::LoadInitialLevel(GameLevel* lvl)
{
	loading = true;
	currentLevel = lvl;
	currentLevel->Load();
	loading = false;
}

void GameController::SwitchLevel(GameLevel* lvl)
{
	loading = true;
	currentLevel->Unload();
	lvl->Load();
	//delete currentLevel;
	currentLevel = lvl;
	loading = false;
}

void GameController::Update()
{
	if (loading)
		return;
	hpTimer->Update();
	currentLevel->Update(hpTimer->GetTimeTotal(), hpTimer->GetTimeDelta());
}

void GameController::Render()
{
	if (loading)
		return;
	currentLevel->Render();
}

void GameController::ReloadonPlayerDead()
{
	
	Player::DecreaseLife();
	SwitchLevel(new Level1);
}