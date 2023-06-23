#include "stdafx.h"
#include "Class_Enemy.h"
Class_Enemy::Class_Enemy() {

	MapPos = { 0,0 };
	ScreenPos = { 0,0 };
	target = { 0,0 };

}
void Class_Enemy::Target_input(Vec2 TargetPos) {

	target = TargetPos;

}
void Class_Enemy::Move() {
	speed = Scene::DeltaTime() * 30;

	if (MapPos.x > target.x)
	{
		MapPos.x -= speed;
	}

	if (MapPos.x < target.x)
	{
		MapPos.x += speed;
	}

	if (MapPos.y > target.y)
	{
		MapPos.y -= speed;
	}

	if (MapPos.y < target.y)
	{
		MapPos.y += speed;
	}

	ScreenPos = MapPos - target;

	//座標更新
	Ene_Hit = { ScreenPos.x+400,ScreenPos.y + 300, 10 };

	Print <<U"敵の座標" << ScreenPos;
}

void Class_Enemy::Attack() {



}

void Class_Enemy::Knockback(bool _IsAttack, Rect* _AttackHitPos) {


	if(_IsAttack)
		for(int i=0;i<sizeof _AttackHitPos;i++)
			if (Ene_Hit.intersects(_AttackHitPos[i]))IsAttackHit = true;
			
	if(IsAttackHit)MapPos += normalization_calculate(target.x - MapPos.x, target.y - MapPos.y, { 0,0 }, 4) * -1;

	IsAttackHit = false;
}

void Class_Enemy::Draw() const{
	
	Ene_Hit.draw(ColorF{ 1,0,0,1 });
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
