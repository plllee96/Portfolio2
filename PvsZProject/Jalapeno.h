#pragma once
#include "Plant.h"

class Jalapeno : public Plant {
private:

public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void updateFrame();
};

