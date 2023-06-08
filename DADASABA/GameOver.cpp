#include "GameOver.h"

GameOver::GameOver(const InitData& init)
	: IScene{ init }
{

}

void GameOver::update()
{
	if (KeyEnter.down() || MouseL.down())
	{
		//名前登録ではなくCommon.h内にあるので注意
		changeScene(State::Title);
	}
}

void GameOver::draw() const
{
	//確認用
	FontAsset(U"TitleFont")(U"GameOver Scene").drawAt(400, 200);
	FontAsset(U"TitleFont")(U"Crick or Enter → Title").drawAt(400, 300);
}
