#pragma once
#include "Plant.h"
class WallnutBowling : public Plant {
private:
	float _bowlingX;
	float _bowlingY;
	int _moveTo;
	int _historyLine;

	float _bowlingCount;
	float _bowlingCooltime;

public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void recognizeObject(ObserveData observer);

	void updateFrame();
};

