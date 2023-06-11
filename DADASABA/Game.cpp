# include "Game.h"

Game::~Game() {
	if (player != nullptr) {
		delete player;
	}
	if (enemy != nullptr) {
		delete enemy;
	}
}

Game::Game(const InitData& init)
	: IScene{ init }
{
	player = new Class_player();
	enemy = new Class_Enemy();
}

void Game::update()
{
	ClearPrint();

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
	enemy->Target_input(player->playerPos());
	//敵の動き
	enemy->Move();
	//プレイヤーのエイム
	player->attack_aim();

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
	player->draw();
	enemy->Draw();
	//確認用
	FontAsset(U"TitleFont")(U"Game Scene").drawAt(400, 200);
	FontAsset(U"TitleFont")(U"Crick or Enter Next").drawAt(400, 300);
	FontAsset(U"TitleFont")(U"GameOver→[E]:GameClear→[C]").drawAt(400, 500);
	if (CountDown <= 0)
	{
		FontAsset(U"TitleFont")(U"ボス戦中").drawAt(400, 400);
	}
	else
	{
		FontAsset(U"TitleFont")(downPrint, U"秒後にボス戦移動").drawAt(400, 400);
	}
}

