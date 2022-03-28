#pragma once
#include "Plant.h"

enum class ScaredyshroomStatus { WAIT, SHOT, SCARED };

class Scaredyshroom : public Plant {
private:
	ScaredyshroomStatus _status;

	RECT _scaredRect;

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

	void setFrame();
	void updateFrame();
};

