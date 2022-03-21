#pragma once
#include "Zombie.h"

enum class NormalZombieStatus {
	WAIT, WALK, ATTACK, DEAD, EXPLODE
};

class NormalZombie : public Zombie {
private:
	NormalZombieStatus _status;
public:
	virtual HRESULT init(ZombieType type, int line);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void act();

	virtual ObserveData getRectUpdate();
	virtual void collideObject(ObserveData obData);
	virtual void recognizeObject(ObserveData observer);

	void setFrame();
	void updateFrame();
};

