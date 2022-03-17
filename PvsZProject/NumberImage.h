#pragma once
#include "GameNode.h"

class NumberImage : public GameNode {
private:
	Image* _numberImage;
	float* _x;
	float* _y;
public:
	HRESULT init(float* x, float* y);
	void release(void);
	void update(void);
	void render(void);
	void render(int num);
};

