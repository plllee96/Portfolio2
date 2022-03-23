#pragma once
#include "Plant.h"

enum class ChomperStatus { WAIT, ATTACK, EAT };
class Chomper : public Plant {
private:
	ChomperStatus _status;
	float _attackCount;
	float _attackCoolTime;
	bool _alreadyAttack;

public:
	HRESULT init(PlantType type, POINT location);
	void release(void);
	void update(void);
	void render(void);

	void recognizeObject(ObserveData observer);

	BulletObserveData getFireUpdate();
	void fireObject(BulletObserveData observer);

	void setFrame();
	void updateFrame();
};

