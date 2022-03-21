#pragma once
#include "Plant.h"

enum class PeashooterStatus {WAIT, SHOT};
class Peashooter : public Plant {
private:
	PeashooterStatus _status;

	float _shotCount;
	float _shotCooltime;
	bool _alreadyShot;

public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void act();
	void fire();

	virtual ObserveData getRectUpdate();
	virtual void collideObject(ObserveData obData);
	virtual void recognizeObject(ObserveData observer);
	
	void setFrame();
	void updateFrame();
};

