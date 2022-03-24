#pragma once
#include "Plant.h"
enum class SunshroomStatus { WAIT, GENERATE };

class Sunshroom: public Plant {
	SunshroomStatus _status;

	float _generateCooltime;
	float _generateCount;
	bool _generate;

	float _growTime;
	float _growCount;
	bool _grow;

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
	bool isGrow() { return _grow; }
	void setGenerate(bool generate) { _generate = generate; }

};

