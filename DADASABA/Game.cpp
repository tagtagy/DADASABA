# include "Game.h"

Game::~Game() {
	if (player != nullptr)delete player;


	if (enemyCanon != nullptr)delete enemyCanon;

	for (int i = 0; i < maxItemNum; i++) {
		if (item[i] != nullptr) delete item[i];
	}
}

Game::Game(const InitData& init)
	: IScene{ init }
{
	
	for (int i = 0; i < maxItemNum; i++) {
		item[i] = new Class_Item();

	}
	player = new Class_player;
	enemyCanon = new Class_EnemyCanon;
	SpawnItem({ 0,0 });
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
	player->SetMainCamera(MainCamera);

	


	//敵の出現
	enemyCanon->appearance(player->playerPos(), player->getPlayerHit(),
		                   player->IsAttack_during(), player->AttackHitPos(),
		                   MainCamera, deltatime);
	//タイマーの取得
	enemyCanon->SetAngleTimer(timer.GetTimerCount());
	Print << timer.GetTimerCount();
	//プレイヤーのエイム
	player->attack_aim();

	//デバッグ用
	if (KeyI.down()) {
		int rX = Random(-1000, 1000);
		int rY = Random(-1000, 1000);
		//マップ上の座標に出るように変更しました
		SpawnItem({ rX,rY });
	}

	//全ての要素にアクセス
	for (int i = 0; i < maxItemNum; i++) {
		//有効な時
		if (item[i]->getIsValid()) {
			//描画位置の更新
			item[i]->MapPos(player->playerPos(), player->getPlayerHit_Item(), MainCamera);
			//当たり判定
			item[i]->hitPlayerHit(player->getPlayerHit_Item());
			if (item[i]->getIsDestroy()) {
				player->addItemCount();
				item[i]->setIsValid(false);
			}
		}
	}

	//アイテム
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
	
	for (int i = 0; i < maxItemNum; i++) {
		if (item[i]->getIsValid()) {
			item[i]->draw();
		}
	}
	//敵の描画
	enemyCanon->Draw();

	
	
}

void Game::SpawnItem(Vec2 _enemyPos) {
	for (int i = 0; i < maxItemNum; i++) {
		if (!item[i]->getIsValid()) {
			//初期位置を設定（playerの位置を足して調整）
			item[i]->init(_enemyPos);
			item[i]->setIsValid(true);
			i = maxItemNum;
		}
	}
}
