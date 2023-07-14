#pragma once
# include <cmath>
enum {
	normalBullet1,
	normalBullet2,
	bossBullet,
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
	void BulletHiter(Circle TargetHit){if (BulletHit.intersects(TargetHit))Disable();};
	
	//有効かどうかの提示
	bool valid() { return isvalid; };

	void Draw()const;
private:
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
	//移動方向座標
	Vec2 directionPos={0,0};
	//弾丸のスピード
	const double spped = 100;
	//当たり判定サイズ
	const int BulletSize = 10;
	//プレイヤーの座標
	Vec2 enemyPos={0,0};
	//マップ上の座標
	Vec2 BulletPos={0,0};
	//有効時間
	const double BulletValidTime = 1;
	double BulletValidCount=0;
	//デルタタイム
	double delta_time = 0;
	//当たり判定
	Circle BulletHit{0,0,0};
	//有効か？
	bool isvalid =false;
};

