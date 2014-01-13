#pragma once
class inputActions
{
public:
	inputActions(void);

	void mouseClick(unsigned, unsigned);
	void leftClick();
	void rightClick();
	void simulateKeys(int);
	float getCurrentVolume(double,bool);
	bool changeVolume(double, bool);
	~inputActions(void);
};

