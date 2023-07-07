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
void Class_Enemy::set(Vec2 pos) {
	//座標の設定
	MapPos = pos;
	isValid = true;
	//出現する時に何の敵になるか決める
	int a = Random(2);
	EnemyTextureNo = a;
}
//ターゲットの設定
void Class_Enemy::Target_input(Vec2 TargetPos, Circle TargetHit) {

	targetPos = TargetPos;
	targetHit = TargetHit;
}
void Class_Enemy::Move() {
	speed = Scene::DeltaTime() * 30;

	Attack();

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
	//弾丸の移動
	for (int i=0; i < bulletMax; i++) {
		bullet[i]->Move(MapPos, { targetPos.x ,targetPos.y });
		if (bullet[i]->valid()) {
			bullet[i]->BulletHiter(targetHit);
		}
	}

	ScreenPos.x = MapPos.x - targetPos.x;
	ScreenPos.y = MapPos.y - targetPos.y;

	//座標更新
	Ene_Hit = { ScreenPos.x+400,ScreenPos.y + 300, 50 };

	//Print <<U"敵の座標" << ScreenPos;
	//Print << U"敵の攻撃カウント" << shootCount;
}

void Class_Enemy::Attack() {

	if (shootCount >= shootTime) {
		shootCount -= shootTime;
		for (int i=0; i < bulletMax; i++) {
			if (!bullet[i]->valid()) {
				bullet[i]->set(MapPos, { targetPos.x ,targetPos.y });
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
			double lengthX= _AttackHitPos[i].x - ScreenPos.x-400;
			double lengthY = _AttackHitPos[i].y - ScreenPos.y-300;
			double hypotenuse = hypot(lengthX, lengthY);
			//Print <<U"斜辺["<<i<<U"]" << hypotenuse;
			if (hypotenuse <= _AttackHitPos[i].r + Ene_Hit.r)IsAttackHit = true;
		}
	}
	//ノックバックの方向計算
	if(IsAttackHit)MapPos += normalization_calculate(targetPos.x - MapPos.x, targetPos.y - MapPos.y, { 0,0 }, 4) * -1;

	IsAttackHit = false;
}

void Class_Enemy::Draw() const{
	
	Ene_Hit(EnemyTexture[EnemyTextureNo]).draw(ColorF{1,0,0,1});

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
