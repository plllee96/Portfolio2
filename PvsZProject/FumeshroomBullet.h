#pragma once
#include "Bullet.h"
class FumeshroomBullet : public Bullet {
private:
	float _count;
	float _coolTime;
	int _frame;
public:
	HRESULT init(BulletType type, int x, int y, int line);
	void release(void);
	void update(void);
	void render(void);

	void collideObject(ObserveData obData);
	void recognizeObject(ObserveData observer);

	void updateFrame();
};

