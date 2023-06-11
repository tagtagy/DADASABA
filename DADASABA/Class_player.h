﻿#pragma once
# include "Common.h"
# include <cmath>
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
	//攻撃の狙い
	void attack_aim();
	//プレイヤーの位置
	Vec2 playerPos();
	//攻撃
	void attack();
	//描画
	void draw() const;

private:
	//角度の計算
	//底辺,高さ
	double angle_calculate(double base, double tall);
	//正規化の計算
	//底辺,高さ,中心座標,回転の半径
	Vec2 normalization_calculate(double base, double tall,Vec2 centerPos,double range);
private:

	//マウス座標
	Vec2 mousePos;
	//攻撃関連////////////////////////////////////////////////////////////

	//プレイヤーの攻撃標準テクスチャ
	const Texture player_attack_mark_Texture{ U"仮素材/Sword.png" };
	//プレイヤーの攻撃位置
	Circle player_attack_mark {0,0,10};
	Vec2 player_attack_markPos { 0,0 };

	//自機関連////////////////////////////////////////////////////////////
	
	//プレイヤーテクスチャ
	const Texture playerTexture{ U"仮素材/Playerdebug.png" };
	//プレイヤーの当たり判定
	Circle playerHit;
	//移動するかどうか
	int moveX = 0;
	int moveY = 0;
	//スピード
	int speed = 10;
	//攻撃マーカーの角度の数値
	double angle_attack_mark = 10_deg;
	//プレイヤーのマップ上の位置
	Vec2 playerMapPos;
	//プレイヤーのスクリーン上の位置
	Vec2 ScreenPos;
	//プレイヤーのサイズ
	int playerSize = 30;
	
};


