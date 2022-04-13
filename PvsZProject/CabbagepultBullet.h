#pragma once
#include "Bullet.h"

const float highestY = 50.0f;
class CabbagepultBullet : public Bullet {
private:
	float _speed;
	float _gravityY;

	float _distance;
	float _halfPoint;
	float _startX;
public:
	HRESULT init(BulletType type, int x, int y, int line);
	void release(void);
	void update(void);
	void render(void);

	void collideObject(ObserveData obData);
	void recognizeObject(ObserveData observer);

	void setDistance();
	void setGravityY();
};

