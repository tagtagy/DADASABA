# pragma once
# include "Common.h"

// ランキングシーン
class Ranking : public App::Scene
{
public:

	Ranking(const InitData& init);

	void update() override;

	void draw() const override;

private:

};
