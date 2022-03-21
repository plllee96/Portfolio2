#pragma once
#include "GameNode.h"
#include "BulletType.h"

class Bullet : public GameNode, public Observer {
protected:
	Image* _image;
	BulletType _type;
	DamageType _damageType;
	int _x;
	int _y;
	RECT _rc;
	RECT _recognizeRc;
	float _damage;
	bool _hitActive;
	bool _active;

	ObservedType _obType;

public:
	virtual HRESULT init(BulletType type, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual ObserveData getRectUpdate();
	virtual void collideObject(ObserveData obData);
	virtual void recognizeObject(ObserveData observer);

	BulletType getType() { return _type; }
	bool isActive() { return _active; }
};

