#pragma once
# include "Common.h"
enum {
	NoMove,
	Right,
	Left = -1

};
enum {
	Down = 1,
	Up = -1

};

class Class_player
{
public:
	Class_player();
	//ボタン
	void button();
	//動き
	void move();
	//攻撃
	void attack();
	//描画
	void draw() const;

private:
	//マウス座標
	Vec2 mousePos;

	//プレイヤーの当たり判定
	Circle playerHit;
	//移動するかどうか
	int moveX = 0;
	int moveY = 0;
	//スピード
	int speed = 10;
	//プレイヤーのマップ上の位置
	Vec2 playerMapPos;
	//プレイヤーのサイズ
	int playerSize = 10;
};


