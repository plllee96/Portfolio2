#pragma once
#include "GameNode.h"
#include "ZombieType.h"
#include "Tile.h"

const int fixY = 30;
struct ZombieFrame {
	int maxFrameX;
	int currentFrameX;
	int currentFrameY;
	float count;
	float coolTime;
};
class Zombie : public GameNode, public Observer {
protected:
	Image* _image;
	ZombieType _type;

	int _line;
	float _x;
	RECT _rc;
	RECT _recognizeRc;

	ZombieFrame _frame;

	float _hp;
	float _damage;
	bool _active;
	bool _attack;

	bool _armFall;
	bool _armAlreadyFall;
	bool _headFall;
	bool _headAlreadyFall;
	bool _objectFall;
	bool _objectAlreadyFall;

	int _tileHeight;

	//Observer Variable
	ObservedType _obType;

public:
	virtual HRESULT init(ZombieType type, int line);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	ObserveData getRectUpdate();
	virtual void collideObject(ObserveData obData);
	virtual void recognizeObject(ObserveData observer);

	virtual void act();

	virtual int getLine() { return _line; }
	virtual bool isActive() { return _active; }
	virtual bool isArmFall() { return _armFall; }
	virtual void setArmFall(bool fall) { _armFall = fall; }
	virtual bool isHeadFall() { return _headFall; }
	virtual void setHeadFall(bool fall) { _headFall = fall; }
	virtual bool isObjectFall() { return _objectFall; }
	virtual void setObjectFall(bool fall) { _objectFall = fall; }

	ZombieType getType() { return _type; }

	int getX() { return _x; }
	void setX(int x) { _x = x; }
	int getY() { return  _line * _tileHeight; }

	void setTileHeight(int tileHeight) { _tileHeight = tileHeight; }
};

