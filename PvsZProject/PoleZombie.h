#pragma once
#include "Zombie.h"

enum class PoleZombieStatus {
	WAIT, RUN, WALK, JUMP, ATTACK, DEAD
};

class PoleZombie : public Zombie {
private:
	PoleZombieStatus _status;
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

