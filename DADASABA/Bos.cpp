#include "Bos.h"

Bos::Bos(const InitData& init)
	:IScene{ init } {}

void Bos::update()
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

	//PlayerHP=0→GameOver
	//BosEnemyHP=0→ResulutRanking
}

void Bos::draw()const
{
	//確認用
	FontAsset(U"TitleFont")(U"Bos Scene").drawAt(400, 200);
	FontAsset(U"TitleFont")(U"GameOver→[E]").drawAt(400, 300);
	FontAsset(U"TitleFont")(U"GameClear→[C]").drawAt(400, 400);
}
