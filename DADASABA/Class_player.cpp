#include "stdafx.h"
#include "Class_player.h"
//ボタン
void Class_player::button() {

	if (KeyLeft.pressed());
	else if (KeyRight.pressed());
	else if (KeyUp.pressed());
	else if (KeyDown.pressed());
}
//動き
void Class_player::move() {


	playerHit = { playerPos ,playerSize };
}
//攻撃
void Class_player::attack() {



}
//描画
void Class_player::draw() const {

	playerHit.draw(ColorF{ 1, 1, 1, 1 });

}
