#pragma once
#include "Class_Enemy.h"
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
	                Vec2 _MainCamera,double deltatime);
	//描画
	void Draw()const;

	void SetAngleTimer(int angleTimer) { angleTime = angleTimer; }
	bool GetBossLive() { return isBossLive; }
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
	//敵
	Class_Enemy* enemy[enemyMax];
};

