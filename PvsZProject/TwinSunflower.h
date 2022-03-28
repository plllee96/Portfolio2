#pragma once
#include "Plant.h"

enum class TwinSunflowerStatus { WAIT, GENERATE };

class TwinSunflower : public Plant {
private:
	TwinSunflowerStatus _status;

	float _generateCooltime;
	float _generateCount;
	bool _generate;
public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void act();

	void setFrame();
	void updateFrame();
	RECT getRect();

	bool isGenerate() { return _generate; }
	void setGenerate(bool generate) { _generate = generate; }

};

