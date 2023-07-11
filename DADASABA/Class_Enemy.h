#pragma once
# include "Common.h"
#include "Class_Bullet.h"
# include <cmath>
//最大の弾丸量
enum {
	bulletMax=4
};
class Class_Enemy
{
public:
	~Class_Enemy();
	Class_Enemy();
	//セット
	void set(Vec2 pos);
	//ターゲットの設定
	void Target_input(Vec2 TargetPos, Circle TargetHit);
	//動き
	void Move(Vec2 _MainCamera, double deltatime);
	//攻撃
	void Attack();
	//ノックバック
	void Knockback(bool _IsAttack, Circle*_AttackHitPos);
	//描画
	void Draw()const;

	//有効かどうかの提示
	bool valid() { return isValid; };
private:
	//正規化の計算
	//底辺,高さ,中心座標,回転の半径
	Vec2 normalization_calculate(double base, double tall, Vec2 centerPos, double range);
private:
	//敵テクスチャ
	const Texture EnemyTexture[3]{
		Texture{U"SOZAI/enemy/Jam_2023_No2_enemy_kokekiti_4.png"},
		Texture{U"SOZAI/enemy/Jam_2023_No2_enemy_nekomaru_9.png"},
		Texture{U"SOZAI/enemy/Jam_2023_tino.png"},
	};
	//描画する敵のナンバー
	int EnemyTextureNo = 0;
	//スクリーン上の座標
	Vec2 ScreenPos;
	//マップ上の座標
	Vec2 MapPos;
	//ターゲットの座標
	Vec2 targetPos;
	//ターゲットの当たり判定
	Circle targetHit;
	//スピード
	double speed;
	//動けるか
	bool ismove = true;
	//当たり判定
	Circle Ene_Hit;
	//攻撃が当たったか
	bool IsAttackHit = false;
	//無敵時間
	double InvincibleCount = 0;
	const double InvincibleTime = 1;
	//デルタタイム
	double delta_time = 0;
	//有効か？
	bool isValid = false;
	//ステータス/////////////////////////////////////////
	//HP
	int MaxHP[3] = {10,10,10};
	int HP = 0;
	//弾丸/////////////////////////////////////////////
	Class_Bullet* bullet[bulletMax];
	//発射するタイミング
	const double shootTime = 2;
	double shootCount = 0;
};

