#pragma once
# include <cmath>
enum {
	normalBullet1,
	normalBullet2,
	bossBullet,
	rangeBullet,
};
class Class_Bullet
{
public:
	Class_Bullet();
	//初期化
	void set(Vec2 MyPos, Vec2 TargetPos,int bulletType);
	//動き
	void Move(Vec2 _MainCamera, double deltatime);
	//衝突処理
	void BulletHiter(){if(enemyPos.intersects(BulletHit))Disable();}
	
	//有効かどうかの提示
	bool valid() { return isvalid; }
	
	Circle Bullet_Hit() { return BulletHit; }

	void Draw()const;
private:
	//通常弾
	void NormalBullet();
	//範囲攻撃
	void RangeBullet();
	//有効時間のカウント
	void ValidTimer();
	//弾の無効化
	void Disable();

	//正規化の計算
	//底辺,高さ,中心座標,回転の半径
	Vec2 normalization_calculate(double base, double tall, Vec2 centerPos, double range);
private:
	//弾のテクスチャ
	const Texture BulletTexture[3]{
		Texture{U"SOZAI/attack/INUNIKUCHUU1.png"},
		Texture{U"SOZAI/attack/INUNIKUCHUU2.png"},
		Texture{U"SOZAI/attack/Tabaco.png"},
	};
	//弾の種類
	int bullet_type;
	//通常弾/////////////////////////////////////////
	//移動方向座標
	Vec2 directionPos={0,0};
	//弾丸のスピード
	const double spped = 200;
	//当たり判定サイズ
	const int BulletSize = 10;
	//プレイヤーの座標
	Vec2 enemyPos={0,0};
	//マップ上の座標
	Vec2 BulletPos={0,0};
	//有効時間
	const double BulletValidTime = 2;
	double BulletValidCount=0;
	//範囲攻撃//////////////////////////////////////////////
	//攻撃場所
	Vec2 AttackRangePos;
	//攻撃チャージ
	double AttackRangeSize = 0;
	const int AttackRangeSizeMax = 100;
	//攻撃範囲表示
	Circle AttackRangeMark;

	////////////////////////////////////////////////////////
	//デルタタイム
	double delta_time = 0;
	//当たり判定
	Circle BulletHit;
	//有効か？
	bool isvalid =false;
};

