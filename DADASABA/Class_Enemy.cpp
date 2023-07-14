#include "stdafx.h"
#include "Class_Enemy.h"
Class_Enemy::~Class_Enemy() {

	for (int i = 0; i < bulletMax; i++)
		if (bullet[i] != nullptr)delete bullet[i];

}

Class_Enemy::Class_Enemy() {

	MapPos = { 0,0 };
	ScreenPos = { 0,0 };
	targetHit = { 0,0,0 };
	
	for (int i=0; i < bulletMax; i++) bullet[i]=new Class_Bullet;
	
}
//セット
void Class_Enemy::set(Vec2 pos, int EnemyType) {
	//座標の設定
	MapPos = pos;
	//有効化
	isValid = true;
	EnemyTextureNo = EnemyType;
	if (EnemyType == 0) {
		//出現する時に何の敵になるか決める
		EnemyTextureNo = Random(2);
	}
	else if (EnemyType == bossEnemy) {
		EnemyTextureNo = 3;
	}
	
	//体力設定
	HP = MaxHP[EnemyTextureNo];
	if (EnemyTextureNo > 1) {
		//ノーマル1タイプの弾丸
		bullet_type = normalBullet1;
	}
	else if (EnemyTextureNo == 2) {
		//ノーマル2タイプの弾丸
		bullet_type = normalBullet2;
	}

}
//ターゲットの設定
void Class_Enemy::Target_input(Vec2 TargetPos, Circle TargetHit) {

	targetPos = TargetPos;
	targetHit = TargetHit;
}
void Class_Enemy::Move(Vec2 _MainCamera, double deltatime) {
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
	for (int i=0; i < bulletMax; i++) {
		if (bullet[i]->valid()) {
			bullet[i]->Move(_MainCamera, deltatime);
			bullet[i]->BulletHiter(targetHit);
		}
	}
	//画面上の座標に変換
	ScreenPos =   MapPos- _MainCamera;
	//座標更新
	Ene_Hit = { ScreenPos.x,ScreenPos.y, 50 };

	Print <<U"敵のマップ上の座標" << MapPos;
	Print << U"敵のスクリーン上の座標" << ScreenPos;
	Print << U"敵のスクリーン上の当たり判定座標" << Ene_Hit;
}

void Class_Enemy::Attack() {
	//射撃
	if (shootCount >= shootTime) {
		shootCount -= shootTime;
		for (int i=0; i < bulletMax; i++) {
			if (!bullet[i]->valid()) {
				bullet[i]->set(MapPos, { targetPos.x ,targetPos.y }, bullet_type);
				i = bulletMax;
			}
		}
	}
	//射撃間隔のカウント
	shootCount += Scene::DeltaTime();

}
//ノックバック
void Class_Enemy::Knockback(bool _IsAttack, Circle* _AttackHitPos) {

	//斬撃に当たったか
	if (_IsAttack) {
		
		for (int i = 0; i < 5; i++) {
			//斜辺の計算
			double lengthX= _AttackHitPos[i].x - ScreenPos.x;
			double lengthY = _AttackHitPos[i].y - ScreenPos.y;
			double hypotenuse = hypot(lengthX, lengthY);
			//斬撃に当たった時
			if (hypotenuse <= _AttackHitPos[i].r + Ene_Hit.r&& InvincibleCount==0) {
				//無敵でなければダメージを食らう
				HP -= 5;
				//HPが0以下なら死亡
				if (HP <= 0)isValid = false;
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

void Class_Enemy::Draw() const{
	//敵の描画
	Ene_Hit(EnemyTexture[EnemyTextureNo]).draw(ColorF{1,0,0,1});
	//弾丸の描画
	for (int i=0; i < bulletMax; i++) {
		bullet[i]->Draw();
	}
}

//正規化の計算
//底辺,高さ,中心座標,回転の半径
Vec2 Class_Enemy::normalization_calculate(double base, double tall, Vec2 centerPos, double range) {
	if (base == 0)return{ 10,0 };
	else {
		//斜辺の計算
		double hypotenuse = hypot(base, tall);
		//底辺の正規化
		double base_Normalization = base / hypotenuse;
		//高さの正規化
		double tall_Normalization = tall / hypotenuse;

		return  { base_Normalization * range + centerPos.x, tall_Normalization * range + centerPos.y };
	}
}
