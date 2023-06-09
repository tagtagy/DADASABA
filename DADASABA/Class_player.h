#pragma once
# include "Common.h"

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

	enum {
		NoMove,
		Right,
		Left = -1
		
	};
	enum {
		Down = 1,
		Up = -1
		
	};

	//プレイヤーの当たり判定
	Circle playerHit;
	//移動するかどうか
	int moveX = 0;
	int moveY = 0;
	//スピード
	int speed = 10;
	//プレイヤーの位置
	Vec2 playerPos;
	//プレイヤーのサイズ
	int playerSize = 10;
};

