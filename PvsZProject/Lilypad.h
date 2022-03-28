#pragma once
#include "Plant.h"

class Lilypad : public Plant {
public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

};

