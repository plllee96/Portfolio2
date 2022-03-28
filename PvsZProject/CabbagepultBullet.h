#pragma once
#include "Bullet.h"
class CabbagepultBullet : public Bullet {
private:
	float _speed;
	float _gravityY;

	float _startX;
public:
	HRESULT init(BulletType type, int x, int y, int line);
	void release(void);
	void update(void);
	void render(void);

	void collideObject(ObserveData obData);
	void recognizeObject(ObserveData observer);

	void setGravityY();
};

