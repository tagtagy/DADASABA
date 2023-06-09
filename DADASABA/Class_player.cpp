#include "stdafx.h"
#include "Class_player.h"

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
	
	Print <<U"マップ上のプレイヤー座標" << playerMapPos;
}
//攻撃
void Class_player::attack() {



}
//描画
void Class_player::draw() const {

	playerHit(playerTexture).draw(ColorF{ 1});

}
