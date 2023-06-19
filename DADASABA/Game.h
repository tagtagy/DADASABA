﻿# pragma once
# include "Common.h"
#include "Class_player.h"
#include "Class_Enemy.h"
#include "Class_Item.h"
// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	~Game();

	void update() override;

	void draw() const override;

	void SpawnItem(Vec2 _enemyPos);

private:
	//プレイヤー
	Class_player* player = nullptr;
	//敵
	Class_Enemy* enemy = nullptr;
	//アイテム
	const static int maxItemNum = 1000;
	Class_Item* item[maxItemNum] = { nullptr };
	int itemSpawnNum = 0;

	double CountDown = 60;
	double downPrint;
	
};
