#pragma once
#include"Plant.h"
class ExplodeBowling : public Plant {
private:
	float _bowlingX;
public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void recognizeObject(ObserveData observer);

	void updateFrame();
};

