# pragma once
# include "Common.h"
#include "Class_player.h"
#include "Class_Enemy.h"
#include "Class_EnemyCanon.h"
#include "Class_Item.h"

enum {
	freeCanon,
	Player,
	Boss,
	maxItemNum = 100,//アイテムの最大数

};

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

	//背景
	const Texture Back_ground{ U"SOZAI/background/haikei_rokugoukann_11.png" };
	//背景貼り付け用ブロック
	RectF Back_groundRect[9];
	//背景のマップ上の位置
	Vec2 BackMapPos[9];
	//背景のスクリーン上の位置
	Vec2 ScreenPos[9];

	//プレイヤー
	Class_player* player = nullptr;
	//敵のキャノン
	Class_EnemyCanon* enemyCanon = nullptr;
	//アイテム
	Class_Item* item[maxItemNum] = { nullptr };

	//カメラ位置
	Vec2 MainCamera{ 0,0 };
	//カメラの追従するモード
	int CameraTarget = freeCanon;

	//デルタタイム
	double deltatime=0;
	//円形のカウントダウン
	double angle = 360_deg;
	double countDCircleX = 100;
	double countDCircleY = 100;
	double countDCircleSize = 100;
	double countDCircleFrame = 3;
	double countDown = 0.105;

};
