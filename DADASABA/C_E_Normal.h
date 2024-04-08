#pragma once
#ifndef _C_E_NORMAL_H_
#define _C_E_NORMAL_H_
#include "P_Enemy.h"
class C_E_Normal:public P_Enemy
{
public:
	~C_E_Normal();
	C_E_Normal();
	//セット
	void set(Vec2 pos, int EnemyType);
	//ターゲットの設定
	void Target_input(Vec2 TargetPos, Circle TargetHit);
	//動き
	void Move(Vec2 _MainCamera, double deltatime);
	//攻撃
	void Attack();
	//ノックバック
	void Knockback(bool _IsAttack, Circle* _AttackHitPos);
	//描画
	void Draw()const;

	//有効かどうかの提示
	bool Getvalid() { return isValid; }
	void Setvalid(bool valid) { isValid = valid; }
	int EnemyHp() { return HP; }

	bool getIsDead() { return isDead; }

	Vec2 getEnemyPos() { return MapPos; }

	Class_Bullet* bullet[bulletMax];
private:

	//通常攻撃
	void NormalBullet();

private:
	//描画する敵のナンバー
	int EnemyTextureNo = 0;
	
	//ステータス/////////////////////////////////////////
	int HP = 0;
	//弾丸/////////////////////////////////////////////
	
	//弾の種類
	int bullet_type = normalBullet1;
	//発射するタイミング
	const double shootTime = 2;
	double shootCount = 0;

	//倒されたらtrue
	bool isDead = false;
	//SE////////////////////////////////////////////////
	//攻撃
	const Audio Attack_SE{ U"SOZAI/SE/ボタン音02.mp3" };
};


#endif
