#pragma once
#include "GameNode.h"

class Reward : public GameNode {
private:
	Image* _image;
	int _rewardNum;
	float _x;
	float _y;
	RECT _rc;

public:
	HRESULT init(int stageNum);
	void release();
	void update();
	void render();


};

