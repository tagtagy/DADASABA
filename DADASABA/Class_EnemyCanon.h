#pragma once
# include "Common.h"
#include "Class_Enemy.h"
class Class_EnemyCanon
{
public:
	//出現
	void appearance();
private:
	//ランダム出現
	void random_appearance();
	//籠目出現
	void ghost_appearance();
	//円出現
	void circle_appearance();
private:

	const double appearanceTime = 1;
	double appearanceCount = 0;

	Class_Enemy Class_Enemy[10];
};

