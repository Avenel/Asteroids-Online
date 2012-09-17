#pragma once
class MotionControl
{
public:
	MotionControl(void);
	~MotionControl(void);

private:
	int left;
	int right;
	int accelerate;
	int accelerationRate;
	int	rotationRate;
};

