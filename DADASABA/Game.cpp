﻿# include "Game.h"

Game::~Game() {
	if (player != nullptr)delete player;


	if (enemyCanon != nullptr)delete enemyCanon;

}

Game::Game(const InitData& init)
	: IScene{ init }
{
	player = new Class_player;
	enemyCanon = new Class_EnemyCanon;
}

void Game::update()
{
	ClearPrint();

	Print << U"カメラの座標" << MainCamera;
	for (const auto& monitor : monitors)
		Print << monitor.displayRect;
	deltatime = Scene::DeltaTime();

	//カメラターゲットがプレイヤーだった時
	if (CameraTarget == Player) {
		//ターゲット位置+描画したいスクリーン上の位置
		MainCamera = player->playerPos() - Vec2{ 400,300 };
	}
	else if (CameraTarget == fullScreen) {

		MainCamera = { -1537 / 2,-865 / 2 };

	}
	//カメラの自由移動(デバック用)
	else if (CameraTarget == freeCanon) {
		//カメラの移動
		if (KeyJ.pressed())MainCamera.x -= 100 * deltatime;
		if (KeyL.pressed())MainCamera.x += 100 * deltatime;
		if (KeyI.pressed())MainCamera.y -= 100 * deltatime;
		if (KeyK.pressed())MainCamera.y += 100 * deltatime;
	}

	//背景
	ScreenPos = BackMapPos - MainCamera;


	//Yで縮小、Uでフルサイズ
	if (KeyY.pressed())
	{
		
		Window::SetFullscreen(false);
		// ウィンドウを中心に移動
		Window::Centering();
		//カメラをプレイヤーに追従させる
		CameraTarget = Player;
	}
	if (KeyU.pressed())
	{
		Window::SetFullscreen(true);
		//カメラをフルスクリーンモードに
		CameraTarget = fullScreen;
	}

	

	if (enemyCanon->GetBossLive()==false)
	{
		changeScene(State::GameOver);
	}

	//円形のカウントダウン
	timer.CountDown();

	//プレイヤーのボタン感知
	player->button(deltatime);
	//プレイヤーの動き
	player->move();
	//カメラ取得
	player->SetMainCamera(MainCamera);
	//アニメーション
	player->animation();
	//敵の出現
	enemyCanon->appearance(player->playerPos(), player->getPlayerHit(),
		                   player->IsAttack_during(), player->AttackHitPos(),
		                   MainCamera, deltatime, player->getPlayerHit_Item());
	//タイマーの取得
	enemyCanon->SetAngleTimer(timer.GetTimerCount());
	Print << timer.GetTimerCount();
	//プレイヤーのエイム
	player->attack_aim();

	//アイテム
	player->setItemCount(enemyCanon->addCountGet());
	player->startBuff();
	player->itemBuff();

}

void Game::draw() const
{
	
	// 背景色を 黄緑 に設定
	Scene::SetBackground(ColorF{ 0, 1, 0 });

	//背景
	Back_ground.resized(1537).drawAt(ScreenPos);

	//円形のカウントダウン
	timer.draw();
		

	player->draw();
	
	//敵の描画
	enemyCanon->Draw();

}
