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
	
	//Yで縮小、Uでフルサイズ
	if (KeyY.pressed())
	{
		
		Window::SetFullscreen(false);
		// ウィンドウを中心に移動
		Window::Centering();
	}
	if (KeyU.pressed())
	{
		Window::SetFullscreen(true);
	}

	

	if (KeyE.down())
	{
		changeScene(State::GameOver);
	}
	if (KeyC.down());

	//円形のカウントダウン
	angle -= countDown * Scene::DeltaTime();
	if (angle <= 0)
	{
		angle = 0;
	}


	//プレイヤーのボタン感知
	player->button();
	//プレイヤーの動き
	player->move();

	//敵の出現
	enemyCanon->appearance(player->playerPos(), player->getPlayerHit_Item(),
		                   player->IsAttack_during(), player->AttackHitPos());

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
			item[i]->MapPos(player->playerPos());
			//当たり判定
			item[i]->hitPlayerHit(player->getPlayerHit_Item());
		}
	}
	//アイテム
	player->itemBuff();


}

void Game::draw() const
{
	
	// 背景色を 黄緑 に設定
	Scene::SetBackground(ColorF{ 0, 1, 0 });

	Circle{ countDCircleX,countDCircleY,countDCircleSize + 1 }
	.drawPie(0_deg, -angle, ColorF{ 0, 0, 1 });

	Circle{ countDCircleX,countDCircleY,countDCircleSize }.drawFrame(0, countDCircleFrame);
		

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
			i = maxItemNum;
		}
	}
}
