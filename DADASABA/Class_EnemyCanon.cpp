#include "stdafx.h"
#include "Class_EnemyCanon.h"

Class_EnemyCanon::~Class_EnemyCanon() {

	for (int i = 0; i < enemyMax+1; i++)
		if (enemy[i] != nullptr)delete enemy[i];

}

Class_EnemyCanon::Class_EnemyCanon() {
	for (int i = 0; i < enemyMax; i++)enemy[i] = new C_E_Normal();
	enemy[enemyMax] = new C_E_Boss();
}

//出現
//プレイヤーが斬撃の攻撃しているか、攻撃の当たり判定
void Class_EnemyCanon::appearance(Vec2 _TargetPos, Circle _TargetHit,
					              bool _IsAttack, Circle* _AttackHitPos,
					              Vec2 _MainCamera, double deltatime, Circle _TargetHit_Item) {
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
		if (enemy[enemyMax]->EnemyHp() <= 0)isBossLive = false;
	}

	//敵の動き
	for (int i = 0; i < enemyMax; i++) {
		if (isBossLive)i = enemyMax;
		if (enemy[i]->Getvalid()) {
			//敵のターゲットの座標取得
			enemy[i]->Target_input(_TargetPos, _TargetHit);
			enemy[i]->Move(_MainCamera, deltatime);
			//敵がプレイヤーの斬撃に当たった時
			enemy[i]->Knockback(_IsAttack, _AttackHitPos);

			if (enemy[i]->getIsDead()) {
				createItem.SpawnItem(enemy[i]->getEnemyPos());
			}
		}
	}

	createItem.UpDate(_TargetPos, _TargetHit_Item, _MainCamera);
}

void Class_EnemyCanon::Draw()const {
	//敵の描画
	for (int i = 0; i < enemyMax; i++)
		if (enemy[i]->Getvalid())enemy[i]->Draw();

	if (enemy[enemyMax]->Getvalid())enemy[enemyMax]->Draw();

	createItem.Draw();
}
//ボス出現
void Class_EnemyCanon::Boss_appearance() {
	//通常の敵を消す
	for (int i = 0; i < enemyMax; i++) {
		if (enemy[i]->Getvalid() == true) {
			enemy[i]->Setvalid(false);
		}
	}
	//ボスの出現
	enemy[enemyMax]->set({ 0,0 }, 0);
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
				int C=Random(3);
				double x = Random(-700,700);
				double y = Random(-400,400);
				enemy[i]->set({ x , y }, C);
				

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
