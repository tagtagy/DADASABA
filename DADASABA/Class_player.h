#pragma once
# include "Common.h"
# include <cmath>
enum {
	//移動
	NoMove,
	Right = 1,
	Down = 1,
	Left = -1,
	Up = -1,
	//残像の数
	afterimageMax = 10,
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
	Vec2 playerPos() { return playerMapPos; };
	//攻撃
	void attack();
	//描画
	void draw() const;

	Circle getPlayerHit() { return playerHit; };

private:
	//通常移動
	void normal_move();
	//回避移動
	void avoid_move();
	//残像
	void afterimage();

	//角度の計算
	//底辺,高さ
	double angle_calculate(double base, double tall);
	//正規化の計算
	//底辺,高さ,中心座標,回転の半径
	Vec2 normalization_calculate(double base, double tall,Vec2 centerPos,double range);
private:

	//マウス座標
	Vec2 mousePos;
	//デルタタイム
	double delta_time;
	//攻撃関連////////////////////////////////////////////////////////////
	//攻撃ボタン
	bool attack_button=false;
	//攻撃時間
	double attack_count = 0;
	//攻撃の有効時間
	double attack_time = 0.1;
	//斬撃
	const Texture ZANGEKI[3]{
		Texture{U"仮素材/ZANGEKI1.png"},
		Texture{U"仮素材/ZANGEKI2.png"},
		Texture{U"仮素材/ZANGEKI3.png"},
	};
	//攻撃のアニメーション
	int attack_animation = 0;
	//攻撃の角度
	double attack_avoid = 0;
	//攻撃の方向
	Vec2 attack_direction = { 0,0 };
	//攻撃マーカーの角度の数値
	double angle_attack_mark = 10_deg;

	//プレイヤーの攻撃標準テクスチャ
	const Texture player_attack_mark_Texture{ U"SOZAI/プレイヤー/PlayerArrow.png" };
	//プレイヤーの攻撃位置
	Circle player_attack_mark {0,0,10};
	Vec2 player_attack_markPos { 0,0 };

	//自機関連////////////////////////////////////////////////////////////
	
	//プレイヤーテクスチャ
	const Texture playerTexture{ U"SOZAI/プレイヤー/Player_pokomaru_Ver2.png" };
	//プレイヤーの当たり判定
	Circle playerHit;
	//移動するかどうか
	int moveX = 0;
	int moveY = 0;
	//スピード
	const int speed = 300;

	//回避経過時間
	double avoid_count = false;
	//最大回避時間
	const double avoid_time = 0.5;
	//回避スピード
	Vec2 avoid_speed = { 0,0 };

	//残像の透明度
	double afterimage_clear[afterimageMax];
	//残像の更新時間
	const double afterimage_update=0.05;
	//残像の出現管理
	double afterimage_emergence=0;
	//残像の描画管理
	bool Isafterimage[afterimageMax];
	//残像のマップ上の位置
	Vec2 afterimageMapPos[afterimageMax];
	//残像のスクリーン上の位置
	Vec2 afterimageScreenPos[afterimageMax];

	//プレイヤーのマップ上の位置
	Vec2 playerMapPos;
	//プレイヤーのスクリーン上の位置
	Vec2 ScreenPos;
	//プレイヤーのサイズ
	int playerSize = 30;
	
};


