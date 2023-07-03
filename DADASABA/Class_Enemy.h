#pragma once
# include "Common.h"
#include "Class_Bullet.h"
# include <cmath>
enum {

	bulletMax=4

};
class Class_Enemy
{
public:
	~Class_Enemy();
	Class_Enemy();
	//セット
	void set(Vec2 pos);
	//ターゲットの設定
	void Target_input(Vec2 TargetPos, Circle TargetHit);
	//動き
	void Move();
	//攻撃
	void Attack();
	//ノックバック
	void Knockback(bool _IsAttack, Rect *_AttackHitPos);

	void Draw()const;

	//有効かどうかの提示
	bool valid() { return isValid; };
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
	Vec2 targetPos;
	//ターゲットの当たり判定
	Circle targetHit;
	//スピード
	double speed;
	//当たり判定
	Circle Ene_Hit;
	//攻撃が当たったか
	bool IsAttackHit = false;

	//有効か？
	bool isValid = false;
	//弾丸/////////////////////////////////////////////
	Class_Bullet* bullet[bulletMax];
	//発射するタイミング
	const double shootTime = 2;
	double shootCount = 0;
};

