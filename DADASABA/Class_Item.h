﻿#pragma once
class Class_Item
{
public:
	//初期化
	Class_Item();
	//スポーンしたときの初期値を設定
	void init(Vec2 _itemPos, Vec2 _playerPos);
	//マップの座標を更新
	void MapPos(Vec2 _playerPos);
	//描画
	void draw();
	//プレイヤーとの当たり判定
	void hitPlayerHit(Circle _playerHit);
private:
	//アイテムの位置
	Vec2 itemPos;
	//アイテムの当たり判定
	Circle itemHit;
	//画像
	const Texture itemRedTexture{ U"仮素材/DropItemRed.png" };
	//サイズ
	int itemSize;
};
