#include "stdafx.h"
#include "Class_Timer.h"

void Class_Timer::CountDown() {
	//円形のカウントダウン
	angle -= countDown * Scene::DeltaTime();
	if (angle <= 0)
	{
		angle = 0;
	}
}

void Class_Timer::draw() const {
	Circle{ countDCircleX,countDCircleY,countDCircleSize + 1 }
	.drawPie(0_deg, -angle, ColorF{ 0, 0, 1 });

	Circle{ countDCircleX,countDCircleY,countDCircleSize }.drawFrame(0, countDCircleFrame);
}
