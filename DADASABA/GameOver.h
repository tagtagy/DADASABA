#pragma once
#include"Common.h"
class GameOver :public App::Scene
{
public:
	GameOver(const InitData& init);

	void update()override;

	void draw()const override;

private:
};

