#include "stdafx.h"
#include "Class_player.h"
# include <cmath>
Class_player::Class_player() {

	playerHit = { 400,300 ,playerSize };
	playerMapPos={ 0,0 };
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
}
//動き
void Class_player::move() {
	//横移動
	if (moveX != NoMove) playerMapPos.x += speed * moveX;
	//縦移動
	if (moveY != NoMove) playerMapPos.y += speed * moveY;
	Print<<a;
	Print <<U"マップ上のプレイヤー座標" << playerMapPos;
}
//攻撃の狙い
void Class_player::attack_aim() {
	//底辺の計算
	double base = mousePos.x - 400;
	//高さの計算
	double tall = mousePos.y - 300;
	//角度の計算
	a = Atan(tall / base) * (180 / 3.14);
	//補正
	if (base < 0) a -= 90;
	else a -= 270;
	//ラジアン化
	a *= (3.14 / 180);



	Print << base;
	Print << tall;
	Print << a;
}
//攻撃
void Class_player::attack() {



}
//描画
void Class_player::draw() const {

	playerHit.draw(ColorF{ 1 });
	playerTexture.resized(100).rotated(a).drawAt(playerHit.x, playerHit.y);
}
