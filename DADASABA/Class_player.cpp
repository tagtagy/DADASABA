#include "stdafx.h"
#include "Class_player.h"

Class_player::Class_player() {

	playerHit = { 400,300 ,playerSize };
	playerMapPos= {0,0 };
	for (int i = 0; i < 5; i++)afterimageMapPos[i]={0,0};
	playerHit_Item = { 400,300,playerSize };
}

//ボタン
void Class_player::button(double deltatime) {
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

	//攻撃
	//攻撃中でない時
	if (MouseL.down()&& !attack_button) {
		attack_count = attack_time;
		attack_button = true;
		//攻撃（今は斬撃）の当たり判定の有効化
		SlashingHit = true;
		//回避のキャンセル
		avoid_count = false;
		//攻撃場所の決定
		W_AttackM_Pos = mousePos;
		
	}

	//回避
	//攻撃中でない時
	//回避中でない時
	if (MouseR.down()&& !attack_button && !avoid_count) {
		avoid_count = avoid_time;
		afterimage_emergence = 0;
		//正規化
		avoid_speed = normalization_calculate(mousePos.x - ScreenPos.x, mousePos.y - ScreenPos.y, { 0,0 }, (speed + 800) * delta_time);
	}
	//共有のデルタタイム
	delta_time = deltatime;
}
//動き
void Class_player::move() {
	//回避移動
	if (avoid_count!=false)avoid_move();
	//通常移動
	else normal_move();

	//残像の消去
	afterimage_delete();

	//攻撃行動
	if (attack_button)attack();

	//スクリーン用に座標変換
	ScreenPos = playerMapPos-Camera ;
	playerHit.x = ScreenPos.x;
	playerHit.y = ScreenPos.y;

	playerHit_Item.x= ScreenPos.x;
	playerHit_Item.y = ScreenPos.y;

	Print <<U"マップ上のプレイヤー座標" << playerMapPos;
	Print << U"スクリーン上のプレイヤー座標" << ScreenPos;
	Print << U"プレイヤーからのマウスの角度" << int(angle_attack_mark * (180/3.14))<<U"°";
	Print << U"攻撃マーカー座標" << player_attack_markPos;
	Print << U"回避の方角" << avoid_speed;
	Print << U"回避の時間" << avoid_count;
}
//通常移動
void Class_player::normal_move() {
	double x= speed * moveX * delta_time;
	//横移動
	if (-1537 / 2 < playerMapPos.x + x && playerMapPos.x + x < 1537 / 2) playerMapPos.x += x;

	double y = speed * moveY * delta_time;
	//縦移動
	if (-865 /2 < playerMapPos.y + y && playerMapPos.y + y < 865 / 2) playerMapPos.y += y;
}
//回避移動
void Class_player::avoid_move() {
	//回避横移動
	if (-1537 / 2 < playerMapPos.x + avoid_speed.x && playerMapPos.x + avoid_speed.x < 1537 / 2)playerMapPos.x += avoid_speed.x;
	//回避横移動
	if (-865 / 2 < playerMapPos.y + avoid_speed.y && playerMapPos.y + avoid_speed.y < 865 / 2)playerMapPos.y += avoid_speed.y;
	
	//残像の描画
	afterimage_generate();
	//回避の時間制限
	avoid_count-= delta_time;
	if (avoid_count < 0)avoid_count = 0;
}
//残像の生成
void Class_player::afterimage_generate() {
	if (afterimage_emergence >= afterimage_update) {
		for (int i = 0; i < afterimageMax; i++) {
			//残像が描画されていない時
			if (!Isafterimage[i]) {
				//座標を更新する
				afterimageMapPos[i] = playerMapPos;
				//残像の描画
				Isafterimage[i] = true;

				i = afterimageMax;
			}
		}
	}
}
//残像の消去
void Class_player::afterimage_delete() {

	if (afterimage_emergence >= afterimage_update) {
		afterimage_emergence -= afterimage_update;

		for (int i = 0; i < afterimageMax; i++) {
			//残像が描画されている時
			if (Isafterimage[i]) {
				//透明度を下げる
				afterimage_clear[i] -= delta_time * 10;
				//完全に透明になったら描画を切る
				if (afterimage_clear[i] < 0) Isafterimage[i] = false;
			}
			if (!Isafterimage[i]) {
				//透明度を元に戻す
				afterimage_clear[i] = 1;
			}
		}
	}
	afterimage_emergence += delta_time;
	//残像の位置更新
	for (int i = 0; i < afterimageMax; i++)afterimageScreenPos[i] = afterimageMapPos[i] - playerMapPos + ScreenPos;

}
//攻撃の狙い
void Class_player::attack_aim() {
	//アニメーションの位置
	attack_avoid = angle_calculate(W_AttackM_Pos.x - ScreenPos.x, W_AttackM_Pos.y - ScreenPos.y, true);
	attack_avoid *= (180 / 3.14);
	attack_avoid += 130;
	attack_avoid *= (3.14 / 180);
	attack_direction = normalization_calculate(W_AttackM_Pos.x - ScreenPos.x, W_AttackM_Pos.y - ScreenPos.y, ScreenPos, 40);

	//角度の計算
	angle_attack_mark = angle_calculate(mousePos.x - ScreenPos.x, mousePos.y - ScreenPos.y,true);
	//正規化
	player_attack_markPos = normalization_calculate(mousePos.x - ScreenPos.x, mousePos.y - ScreenPos.y, ScreenPos,50);
	//攻撃のマーカー位置
	player_attack_mark = { player_attack_markPos ,10 };

	//斬撃の当たり判定
	//中心
	SlashingPos = normalization_calculate(W_AttackM_Pos.x - ScreenPos.x, W_AttackM_Pos.y - ScreenPos.y, ScreenPos, 50);
	Slashing[2] = { SlashingPos.x  ,SlashingPos.y,25 };

	//中心に追従
	//右端
	SlashingPos=angle_vector_transformation(W_AttackM_Pos.x - ScreenPos.x, W_AttackM_Pos.y - ScreenPos.y, -50);
	Slashing[0] = { SlashingPos.x *50 + ScreenPos.x  ,SlashingPos.y *50 + ScreenPos.y ,15 };
	//右中
	SlashingPos = angle_vector_transformation(W_AttackM_Pos.x - ScreenPos.x, W_AttackM_Pos.y - ScreenPos.y, -25);
	Slashing[1] = { SlashingPos.x * 50 + ScreenPos.x  ,SlashingPos.y * 50 + ScreenPos.y ,20 };
	//左中
	SlashingPos = angle_vector_transformation(W_AttackM_Pos.x - ScreenPos.x, W_AttackM_Pos.y - ScreenPos.y, 25);
	Slashing[3] = { SlashingPos.x * 50 + ScreenPos.x  ,SlashingPos.y * 50 + ScreenPos.y ,20 };
	//左端
	SlashingPos = angle_vector_transformation(W_AttackM_Pos.x - ScreenPos.x, W_AttackM_Pos.y - ScreenPos.y, 50);
	Slashing[4] = { SlashingPos.x * 50 + ScreenPos.x  ,SlashingPos.y * 50 + ScreenPos.y ,15 };
}

//攻撃
void Class_player::attack() {
	attack_count -= delta_time;

	//アニメーションの更新
	if (attack_count < 0) {
		attack_count += attack_time;
		attack_animation++;
	}

	//アニメーションの終わり
	if (attack_animation >= 4) {
		attack_count = 0;
		attack_animation = 0;
		attack_button = false;
		//攻撃の当たり判定の無効化
		SlashingHit = false;
	}
}
//アニメーション
void Class_player::animation() {



}
//描画
void Class_player::draw() const {
	//プレイヤーの当たり判定アイテム用
	playerHit_Item.draw(ColorF{ 0 });
	//プレイヤーの当たり判定
	playerHit.draw(ColorF{ 1 });

	for (int i = afterimageMax-1; i >=0; i--) {
		//残像の描画
		if (Isafterimage[i])
			playerTexture_ZANGEKI1(0, 0, 1200, 1200).resized(100).drawAt(afterimageScreenPos[i],ColorF(1,0.5,0.5, afterimage_clear[i]));
	}
	//プレイヤーのテクスチャ
	playerTexture_ZANGEKI1(1200*animCount,0,1200,1200).resized(100).drawAt(playerHit.x, playerHit.y);
	//プレイヤーの攻撃マーカー
	player_attack_mark.draw(ColorF{ 1 });
	player_attack_mark_Texture.resized(50).rotated(angle_attack_mark).drawAt(player_attack_markPos);

	//攻撃アニメーション
	if(attack_button)ZANGEKI(1000* attack_animation,0,1000,1000).resized(200).rotated(attack_avoid).drawAt(attack_direction);

	//攻撃の当たり判定
	//if(SlashingHit)
	//for (int i = 0; i < 5; i++) Slashing[i].draw();
	

}

//獲得したアイテム数を加算
void Class_player::startBuff() {
	if (getItemCount != 0 && getItemCount % 5 == 0) {
		buffFlag = true;
	}
}
//アイテムの効果
void Class_player::itemBuff() {
	Print << U"アイテム獲得数" << getItemCount;
	Print << U"バフのフラグ" << buffFlag;
	if (buffFlag) {
		// 経過時間を加算
		t += Scene::DeltaTime();

		//効果
		playerHit_Item = { 400,300,50 };
		if (t > 5) {
			buffFlag = false;
			t = 0;
			playerHit_Item = { 400,300,playerSize };
		}
	}
}


//角度の計算
//底辺,高さ
double Class_player::angle_calculate(double base, double tall, bool isRadian) {

	//角度の計算
	double angle = Atan(tall / base) * (180 / 3.14);
	//補正
	if (base < 0) angle -= 90;
	else angle -= 270;

	if (isRadian) {
		//ラジアン化
		angle *= (3.14 / 180);

		return angle;
	}
	else return angle;
}
//特定のものを中心にして、そこからずらした角度からベクトルへの変換
//中心にする座標、ずらす角度
Vec2 Class_player::angle_vector_transformation(double base, double tall, double avoid) {


	double Angle = angle_calculate(base, tall, false);
	Angle -= 90+ avoid;

	if (Angle > 360)Angle -= 360;
	else if (Angle < 0)Angle += 360;

	double rad = Angle * Math::PiF / 180;

	double radY = sin(rad);
	double radX = cos(rad);
	return { radX,radY };
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
