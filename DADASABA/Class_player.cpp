#include "stdafx.h"
#include "Class_player.h"
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
	if (moveX != NoMove) playerPos.x += speed * moveX;
	//縦移動
	if (moveY != NoMove) playerPos.y += speed * moveY;

	
	//座標代入
	playerHit = { playerPos ,playerSize };
}
//攻撃
void Class_player::attack() {



}
//描画
void Class_player::draw() const {

	playerHit.draw(ColorF{ 1, 1, 1, 1 });

}
