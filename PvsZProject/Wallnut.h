#pragma once
#include "Plant.h"

class Wallnut : public Plant {
public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void act();

	void setFrame();
	void updateFrame();
};

