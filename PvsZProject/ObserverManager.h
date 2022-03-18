#pragma once
#include "Observer.h"
#include "SingletonBase.h"

class Plant;
class Zombie;

class ObserverManager : public SingletonBase<ObserverManager> {
private:
	typedef  vector<Observer*> vObserver;
	typedef  vector<Observer*>::iterator viObserver;

private:
	vObserver _vObserver;
	viObserver _viObserver;
	viObserver _viObserverCompare;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void registerObserver(Observer* observer);
	virtual void removeObserver(Observer* observer);

	virtual void manageRect();

	ObserverManager() {}
	~ObserverManager() {}
};

