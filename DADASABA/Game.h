# pragma once
# include "Common.h"
#include "Class_player.h"
#include "Class_Enemy.h"
#include "Class_EnemyCanon.h"
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
	// 接続されているモニタの情報一覧を取得
	const Array<MonitorInfo> monitors = System::EnumerateMonitors();

	//プレイヤー
	Class_player* player = nullptr;
	//敵のキャノン
	Class_EnemyCanon* enemyCanon = nullptr;
	//アイテム
	//スポーンできる最大数
	const static int maxItemNum = 1000;
	Class_Item* item[maxItemNum] = { nullptr };
	//現在スポーンしているアイテムの数
	int itemSpawnNum = 0;

	double CountDown = 60;
	double downPrint;
	
};
