﻿#include "stdafx.h"
#include "Class_Bullet.h"

Class_Bullet::Class_Bullet() {
	//弾のサイズ設定
	BulletHit.r = BulletSize;

}

void Class_Bullet::set(Vec2 MyPos, Vec2 TargetPos, int bulletType) {
	//弾の設定
	bullet_type = bulletType;
	//出現位置の設定
	BulletPos = MyPos;
	//移動方向の設定
	Vec2 a= { TargetPos - MyPos };
	directionPos = normalization_calculate(a.x , a.y, { 0,0 }, spped );
	//出現
	isvalid = true;
	//有効時間の初期化
	BulletValidCount = 0;
}
//動き
void Class_Bullet::Move(Vec2 _MainCamera,double deltatime) {

	//デルタタイム
	delta_time = deltatime;

		//移動
	BulletPos += directionPos * delta_time;


	//スクリーン上位置の設定
	BulletHit.x = BulletPos.x - _MainCamera.x;
	BulletHit.y = BulletPos.y - _MainCamera.y;

	ValidTimer();

}
//有効時間のカウント
void Class_Bullet::ValidTimer() {

	if (BulletValidCount > BulletValidTime) Disable();
		
	BulletValidCount+= delta_time;
}
//弾の無効化
void Class_Bullet::Disable() {

	isvalid = false;
	
}
void Class_Bullet::Draw()const {

	if (isvalid) {
		//BulletHit.draw();
		BulletTexture[bullet_type].resized(40).rotated(Scene::Time() * 90_deg).drawAt(BulletHit.x, BulletHit.y);
	}
}

//正規化の計算
//底辺,高さ,中心座標,回転の半径
Vec2 Class_Bullet::normalization_calculate(double base, double tall, Vec2 centerPos, double range) {
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
