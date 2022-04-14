#pragma once
#include "Plant.h"

enum class BloverStatus {WAIT, BLOW};
class Blover : public Plant {
private:
	BloverStatus _status;
	int _blowCount;
	bool _blow;
public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void updateFrame();
	bool isBlow() { return _blow; }
};

