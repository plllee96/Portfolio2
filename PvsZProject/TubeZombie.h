#pragma once
#include "Zombie.h"

enum class TubeZombieStatus {
	WALK, SWIM, DEAD
};

class TubeZombie : public Zombie {
private:
	TubeZombieStatus _status;
	float _speed;
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

