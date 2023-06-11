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
}

void Class_Enemy::Attack() {

}

void Class_Enemy::Draw() const{
	
	Ene_Hit.draw(ColorF{ 1,0,0,1 });
}

