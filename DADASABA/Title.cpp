# include "Title.h"

Title::Title(const InitData& init)
	: IScene{ init } {}

void Title::update() 
{
	if (KeyEnter.down() || MouseL.down())
	{
		//名前登録ではなくCommon.h内にあるので注意
		changeScene(State::Tutorial);
	}
}

void Title::draw() const
{
	playerTexture.drawAt(100, 200);

	//確認用
	FontAsset(U"TitleFont")(U"Title Scene").drawAt(400, 200);
	FontAsset(U"TitleFont")(U"Crick or Enter Start").drawAt(400, 300);
}
