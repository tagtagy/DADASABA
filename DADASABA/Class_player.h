#pragma once
# include "Common.h"
# include <cmath>
#include <math.h>
enum {
	//移動
	NoMove,
	Right = 1,
	Down = 1,
	Left = -1,
	Up = -1,
	//残像の数
	afterimageMax = 15,
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
	//攻撃
	void attack();
	//描画
	void draw() const;
	//獲得したアイテム数を加算
	void addItemCount();
	//アイテムの効果
	void itemBuff();


	//情報の提示
	//プレイヤーの位置
	Vec2 playerPos() { return playerMapPos; };
	//プレイヤーの当たり判定を取得
	Circle getPlayerHit() { return playerHit; };
	//プレイヤーの当たり判定アイテム用を取得
	Circle getPlayerHit_Item() { return playerHit_Item; };
	//攻撃しているかの受け渡し
	bool IsAttack_during() { return SlashingHit; }
	Circle* AttackHitPos() { return Slashing; }
private:
	//通常移動
	void normal_move();
	//回避移動
	void avoid_move();
	//残像の生成
	void afterimage_generate();
	//残像の消去
	void afterimage_delete();

	//角度の計算
	//底辺,高さ
	double angle_calculate(double base, double tall,bool isRadian);
	//特定のものを中心にずらした角度からベクトルへの変換
	//中心にする座標、ずらす角度
	Vec2 angle_vector_transformation(double base, double tall, double avoid);

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
		Texture{U"KARISOZAI/ZANGEKI1.png"},
		Texture{U"KARISOZAI/ZANGEKI2.png"},
		Texture{U"KARISOZAI/ZANGEKI3.png"},
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
	const Texture player_attack_mark_Texture{ U"SOZAI/player/PlayerArrow.png" };
	//プレイヤーの攻撃位置
	Circle player_attack_mark {0,0,10};
	Vec2 player_attack_markPos { 0,0 };

	//自機関連////////////////////////////////////////////////////////////
	
	//プレイヤーテクスチャ
	const Texture playerTexture{ U"SOZAI/player/Player_pokomaru_Ver2.png" };
	//プレイヤーの当たり判定
	Circle playerHit;
	//プレイヤーの当たり判定アイテム用
	Circle playerHit_Item;
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

	//攻撃の当たり判定//////////////////////////////////
	//斬撃
	Circle Slashing[5];
	Vec2 SlashingPos;
	bool SlashingHit=false;


	//アイテム//////////////////////////////////////////
	//バフの経過時間を保存
	double t = 0;
	//現在のアイテム獲得数
	int getItemCount = 0;
	bool buffFlag = false;
};


