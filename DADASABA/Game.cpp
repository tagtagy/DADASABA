# include "Game.h"

Game::~Game() {
	if (player != nullptr) {
		delete player;
	}
}

Game::Game(const InitData& init)
	: IScene{ init }
{
	player = new Class_player();
}

void Game::update()
{
	if (KeyE.down())
	{
		changeScene(State::GameOver);
	}
	if (KeyC.down())
	{
		//名前登録ではなくCommon.h内にあるので注意
		changeScene(State::ResultRanking);
	}
}

void Game::draw() const
{
	//確認用
	FontAsset(U"TitleFont")(U"Game Scene").drawAt(400, 200);
	FontAsset(U"TitleFont")(U"Crick or Enter Next").drawAt(400, 300);
	FontAsset(U"TitleFont")(U"60秒後にボス戦移動").drawAt(400, 400);
	FontAsset(U"TitleFont")(U"GameOver→[E]").drawAt(400, 300);
	FontAsset(U"TitleFont")(U"GameClear→[C]").drawAt(400, 400);
}

