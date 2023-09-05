#include "stdafx.h"
#include "Class_CreateItem.h"

Class_CreateItem::Class_CreateItem() {
	for (int i = 0; i < maxItemNum; i++) {
		item[i] = new Class_Item();

	}
}

Class_CreateItem::~Class_CreateItem() {
	for (int i = 0; i < maxItemNum; i++) {
		if (item[i] != nullptr) delete item[i];
	}
}

void Class_CreateItem::UpDate(Vec2 _playerPos, Circle _playerHit_Item, Vec2 _MainCamera) {
	//デバッグ用
	if (KeyI.down()) {
		int rX = Random(-1000, 1000);
		int rY = Random(-1000, 1000);
		//マップ上の座標に出るように変更しました
		SpawnItem({ rX,rY });
	}

	//全ての要素にアクセス
	for (int i = 0; i < maxItemNum; i++) {
		//有効な時
		if (item[i]->getIsValid()) {
			//描画位置の更新
			item[i]->MapPos(_playerPos, _playerHit_Item, _MainCamera);
			//当たり判定
			item[i]->hitPlayerHit(_playerHit_Item);
			if (item[i]->getIsDestroy()) {
				addCount++;
				item[i]->setIsValid(false);
				//アイテム取得SE
				itemHit_SE.play();
			}
		}
	}
}

void Class_CreateItem::Draw() const {
	for (int i = 0; i < maxItemNum; i++) {
		if (item[i]->getIsValid()) {
			item[i]->draw();
		}
	}
}

void Class_CreateItem::SpawnItem(Vec2 _enemyPos) {
	for (int i = 0; i < maxItemNum; i++) {
		if (!item[i]->getIsValid()) {
			//初期位置を設定（playerの位置を足して調整）
			item[i]->init(_enemyPos);
			item[i]->setIsValid(true);
			i = maxItemNum;
		}
	}
}
