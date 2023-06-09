﻿# include "Ranking.h"

Ranking::Ranking(const InitData& init)
	: IScene{ init }
{
	
}

void Ranking::update()
{
	if (KeyEnter.down() || MouseL.down())
	{
		//名前登録ではなくCommon.h内にあるので注意
		changeScene(State::Title);
	}
}

void Ranking::draw() const
{
	//確認用
	FontAsset(U"TitleFont")(U"Result&Ranking Scene").drawAt(400, 200);
	FontAsset(U"TitleFont")(U"Crick or Enter → Title").drawAt(400, 300);

	//図鑑的なのを追加するのか否か…
}
