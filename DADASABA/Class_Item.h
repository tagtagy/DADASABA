#pragma once
class Class_Item
{
public:
	//初期化
	//Class_Item();
	//スポーンしたときの初期値を設定
	void init(Vec2 _itemPos);
	//マップの座標を更新
	void MapPos(Vec2 _playerPos);
	//描画
	void draw() const;
	//プレイヤーとの当たり判定
	void hitPlayerHit(Circle _playerHit);

	bool getIsValid() { return IsValid; }
private:
	//アイテムの位置
	Vec2 itemPos;
	//アイテムの当たり判定
	Circle itemHit;
	//画像
	const Texture itemRedTexture{ U"KARISOZAI/DropItemRed.png" };
	//サイズ
	int itemSize=15;
	//プレイヤーと当たったら消えるフラグ
	bool isDestroy=false;
	//有効かどうか
	bool IsValid = false;
};

