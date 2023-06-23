#pragma once
# include "Common.h"
# include <cmath>
struct EnemyBullet {
private:
	//座標
	Vec2 position;
	//弾丸のスピード
	const double spped = 10;
	//当たり判定
	Circle BulletHit;
	//有効か？
	bool IsValid;

};

class Class_Enemy
{
public:
	Class_Enemy();
	void Target_input(Vec2 TargetPos);
	//動き
	void Move();
	//攻撃
	void Attack();
	//ノックバック
	void Knockback(bool _IsAttack, Rect *_AttackHitPos);
	void Draw()const;

private:
	//正規化の計算
	//底辺,高さ,中心座標,回転の半径
	Vec2 normalization_calculate(double base, double tall, Vec2 centerPos, double range);
private:
	//スクリーン上の座標
	Vec2 ScreenPos;
	//マップ上の座標
	Vec2 MapPos;
	//ターゲットの座標
	Vec2 target;
	//スピード
	double speed;
	//当たり判定
	Circle Ene_Hit;
	//攻撃が当たったか
	bool IsAttackHit = false;

	const int MaxBullets = 100;
	//弾丸
	Array<EnemyBullet> bullets();
};

