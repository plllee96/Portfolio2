#pragma once
#include "Zombie.h"

enum class BucketheadZombieStatus {
	WAIT, WALK, ATTACK
};

class BucketheadZombie : public Zombie {
private:
	BucketheadZombieStatus _status;
public:
	virtual HRESULT init(ZombieType type, int line);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void act();
	void attack();

	virtual void collideObject(ObserveData obData);
	virtual void recognizeObject(ObserveData observer);

	void setFrame();
	void updateFrame();
};

