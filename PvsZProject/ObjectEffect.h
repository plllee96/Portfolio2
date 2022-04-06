#pragma once
#include "GameNode.h"

const float maintainTime = 2.0f;

class ObjectEffect : public GameNode {
private:
	Image* _image;
	float _x, _y;
	float _xspeed;
	float _targetY;
	float _gravity;
	float _timer;

	bool _isActive;
public:
	HRESULT init(void);
	virtual HRESULT init(const char* imageName, int x, int y);
	void release(void);
	void update(void);
	void render(void);

	bool getIsActive(void) { return _isActive; }
};

