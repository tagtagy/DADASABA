#include "stdafx.h"
#include "Class_Item.h"


void Class_Item::init(Vec2 _itemPos) {
	itemPos.x = _itemPos.x + 400;
	itemPos.y = _itemPos.y + 300;
}

void Class_Item::draw() const{
	itemHit(itemRedTexture).draw();
}

void Class_Item::MapPos(Vec2 _playerPos) {
	itemHit = { itemPos.x - _playerPos.x, itemPos.y - _playerPos.y,itemSize };
}

void Class_Item::hitPlayerHit(Circle _playerHit) {
	if (itemHit.intersects(_playerHit)) {
		isDestroy = true;
	}
	else {
		isDestroy = false;
	}
}
