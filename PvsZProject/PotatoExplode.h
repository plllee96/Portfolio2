#pragma once
#include "Bullet.h"

class PotatoExplode : public Bullet {
private:
	float _initTime;
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
};

