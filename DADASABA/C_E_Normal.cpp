#include "stdafx.h"
#include "C_E_Normal.h"
C_E_Normal::~C_E_Normal() {

	for (int i = 0; i < bulletMax; i++)
		if (bullet[i] != nullptr)delete bullet[i];

}

C_E_Normal::C_E_Normal() {

	MapPos = { 0,0 };
	ScreenPos = { 0,0 };
	targetHit = { 0,0,0 };

	for (int i = 0; i < bulletMax; i++) bullet[i] = new Class_Bullet();

}
//セット
void C_E_Normal::set(Vec2 pos, int EnemyType) {
	//座標の設定
	MapPos = pos;
	//有効化
	isValid = true;
	EnemyTextureNo = EnemyType;

	//体力設定
	HP = MaxHP[EnemyTextureNo];
	if (EnemyTextureNo > 3) {
		//ノーマル1タイプの弾丸
		bullet_type = normalBullet1;
	}
	else if (EnemyTextureNo == 3) {
		//ノーマル2タイプの弾丸
		bullet_type = normalBullet2;
	}

	isDead = false;
}
//ターゲットの設定
void C_E_Normal::Target_input(Vec2 TargetPos, Circle TargetHit) {

	targetPos = TargetPos;
	targetHit = TargetHit;
}
void C_E_Normal::Move(Vec2 _MainCamera, double deltatime) {
	speed = Scene::DeltaTime() * 30;
	if (ismove) {
		//射撃
		Attack();
		//移動
		if (MapPos.x > targetPos.x)
		{
			MapPos.x -= speed;
		}

		if (MapPos.x < targetPos.x)
		{
			MapPos.x += speed;
		}

		if (MapPos.y > targetPos.y)
		{
			MapPos.y -= speed;
		}

		if (MapPos.y < targetPos.y)
		{
			MapPos.y += speed;
		}
	}
	//弾丸の移動
	for (int i = 0; i < bulletMax; i++) {
		if (bullet[i]->valid()) {
			bullet[i]->Move(_MainCamera, deltatime);
			bullet[i]->BulletHiter(targetHit);
		}
	}
	//画面上の座標に変換
	ScreenPos = MapPos - _MainCamera;
		//座標更新
		Ene_Hit = { ScreenPos.x,ScreenPos.y, EnemySize };
}

void C_E_Normal::Attack() {
	//射撃
	NormalBullet();
	//射撃間隔のカウント
	shootCount += Scene::DeltaTime();

}
//通常弾
void C_E_Normal::NormalBullet() {

	if (shootCount >= shootTime) {
		shootCount -= shootTime;
		for (int i = 0; i < bulletMax; i++) {
			if (!bullet[i]->valid()) {
				bullet[i]->set(MapPos, { targetPos.x ,targetPos.y }, bullet_type);
				i = bulletMax;
			}
		}
	}

}
//ノックバック
void C_E_Normal::Knockback(bool _IsAttack, Circle* _AttackHitPos) {

	//斬撃に当たったか
	if (_IsAttack) {

		for (int i = 0; i < 5; i++) {
			//斜辺の計算
			double lengthX = _AttackHitPos[i].x - ScreenPos.x;
			double lengthY = _AttackHitPos[i].y - ScreenPos.y;
			double hypotenuse = hypot(lengthX, lengthY);
			//斬撃に当たった時
			if (hypotenuse <= _AttackHitPos[i].r + Ene_Hit.r && InvincibleCount == 0) {
				//無敵でなければダメージを食らう
				HP -= 5;
				//HPが0以下なら死亡
				if (HP <= 0) {
					isValid = false;
					isDead = true;
				}
				//ノックバックの方向計算
				MapPos += normalization_calculate(targetPos.x - MapPos.x, targetPos.y - MapPos.y, { 0,0 }, 100) * -1;
				InvincibleCount = InvincibleTime;
			}
		}
	}
	//無敵時間の処理
	if (InvincibleCount > 0) {
		InvincibleCount -= Scene::DeltaTime();
		ismove = false;
	}
	else {
		InvincibleCount = 0;
		ismove = true;

	}

}

void C_E_Normal::Draw() const {
	//敵の描画
	Ene_Hit(EnemyTexture[EnemyTextureNo]).draw();
	//弾丸の描画
	for (int i = 0; i < bulletMax; i++) {
		bullet[i]->Draw();
	}
}
