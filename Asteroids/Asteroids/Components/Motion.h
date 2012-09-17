#pragma once
class Motion
{
public:
	Motion(void);
	~Motion(void);

private:
	float speedX;
	float speedY;
	float damping;
};

