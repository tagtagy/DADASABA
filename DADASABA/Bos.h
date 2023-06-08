#pragma once
#include"Common.h"

class Bos:public App::Scene
{
public:

	Bos(const InitData& init);

	void update() override;

	void draw() const override;

private:
};

