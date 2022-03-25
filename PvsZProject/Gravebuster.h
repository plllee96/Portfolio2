#pragma once
#include "Plant.h"

class Gravebuster : public Plant {
private:
	RECT _startRc;
	float _moveY;
public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void updateFrame();
};

