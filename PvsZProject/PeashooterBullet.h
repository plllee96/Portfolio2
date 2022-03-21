#pragma once
#include "Bullet.h"
class PeashooterBullet : public Bullet {
private:
	float _speed;
public:
	HRESULT init(BulletType type, int x, int y);
	void release(void);
	void update(void);
	void render(void);

	ObserveData getRectUpdate();
	void collideObject(ObserveData obData);
	void recognizeObject(ObserveData observer);

};

