#pragma once
#ifndef _P_ENEMY_H_
#define _P_ENEMY_H_
# include "Common.h"
#include "Class_Bullet.h"
# include <cmath>

enum {
	normalEnemy1,
	normalEnemy2,
	normalEnemy3,
	normalEnemy4,
	EnemytypeMax,
	bulletMax = 4//最大の弾丸量
};
class P_Enemy
{
public:

	//セット
	virtual void set(Vec2 pos, int EnemyType)=0;
	//ターゲットの設定
	virtual void Target_input(Vec2 TargetPos, Circle TargetHit) = 0;
	//動き
	virtual void Move(Vec2 _MainCamera, double deltatime) = 0;
	//攻撃
	virtual void Attack() = 0;
	//ノックバック
	virtual void Knockback(bool _IsAttack, Circle* _AttackHitPos) = 0;
	//描画
	virtual void Draw()const = 0;

	//有効かどうかの提示
	virtual bool Getvalid() = 0;
	virtual void Setvalid(bool valid) = 0;
	virtual int EnemyHp() = 0;

	virtual bool getIsDead() = 0;

	virtual Vec2 getEnemyPos() = 0;

	//正規化の計算
	//底辺,高さ,中心座標,回転の半径
	virtual Vec2 normalization_calculate(double base, double tall, Vec2 centerPos, double range);
private:
	//敵テクスチャ
	const Texture EnemyTexture;
	//敵のサイズ
	int EnemySize = 100;
	//スクリーン上の座標
	Vec2 ScreenPos;
	//マップ上の座標
	Vec2 MapPos;
	//ターゲットの座標
	Vec2 targetPos;
	//ターゲットの当たり判定
	Circle targetHit;
	//スピード
	double speed;
	//動けるか
	bool ismove = true;
	//当たり判定
	Circle Ene_Hit;
	//攻撃が当たったか
	bool IsAttackHit = false;
	//無敵時間
	double InvincibleCount = 0;
	const double InvincibleTime = 1;
	//デルタタイム
	double delta_time = 0;
	//有効か？
	bool isValid = false;
	//ステータス/////////////////////////////////////////
	//HP
	int MaxHP = 10;
	int HP = 0;
	//弾丸/////////////////////////////////////////////
	Class_Bullet* bullet[bulletMax];
	//弾の種類
	int bullet_type = normalBullet1;
	//発射するタイミング
	const double shootTime = 2;
	double shootCount = 0;
	//範囲制限
	Rect AttackRange;

	//倒されたらtrue
	bool isDead = false;
};


#endif
