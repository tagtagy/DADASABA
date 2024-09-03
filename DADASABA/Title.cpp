# include "Title.h"

Title::Title(const InitData& init)
	: IScene{ init } {


}

void Title::update() 
{
	if (KeyEnter.down() || MouseL.down())
	{
		//名前登録ではなくCommon.h内にあるので注意
		changeScene(State::Game);
	}
}

void Title::draw() const
{
	playerTexture.drawAt(100, 200);

	//確認用
	FontAsset(U"TitleFont")(U"DADADASABA").drawAt(250, 200);
	FontAsset(U"Menu")(U"Crick or Enter Start").drawAt(250, 450, { 1,1,1 });
}
