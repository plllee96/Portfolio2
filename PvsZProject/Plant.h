#pragma once
#include "GameNode.h"
#include "PlantType.h"
#include "Tile.h"
#include "Observer.h"
#include "BulletType.h"

struct PlantFrame {
	int maxFrameX;
	int currentFrameX;
	int currentFrameY;
	float count;
	float coolTime;
};

class Plant : public GameNode, public Observer, public BulletObserver {
protected:
	//Plants Variable
	Image* _image;
	PlantType _type;
	POINT _location;
	int _line;
	RECT _rc;
	RECT _recognizeRc;
	PlantFrame _frame;
	float _hp;
	bool _active;
	bool _hitActive;

	//Bullet fire Variable
	BulletType _bulletType;
	bool _fire;
	int _fireX;
	int _fireY;

	//Observer Variable
	ObservedType _obType;
	BulletObservedType _bulletObType;

	//fix Position
	int fixFireX;
	int fixFireY;

	int _tileHeight;
public:
	virtual HRESULT init(PlantType type, POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	ObserveData getRectUpdate();
	virtual void collideObject(ObserveData obData);
	virtual void recognizeObject(ObserveData observer);

	BulletObserveData getFireUpdate();
	virtual void fireObject(BulletObserveData observer);
	virtual void fireObject(BulletObserveData observer, RECT rc);

	virtual void act();
	
	POINT getLocation() { return _location; }
	int getLine() { return _line; }
	PlantType getType() { return _type; }
	virtual RECT getRect() { return _rc; }
	virtual RECT getRecognizeRect() { return _recognizeRc; }
	bool isActive() { return _active; }
	void setTileHeight(int tileHeight) { _tileHeight = tileHeight; }
};

