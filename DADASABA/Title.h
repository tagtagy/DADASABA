# pragma once
# include "Common.h"

// タイトルシーン
class Title : public App::Scene
{
public:

	Title(const InitData& init);

	void update() override;

	void draw() const override;

private:

	const Texture playerTexture{ U"SOZAI/player/Player_pokomaru_Ver2.png" };
};
