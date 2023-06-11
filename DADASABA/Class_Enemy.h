#pragma once
#include "Class_player.h"

class Class_Enemy
{
public:
	Class_Enemy();
	void Target_input(Vec2 TargetPos);
	void Move();
	void Attack();
	void Draw()const;
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

