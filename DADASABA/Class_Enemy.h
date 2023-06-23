#pragma once
#include "Class_player.h"

class Class_Enemy
{
public:
	Class_Enemy();
	void Target_input(Vec2 TargetPos);
	void Move();
	void Attack();
	//ノックバック
	void Knockback();
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
};

