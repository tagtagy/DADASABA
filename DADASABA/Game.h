# pragma once
# include "Common.h"
#include "Class_player.h"

// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	~Game();

	void update() override;

	void draw() const override;

private:
	Class_player* player = nullptr;
	
};
