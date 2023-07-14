#pragma once
class Class_Timer
{
public:

	void CountDown();

	void draw() const;

private:
	//円形のカウントダウン
	double angle = 360_deg;
	double countDCircleX = 100;
	double countDCircleY = 100;
	double countDCircleSize = 100;
	double countDCircleFrame = 3;
	double countDown = 0.105;
};

