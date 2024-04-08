#include "stdafx.h"
#include "C_E_Boss.h"
C_E_Boss::~C_E_Boss() {

	for (int i = 0; i < bulletMax; i++)
		if (bullet[i] != nullptr)delete bullet[i];

}

C_E_Boss::C_E_Boss() {
	//敵テクスチャ
	EnemyTexture << Texture{ U"SOZAI/enemy/Enemy_ChocolateMonkey05.png" };
	//敵のサイズ
	EnemySize = 100;

	//HP
	for (int i = 0; i < EnemyTexture.size() - 1; i++)MaxHP << 10;
	//動けるか
	ismove = true;
	//マップ上の座標
	MapPos = { 0,0 };
	//スクリーン上の座標
	ScreenPos = { 0,0 };
	//ターゲットの座標
	targetHit = { 0,0,0 };

	for (int i = 0; i < bulletMax; i++) bullet[i] = new Class_Bullet();

}
//セット
void C_E_Boss::set(Vec2 pos, int EnemyType) {
	//座標の設定
	MapPos = pos;
	//有効化
	isValid = true;

	//体力設定
	HP = MaxHP.front();
	
	bullet_type = normalBullet2;
	

	isDead = false;
}
//ターゲットの設定
void C_E_Boss::Target_input(Vec2 TargetPos, Circle TargetHit) {

	targetPos = TargetPos;
	targetHit = TargetHit;
}
void C_E_Boss::Move(Vec2 _MainCamera, double deltatime) {
	speed = Scene::DeltaTime() * 30;

	Attack();
	if (ismove) {
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
	for (int i = 0; i < bulletMax; i++) {
		if (bullet[i]->valid()) {
			bullet[i]->Move(_MainCamera, deltatime);
			
		}
	}
	//画面上の座標に変換
	ScreenPos = MapPos - _MainCamera;
	
		//座標更新
	Ene_Hit = { ScreenPos.x,ScreenPos.y, EnemySize };

	//Print <<U"敵のマップ上の座標" << MapPos;
	//Print << U"敵のスクリーン上の座標" << ScreenPos;
	//Print << U"敵のスクリーン上の当たり判定座標" << Ene_Hit;
}

void C_E_Boss::Attack() {
	//射撃
	if (shootCount >= shootTime) {
		shootCount -= shootTime;
		
		RangeBullet();
		
	}
	//射撃間隔のカウント
	shootCount += Scene::DeltaTime();

}
//範囲攻撃
void C_E_Boss::RangeBullet() {
	for (int i = 0; i < 4; i++) {
		if (!bullet[i]->valid()) {
			//爆破の中心位置
			Vec2 pos;
			pos.x = Random(400);
			pos.y = Random(400);
			int x = 1;
			int y = 1;

			if (i == 1)x = -1;
			else if (i == 2)y = -1;
			else if (i == 3) {
				x = -1;
				y = -1;
			}

			//範囲攻撃
			bullet[i]->set({ MapPos.x + pos.x * x,MapPos.y + pos.y * y }, { 0,0 }, rangeBullet);
		}
	}
}
//ノックバック
void C_E_Boss::Knockback(bool _IsAttack, Circle* _AttackHitPos) {

	//斬撃に当たったか
	if (_IsAttack) {

		for (int i = 0; i < 5; i++) {
			//斜辺の計算
			double lengthX = _AttackHitPos[i].x - ScreenPos.x;
			double lengthY = _AttackHitPos[i].y - ScreenPos.y;
			double hypotenuse = hypot(lengthX, lengthY);
			//斬撃に当たった時
			if (hypotenuse <= _AttackHitPos[i].r + Ene_Hit.r && InvincibleCount == 0) {
				//無敵でなければダメージを食らう
				HP -= 5;
				//HPが0以下なら死亡
				if (HP <= 0) {
					isValid = false;
					isDead = true;
				}
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

void C_E_Boss::Draw() const {
	//敵の描画
	Ene_Hit(EnemyTexture.front()).draw();
	//弾丸の描画
	for (int i = 0; i < bulletMax; i++) {
		bullet[i]->Draw();
	}
}
