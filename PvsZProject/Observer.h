#pragma once
#include "Stdafx.h"
#include "BulletType.h"
#include "PlantType.h"

//=====================================
//	## Rect Collide Observer ##
//=====================================

enum class ObservedType {
	PLANT, ZOMBIE, BULLET, MOWER
};
enum class DamageType {NONE, EXPLODE, EXTINCT};

typedef struct tagObservedInfo {
	ObservedType* type;
	DamageType* damageType;
	PlantType* plantType;
	RECT* rc;
	RECT* recognizeRc;
	float* damage;
	int* line;
	bool* hitActive;

	tagObservedInfo() {
		type = nullptr;
		damageType = nullptr;
		plantType = nullptr;
		rc = nullptr;
		recognizeRc = nullptr;
		damage = nullptr;
		line = nullptr;
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

//=====================================
//	## Bullet Observer ##
//=====================================

enum class BulletObservedType {OBJECT, BULLETMANAGER};
typedef struct tagBulletObserverInfo {
	BulletObservedType* type;
	BulletType* bulletType;
	PlantType* plantType;
	bool* fire;
	int* line;
	int* x;
	int* y;
} BulletObserveData;

class BulletObserver {
public:
	virtual BulletObserveData getFireUpdate() = 0;
	virtual void fireObject(BulletObserveData observer) = 0;
	virtual void fireObject(BulletObserveData observer, RECT rc) = 0;
};