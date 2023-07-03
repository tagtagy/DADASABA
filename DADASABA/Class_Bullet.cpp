#include "stdafx.h"
#include "Class_Bullet.h"

Class_Bullet::Class_Bullet() {
	//弾のサイズ設定
	BulletHit.r = BulletSize;

}

void Class_Bullet::set(Vec2 MyPos, Vec2 TargetPos) {
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
void Class_Bullet::Move(Vec2 MyPos, Vec2 TargetPos) {
	//有効な時だけ動かす
	if (isvalid) {
		//プレイヤーの座標
		enemyPos = TargetPos;

		//移動
		BulletPos += directionPos * Scene::DeltaTime();

		//スクリーン上位置の設定
		BulletHit.x = BulletPos.x - enemyPos.x + 400;
		BulletHit.y = BulletPos.y - enemyPos.y + 300;

		ValidTimer();
	}
}
//有効時間のカウント
void Class_Bullet::ValidTimer() {

	if (BulletValidCount > BulletValidTime) Disable();
		
	BulletValidCount+= Scene::DeltaTime();
}
//弾の無効化
void Class_Bullet::Disable() {

	isvalid = false;
	
}
void Class_Bullet::Draw()const {

	if(isvalid)BulletHit.draw();

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
