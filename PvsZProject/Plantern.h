#pragma once
#include "Plant.h"

class Plantern : public Plant {
private:
	bool _alreadySetLight;
public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void act();

	void updateFrame();

	bool isAlreadySetLight() { return _alreadySetLight; }
	void setLight(bool light) { _alreadySetLight = light; }
};

