#pragma once
#include "GameNode.h"

enum class SunType { FALL, GENERATE, GAIN };
const float sunCooltime = 10.0f;
const float sunFrameDelay = 0.5f;
const float uiX = 75;
const float uiY = 20;

class Sun : public GameNode {
private:
	Image* _image;
	Image* _smallImage;
	SunType _type;
	bool _small;
	float _x;
	float _y;
	float _targetY;
	float _gravity;
	float _xspeed;
	float _timer;
	RECT _rc;

	int _frame;
	float _frameTimer;
public:
	HRESULT init(SunType type);
	HRESULT init(SunType type, float x, float y);
	void release(void);
	void update(void);
	void render(void);

	void updateFrame();
	
	RECT getRect() { return _rc; }
	void setType(SunType type) { _type = type; }
	void setSmall() { _small = true; }
	bool isSmall() { return _small; }
	bool isOverTime();
	bool isCompleteObtained();


	Sun() {}
	~Sun() {}
};

