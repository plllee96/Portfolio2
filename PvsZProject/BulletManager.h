#pragma once
#include "GameNode.h"
#include "Bullet.h"

#pragma region BulletType
#include "PeashooterBullet.h"
#include "CherryExplode.h"
#include "PotatoExplode.h"
#include "MushroomBullet.h"
#include "FumeshroomBullet.h"
#include "JalapenoExplode.h"
#include "ThreepeaterBullet.h"
#include "CabbagepultBullet.h"

#include "InvisibleRect.h"
#pragma endregion

class BulletManager : public GameNode, public BulletObserver {
private:
	typedef vector<Bullet*> vBullet;
	typedef vector<Bullet*>::iterator viBullet;

	vBullet _vBullet;
	viBullet _viBullet;

	BulletObservedType _bulletObType;

	int _stageNum;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addBullet(BulletType type, int x, int y, int line);
	void addBullet(BulletType type, int x, int y, int line, RECT rc);
	void removeBullet(viBullet iter);

	virtual BulletObserveData getFireUpdate();
	virtual void fireObject(BulletObserveData observer);
	virtual void fireObject(BulletObserveData observer, RECT rc);

	void setStage(int num) { _stageNum = num; }

};

