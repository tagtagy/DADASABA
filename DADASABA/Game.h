# pragma once
# include "Common.h"
#include "Class_player.h"
#include "Class_Enemy.h"
// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	~Game();

	void update() override;

	void draw() const override;

private:
	//プレイヤー
	Class_player* player = nullptr;
	//敵
	Class_Enemy* enemy = nullptr;

	double CountDown = 60;
	double downPrint;
	
};
