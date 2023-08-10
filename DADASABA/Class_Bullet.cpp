#include "stdafx.h"
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
	//範囲攻撃カウントリセット
	AttackRangeSize = 0;
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
	if (bullet_type == bossBullet) {
		//通常攻撃
		NormalBullet();
	}
	else if (bullet_type == rangeBullet) {
		//範囲攻撃
		RangeBullet();
	}

	//スクリーン上位置の設定
	BulletHit.x = BulletPos.x - _MainCamera.x;
	BulletHit.y = BulletPos.y - _MainCamera.y;

	ValidTimer();

}

//通常弾
void Class_Bullet::NormalBullet() {

	//移動
	BulletPos += directionPos * delta_time;

}
//範囲攻撃
void Class_Bullet::RangeBullet() {
	//攻撃位置設定
	AttackRangePos = BulletPos;

	AttackRangeSize += 50 * delta_time;

	//攻撃マーカーの設定
	AttackRangeMark = { AttackRangePos ,AttackRangeSize };
	//マックスになったら消去
	if (AttackRangeSize >= AttackRangeSizeMax) Disable();

}
//有効時間のカウント
void Class_Bullet::ValidTimer() {
	if (bullet_type == bossBullet) {
		if (BulletValidCount > BulletValidTime) Disable();

		BulletValidCount += delta_time;
	}
}
//弾の無効化
void Class_Bullet::Disable() {

	isvalid = false;
	
}
void Class_Bullet::Draw()const {

	if (isvalid) {
		if (bullet_type == bossBullet) {
			//BulletHit.draw();
			BulletTexture[bullet_type].resized(40).rotated(Scene::Time() * 90_deg).drawAt(BulletHit.x, BulletHit.y);
		}
		else if (bullet_type == rangeBullet) {
			//範囲攻撃
			AttackRangeMark.draw(ColorF(1,0,0,1));
			Circle{ AttackRangeMark.x,AttackRangeMark.y,AttackRangeSizeMax }.drawFrame(3, 3, Palette::Orange);
		}
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
