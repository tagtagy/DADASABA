#include "stdafx.h"
#include "Class_Item.h"



void Class_Item::init(Vec2 _itemPos) {
	//アイテムの位置設定
	itemPos = _itemPos;
	//出現する時に何のアイテムになるか決める
	int a = Random(1);
	itemRedTextureNo = a;

	toPlayer = false;
	isDestroy = false;
}

void Class_Item::draw() const{
	//アイテムの描画
	itemHit(itemRedTexture[itemRedTextureNo]).draw();
}

void Class_Item::MapPos(Vec2 _playerPos, Circle _playerHit, Vec2 _MainCamera, double _deltaTime) {
	//アイテムの座標更新
	itemHit = { itemPos.x - _MainCamera.x, itemPos.y - _MainCamera.y,itemSize };

	if (toPlayer) {
		count++;
		Vec2 pos = { _playerPos.x - itemPos.x , _playerPos.y - itemPos.y };
		float length = sqrt(pos.x * pos.x + pos.y * pos.y);
		float normalX = pos.x / length;
		float normalY = pos.y / length;
		if (count < 50) {
			itemPos.x -= normalX * 300 * _deltaTime;
			itemPos.y -= normalY * 300 * _deltaTime;
		}
		else {
			itemPos.x += normalX *  300 * _deltaTime;
			itemPos.y += normalY *  300 * _deltaTime;
			if (itemHit.intersects(_playerHit)) {
				isDestroy = true;
				toPlayer = false;
			}
		}
	}
	else {
		isDestroy = false;
		count = 0;
	}
}

void Class_Item::hitPlayerHit(Circle _playerHit) {
	//プレイヤーに当たった時
	if (itemHit.intersects(_playerHit)) {
		toPlayer = true;
		count = 0;
	}
}
