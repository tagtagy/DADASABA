﻿#pragma once
#include "Class_Item.h"
enum {
	maxItemNum = 100,//アイテムの最大数
};
class Class_CreateItem
{
public:
	Class_CreateItem();

	~Class_CreateItem();

	void UpDate(Vec2 _playerPos, Circle _playerHit_Item, Vec2 _MainCamera);

	void Draw() const;

	void SpawnItem(Vec2 _enemyPos);

	int getAddCount() { return addCount; }

private:
	//アイテム
	Class_Item* item[maxItemNum] = { nullptr };

	int addCount = 0;
};

