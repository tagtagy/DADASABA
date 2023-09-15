#pragma once
#include "P_Enemy.h"
#include "C_E_Normal.h"
#include "C_E_Boss.h"
#include "Class_CreateItem.h"
//敵の最大数
enum {
	enemyMax = 10
};
class Class_EnemyCanon
{
public:
	~Class_EnemyCanon();
	Class_EnemyCanon();
	//出現
	//ターゲットの座標、ターゲットの当たり判定
	//プレイヤーが斬撃の攻撃しているか、攻撃の当たり判定
	//カメラの座標、デルタタイム
	void appearance(Vec2 _TargetPos, Circle _TargetHit,
					bool _IsAttack, Circle* _AttackHitPos,
	                Vec2 _MainCamera,double deltatime, Circle _TargetHit_Item);
	//描画
	void Draw()const;

	void SetAngleTimer(int angleTimer) { angleTime = angleTimer; }
	bool GetBossLive() { return isBossLive; }

	int addCountGet() { return createItem.getAddCount(); }

	//敵
	P_Enemy* enemy[enemyMax + 1] = { nullptr };
private:
	//ボス出現
	void Boss_appearance();
	//ランダム出現
	void random_appearance();
	//籠目出現
	void ghost_appearance();
	//円出現
	void circle_appearance();
private:
	//ターゲットの座標
	Vec2 TargetPos;
	//タイマーの割合
	int angleTime = 360;
	//ボス戦かどうか
	bool isBossFight = false;
	//ボスが生きているか
	bool isBossLive = true;
	//デルタタイム
	double delta_time=0;
	//出現タイミングのカウント
	const double appearanceTime = 1;
	double appearanceCount = 0;
	

	Class_CreateItem createItem;
};

