#pragma once
#include "Bullet.h"

class InvisibleRect : public Bullet {
private:
	float _availableTime;
public:
	HRESULT init(BulletType type, int x, int y, int line);
	void release(void);
	void update(void);
	void render(void);

	void collideObject(ObserveData obData);
	void recognizeObject(ObserveData observer);
};

