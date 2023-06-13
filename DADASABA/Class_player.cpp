#include "stdafx.h"
#include "Class_player.h"

Class_player::Class_player() {

	playerHit = { 400,300 ,playerSize };
	playerMapPos= { 400,300 };
}

//ボタン
void Class_player::button() {
	//マウスの位置
	mousePos = Cursor::Pos();

	//X移動
	if (KeyLeft.pressed()|| KeyA.pressed()) moveX = Left;
	else if (KeyRight.pressed()|| KeyD.pressed()) moveX = Right;
	else moveX = NoMove;
	//Y移動
	if (KeyUp.pressed()|| KeyW.pressed())moveY = Up;
	else if (KeyDown.pressed()|| KeyS.pressed())moveY = Down;
	else moveY = NoMove;

	//回避
	if (MouseR.down()) {
		avoid_count = avoid_time;
		//正規化
		avoid_speed = normalization_calculate(mousePos.x - 400, mousePos.y - 300, { 0,0 }, (speed + 800) * delta_time);
	}
	delta_time = Scene::DeltaTime();
}
//動き
void Class_player::move() {
	//回避移動
	if (avoid_count!=false)avoid_move();
	//通常移動
	else normal_move();

	Print <<U"マップ上のプレイヤー座標" << playerMapPos;
	Print << U"角度(ベクトル値)" << angle_attack_mark;
	Print << U"回避の方角" << avoid_speed;
	Print << U"回避の時間" << avoid_count;
}
//通常移動
void Class_player::normal_move() {
	//横移動
	if (moveX != NoMove) playerMapPos.x += speed * moveX * delta_time;
	//縦移動
	if (moveY != NoMove) playerMapPos.y += speed * moveY * delta_time;
}
//回避移動
void Class_player::avoid_move() {
	
	
	playerMapPos += avoid_speed;

	avoid_count-= delta_time;
	if (avoid_count < 0)avoid_count = 0;

	
}
//攻撃の狙い
void Class_player::attack_aim() {
	//角度の計算
	angle_attack_mark = angle_calculate(mousePos.x - 400, mousePos.y - 300);
	//正規化
	player_attack_markPos = normalization_calculate(mousePos.x - 400, mousePos.y - 300,{400,300},50);

	player_attack_mark = { player_attack_markPos ,10 };

	Print <<U"攻撃マーカー座標" << player_attack_markPos;
}

//攻撃
void Class_player::attack() {



}
//描画
void Class_player::draw() const {
	//プレイヤーの当たり判定
	playerHit.draw(ColorF{ 1 });
	//プレイヤーのテクスチャ
	playerTexture(0,0,1200,1200).resized(100).drawAt(playerHit.x, playerHit.y);
	//プレイヤーの攻撃マーカー
	player_attack_mark.draw(ColorF{ 1 });

	player_attack_mark_Texture.resized(50).rotated(angle_attack_mark).drawAt(player_attack_markPos);
}

//角度の計算
//底辺,高さ
double Class_player::angle_calculate(double base, double tall) {

	//角度の計算
	double angle = Atan(tall / base) * (180 / 3.14);
	//補正
	if (base < 0) angle -= 90;
	else angle -= 270;
	//ラジアン化
	angle *= (3.14 / 180);

	return angle;
}
//正規化の計算
//底辺,高さ,中心座標,回転の半径
Vec2 Class_player::normalization_calculate(double base, double tall, Vec2 centerPos, double range) {

	//斜辺の計算
	double hypotenuse = hypot(base, tall);
	//底辺の正規化
	double base_Normalization = base / hypotenuse;
	//高さの正規化
	double tall_Normalization = tall / hypotenuse;
	
	return  { base_Normalization * range + centerPos.x, tall_Normalization * range + centerPos.y };
}
