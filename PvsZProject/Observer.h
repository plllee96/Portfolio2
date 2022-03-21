#pragma once
#include "Stdafx.h"

enum class ObservedType {
	PLANT, ZOMBIE, BULLET
};
enum class DamageType {NONE, EXPLODE, EXTINCT};

typedef struct tagObservedInfo {
	ObservedType* type;
	DamageType* damageType;
	RECT* rc;
	RECT* recognizeRc;
	float* damage;
	bool* hitActive;

	tagObservedInfo() {
		type = nullptr;
		damageType = nullptr;
		rc = nullptr;
		recognizeRc = nullptr;
		damage = nullptr;
		hitActive = nullptr;
	}
} ObserveData; 

class Observer {
public:
	virtual ObserveData getRectUpdate() = 0;
	virtual void collideObject(ObserveData observer) = 0;
	virtual void recognizeObject(ObserveData observer) = 0;

	Observer() {}
	virtual ~Observer() {}
};