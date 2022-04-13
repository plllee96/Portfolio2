#pragma once
#include "Bullet.h"

class PeashooterBullet : public Bullet {
private:
	Image* _fireImage;
	bool _isFire;
	float _speed;
public:
	HRESULT init(BulletType type, int x, int y, int line);
	void release(void);
	void update(void);
	void render(void);

	void collideObject(ObserveData obData);
	void recognizeObject(ObserveData observer);

};

