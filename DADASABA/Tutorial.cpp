#include "Tutorial.h"

Tutorial::Tutorial(const InitData&init)
	:IScene{init}{}

void Tutorial::update()
{
	if (KeyEnter.down() || MouseL.down())
	{
		//名前登録ではなくCommon.h内にあるので注意
		changeScene(State::Game);
	}
}

void Tutorial::draw()const
{
	//確認用
	FontAsset(U"TitleFont")(U"Tutorial Scene").drawAt(400, 200);
	FontAsset(U"TitleFont")(U"Crick or Enter Next").drawAt(400, 300);
}
