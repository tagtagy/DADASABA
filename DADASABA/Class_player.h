#pragma once
class Class_player
{
public:
	//ボタン
	void button();
	//動き
	void move();
	//攻撃
	void attack();
	//描画
	void draw() const;

private:
	//プレイヤーの当たり判定
	Circle playerHit;
	//移動するかどうか
	bool moveX=false;
	bool moveY=false;
	//プレイヤーの位置
	Vec2 playerPos;
	//プレイヤーのサイズ
	int playerSize = 10;
};

