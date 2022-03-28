#pragma once
#include "Bullet.h"

class ThreepeaterBullet : public Bullet{
private:
	float _speed;

	int _moveY;
public:
	HRESULT init(BulletType type, int x, int y, int line);
	void release(void);
	void update(void);
	void render(void);

	void collideObject(ObserveData obData);
	void recognizeObject(ObserveData observer);

};

