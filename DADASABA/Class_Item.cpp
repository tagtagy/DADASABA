#include "stdafx.h"
#include "Class_Item.h"



void Class_Item::init(Vec2 _itemPos) {
	//アイテムの位置設定
	itemPos = _itemPos + Vec2(400, 300);
	//出現する時に何のアイテムになるか決める
	int a = Random(1);
	itemRedTextureNo = a;
}

void Class_Item::draw() const{
	//アイテムの描画
	itemHit(itemRedTexture[itemRedTextureNo]).draw();
}

void Class_Item::MapPos(Vec2 _playerPos) {
	//アイテムの座標更新
	itemHit = { itemPos.x - _playerPos.x, itemPos.y - _playerPos.y,itemSize };
}

void Class_Item::hitPlayerHit(Circle _playerHit) {
	//プレイヤーに当たった時
	if (itemHit.intersects(_playerHit)) {
		isDestroy = true;
	}
	else {
		isDestroy = false;
	}
}
