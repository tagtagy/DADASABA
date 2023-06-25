﻿#pragma once
# include <cmath>
class Class_Bullet
{
public:
	void set(Vec2 MyPos, Vec2 TargetPos);
	//動き
	void Move(Vec2 MyPos, Vec2 TargetPos);
	//弾の無効化
	void Disable(Circle TargetHit);
	//有効かどうかの提示
	bool valid() { return IsValid; };

	void Draw()const;
private:
	//正規化の計算
	//底辺,高さ,中心座標,回転の半径
	Vec2 normalization_calculate(double base, double tall, Vec2 centerPos, double range);
private:
	//移動方向座標
	Vec2 directionPos;
	//弾丸のスピード
	const double spped = 100;
	//当たり判定サイズ
	const int BulletSize = 10;
	//敵の座標
	Vec2 enemyPos;
	//マップ上の座標
	Vec2 BulletPos;
	//スクリーン上の座標
	Vec2 BulletScreenPos;
	//当たり判定
	Circle BulletHit;
	//有効か？
	bool IsValid=false;
};
