#pragma once
#include "Class_Enemy.h"
enum {

	enemyMax = 10

};
class Class_EnemyCanon
{
public:
	~Class_EnemyCanon();
	Class_EnemyCanon();
	//出現
	void appearance(Vec2 _TargetPos, Circle _TargetHit,
					bool _IsAttack, Rect* _AttackHitPos);

	void Draw()const;
private:
	//ランダム出現
	void random_appearance();
	//籠目出現
	void ghost_appearance();
	//円出現
	void circle_appearance();
private:

	Vec2 TargetPos;

	//出現タイミングのカウント
	const double appearanceTime = 1;
	double appearanceCount = 0;

	Class_Enemy* enemy[enemyMax];
};

