#include "stdafx.h"
#include "Class_EnemyCanon.h"

Class_EnemyCanon::~Class_EnemyCanon() {

	for (int i = 0; i < enemyMax; i++)
		if (enemy[i] != nullptr)delete enemy[i];

}
Class_EnemyCanon::Class_EnemyCanon() {
	for (int i = 0; i < enemyMax; i++)enemy[i] = new Class_Enemy;
}

//出現
//プレイヤーが斬撃の攻撃しているか、攻撃の当たり判定
void Class_EnemyCanon::appearance(Vec2 _TargetPos, Circle _TargetHit,
					              bool _IsAttack, Circle* _AttackHitPos,
					              Vec2 _MainCamera, double deltatime) {
	//ターゲットの設定
	TargetPos = _TargetPos;
	delta_time = deltatime;
	if (angleTime > 0) {
		//ランダム出現
		random_appearance();
	}
	else {
		//ボス出現
		if(!isBossFight)Boss_appearance();
		if (enemy[0]->EnemyHp() <= 0)isBossLive = false;
	}

	//敵の動き
	for (int i = 0; i < enemyMax; i++) {
		if (enemy[i]->Getvalid()) {
			//敵のターゲットの座標取得
			enemy[i]->Target_input(_TargetPos, _TargetHit);
			enemy[i]->Move(_MainCamera, deltatime);
			//敵がプレイヤーの斬撃に当たった時
			enemy[i]->Knockback(_IsAttack, _AttackHitPos);
		}
	}

}

void Class_EnemyCanon::Draw()const {
	//敵の描画
	for (int i = 0; i < enemyMax; i++)
		if (enemy[i]->Getvalid())enemy[i]->Draw();

}
//ボス出現
void Class_EnemyCanon::Boss_appearance() {
	for (int i = 0; i < enemyMax; i++) {
		if (enemy[i]->Getvalid() == true) {
			enemy[i]->Setvalid(false);
		}
	}
	if (enemy[0]->Getvalid() == false)
	enemy[0]->set({ 0,0}, bossEnemy);
	//ボス戦開始
	isBossFight = true;
}
//ランダム出現
void Class_EnemyCanon::random_appearance() {
	
	if (appearanceCount > appearanceTime) {
		//カウントリセット
		appearanceCount -= appearanceTime;
		//敵の出現
		for (int i = 0; i < enemyMax; i++) {
			if (enemy[i]->Getvalid() == false) {
				int C=Random(2);

				int a = Random(1);
				int b = Random(1);
				if (b == 0)b = -1;
				//縦方向から来る敵
				if (a) {
					double r = Random(800);
					enemy[i]->set({ r + TargetPos.x, 600 * b + TargetPos.y }, C);
				}
				//横方向から来る敵
				else{
					double r = Random(800);
					enemy[i]->set({ 800 * b + TargetPos.x,r + TargetPos.y }, C);
				}

				i = enemyMax;
			}
		}

	}

	appearanceCount += delta_time;
}
//籠目出現
void Class_EnemyCanon::ghost_appearance() {



}
//円出現
void Class_EnemyCanon::circle_appearance() {



}
