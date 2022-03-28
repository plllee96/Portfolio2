#pragma once
#include "Observer.h"
#include "SingletonBase.h"

class Plant;
class Zombie;

class ObserverManager : public SingletonBase<ObserverManager> {
private:
	typedef  vector<Observer*> vObserver;
	typedef  vector<Observer*>::iterator viObserver;

	typedef vector<BulletObserver*> vBulletObserver;
	typedef vector<BulletObserver*>::iterator viBulletObserver;

private:
	vObserver _vObserver;
	viObserver _viObserver;
	viObserver _viObserverCompare;

	vBulletObserver _vBulletObserver;
	viBulletObserver _viBulletObserver;
	viBulletObserver _viBulletObserverCompare;

	RECT _tempRC;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void registerObserver(Observer* observer);
	virtual void removeObserver(Observer* observer);

	virtual void registerBulletObserver(BulletObserver* observer);
	virtual void removeBulletObserver(BulletObserver* observer);

	virtual void manageRect();
	virtual void manageBullet();

	ObserverManager() {}
	~ObserverManager() {}
};

