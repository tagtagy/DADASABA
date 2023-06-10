﻿# include "Game.h"

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

	player->button();
	player->move();
	player->attack_aim();

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
	/*//確認用
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
	}*/
}

