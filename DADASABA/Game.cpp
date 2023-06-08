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
	if (KeyEnter.down() || MouseL.down()//||60秒経ったら
		)
	{
		//名前登録ではなくCommon.h内にあるので注意
		changeScene(State::Bos);
	}
}

void Game::draw() const
{
	//確認用
	FontAsset(U"TitleFont")(U"Game Scene").drawAt(400, 200);
	FontAsset(U"TitleFont")(U"Crick or Enter Next").drawAt(400, 300);
	FontAsset(U"TitleFont")(U"60秒後にシーン移動").drawAt(400, 400);
}

