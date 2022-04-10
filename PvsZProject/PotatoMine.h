#pragma once
#include "Plant.h"
const float _potatoReadyTime = 15.0f;

enum class PotatoStatus {LOAD, READY, WAIT};
class PotatoMine : public Plant {
private:
	PotatoStatus _status;
	float _readyCount;

public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void recognizeObject(ObserveData observer);

	void setFrame();
	void updateFrame();
};

