#pragma once
#include "Plant.h"
class CherryBomb : public Plant {
private:

public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual BulletObserveData getFireUpdate();
	virtual void fireObject(BulletObserveData observer);

	void updateFrame();
};

