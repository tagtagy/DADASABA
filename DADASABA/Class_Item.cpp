#include "stdafx.h"
#include "Class_Item.h"

Class_Item::Class_Item() {
	itemPos = { 0,0 };
	itemHit = { 0,0,0 };
	itemSize = 15;
}

void Class_Item::init(Vec2 _itemPos, Vec2 _playerPos) {
	itemPos = _itemPos + _playerPos;
}

void Class_Item::draw() {
	itemHit(itemRedTexture).draw();
}

void Class_Item::MapPos(Vec2 _playerPos) {
	itemHit = { itemPos.x - _playerPos.x, itemPos.y - _playerPos.y,itemSize };
}

void Class_Item::hitPlayerHit(Circle _playerHit) {
	if (itemHit.intersects(_playerHit)) {
		Print << U"hit";
	}
}
