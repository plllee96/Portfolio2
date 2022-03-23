#pragma once
#include "GameNode.h"
#include "BulletType.h"

class Bullet : public GameNode, public Observer {
protected:
	Image* _image;
	BulletType _type;
	DamageType _damageType;
	int _line;
	int _x;
	int _y;
	RECT _rc;
	RECT _recognizeRc;
	float _damage;
	bool _hitActive;			//true : damage Zombie, false : ignore
	bool _active;			//false : remove Bullet

	ObservedType _obType;

public:
	virtual HRESULT init(BulletType type, int x, int y, int line);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	ObserveData getRectUpdate();
	virtual void collideObject(ObserveData obData);
	virtual void recognizeObject(ObserveData observer);

	BulletType getType() { return _type; }
	bool isActive() { return _active; }
};

