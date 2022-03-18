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
	bool* specialBullet;

	tagObservedInfo() {
		type = nullptr;
		rc = nullptr;
		damage = nullptr;
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