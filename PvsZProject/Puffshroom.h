#pragma once
#include "Plant.h"

enum class PuffshroomStatus {WAIT, SHOT};
class Puffshroom : public Plant {
private:
	PuffshroomStatus _status;

	float _shotCount;
	float _shotCooltime;
	bool _alreadyShot;

public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void act();
	void fire(bool fire);

	virtual void recognizeObject(ObserveData observer);

	virtual BulletObserveData getFireUpdate();
	virtual void fireObject(BulletObserveData observer);

	void setFrame();
	void updateFrame();
};

