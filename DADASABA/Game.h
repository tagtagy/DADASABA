# pragma once
#include <cmath>
# include "Common.h"
#include "Class_player.h"
#include "Class_EnemyCanon.h"
#include "Class_Timer.h"

enum {
	freeCanon,
	fullScreen,
	Player,
	Boss,

};

// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	~Game();

	void update() override;

	void draw() const override;

private:
	// 接続されているモニタの情報一覧を取得
	const Array<MonitorInfo> monitors = System::EnumerateMonitors();

	//背景
	const Texture Back_ground{ U"SOZAI/background/haikei_rokugoukann_12.png" };
	//背景枠
	const Texture Back_ground_frame{ U"SOZAI/background/waku.png" };
	RectF Back_ground_frame_sticker;
	//背景のマップ上の位置
	Vec2 BackMapPos{0,0};
	//背景のスクリーン上の位置
	Vec2 ScreenPos;

	//プレイヤー
	Class_player* player = nullptr;
	//敵のキャノン
	Class_EnemyCanon* enemyCanon = nullptr;

	//カメラ位置
	Vec2 MainCamera{ 0,0 };
	//カメラの追従するモード
	int CameraTarget = Player;

	//デルタタイム
	double deltatime=0;

	Class_Timer timer;

};
