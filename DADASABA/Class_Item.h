#pragma once
# include <cmath>
#include <math.h>

class Class_Item
{
public:
	//初期化
	//Class_Item();
	//スポーンしたときの初期値を設定
	void init(Vec2 _itemPos);
	//マップの座標を更新
	void MapPos(Vec2 _playerPos, Circle _playerHit,Vec2 _MainCamera);
	//描画
	void draw() const;
	//プレイヤーとの当たり判定
	void hitPlayerHit(Circle _playerHit);

	bool getIsValid() { return IsValid; }
	void setIsValid(bool _isVaild) { IsValid = _isVaild; }
	bool getIsDestroy() { return isDestroy; }
private:
	//アイテムの位置
	Vec2 itemPos;
	//アイテムの当たり判定
	Circle itemHit;
	//画像
	const Texture itemRedTexture[2]{
		Texture{U"SOZAI/item/item1_1.png"},
		Texture{U"SOZAI/item/item2_1.png"},
	};
	//アイテムの使う種類
	int itemRedTextureNo = 0;
	//サイズ
	int itemSize=15;
	//プレイヤーと当たったら消えるフラグ
	bool isDestroy=false;
	//プレイヤーの方に向かうかどうか
	bool toPlayer = false;
	//有効かどうか
	bool IsValid = false;

	int count = 0;

	
};

