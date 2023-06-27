# include "Game.h"

Game::~Game() {
	if (player != nullptr) {
		delete player;
	}
	if (enemy != nullptr) {
		delete enemy;
	}
	for (int i = 0; i < maxItemNum; i++) {
		if (item[i] != nullptr) {
			delete item[i];
		}
	}
}

Game::Game(const InitData& init)
	: IScene{ init }
{
	player = new Class_player();
	enemy = new Class_Enemy();
	SpawnItem({ 0,0 });
}

void Game::update()
{
	ClearPrint();
	//Yで縮小、Uでフルサイズ
	if (KeyY.pressed())
	{
		Window::SetFullscreen(false);
	}
	if (KeyU.pressed())
	{
		Window::SetFullscreen(true);
	}

	//カウントダウン
	CountDown -= Scene::DeltaTime();
	downPrint = floor(CountDown);
	if (CountDown <= 0)
	{
		CountDown = 0;
	}

	if (KeyE.down())
	{
		changeScene(State::GameOver);
	}
	if (KeyC.down());
	//プレイヤーのボタン感知
	player->button();
	//プレイヤーの動き
	player->move();

	//敵のターゲットの座標取得
	enemy->Target_input(player->playerPos(), player->getPlayerHit_Item());
	//敵の動き
	enemy->Move();
	//プレイヤーのエイム
	player->attack_aim();
	//敵がプレイヤーの斬撃に当たった時
	enemy->Knockback(player->IsAttack_during(), player->AttackHitPos());

	//デバッグ用
	if (KeyI.down()) {
		int rX = Random(-1000, 1000);
		int rY = Random(-1000, 1000);
		//マップ上の座標に出るように変更しました
		SpawnItem({ rX,rY });
	}

	//全ての要素にアクセス
	for (int i = 0; i < maxItemNum; i++) {
		if (item[i] != nullptr) {
			//描画一の更新
			item[i]->MapPos(player->playerPos());
			//当たり判定
			item[i]->hitPlayerHit(player->getPlayerHit_Item());
			if (item[i]->getIsDestroy()) {//当たっていたら要素をnullにする
				//獲得アイテム数を加算
				player->addItemCount();
				item[i] = nullptr;
			}
		}
	}
	//アイテム
	player->itemBuff();

	//敵の動き


	/*if (KeyEnter.down() || MouseL.down()//||60秒経ったら
		)
	{
		//名前登録ではなくCommon.h内にあるので注意
		changeScene(State::ResultRanking);
	}*/
}

void Game::draw() const
{
	// 背景色を 黄緑 に設定
	Scene::SetBackground(ColorF{ 0, 1, 0 });


	player->draw();
	enemy->Draw();
	for (int i = 0; i < maxItemNum; i++) {
		if (item[i] != nullptr) {
			item[i]->draw();
		}
	}
	//確認用
	//FontAsset(U"TitleFont")(U"Game Scene").drawAt(400, 200);
	//FontAsset(U"TitleFont")(U"Crick or Enter Next").drawAt(400, 300);
	//FontAsset(U"TitleFont")(U"GameOver→[E]:GameClear→[C]").drawAt(400, 500);
	if (CountDown <= 0)
	{
		//FontAsset(U"TitleFont")(U"ボス戦中").drawAt(400, 400);
	}
	else
	{
		//FontAsset(U"TitleFont")(downPrint, U"秒後にボス戦移動").drawAt(400, 400);
	}
}

void Game::SpawnItem(Vec2 _enemyPos) {
	for (int i = 0; i < maxItemNum; i++) {
		if (item[i] == nullptr) {
			item[i] = new Class_Item();
			//初期位置を設定（playerの位置を足して調整）
			item[i]->init(_enemyPos);
			break;
		}
	}
}
