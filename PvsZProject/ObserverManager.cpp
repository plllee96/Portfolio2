#include "Stdafx.h"
#include "ObserverManager.h"

#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"

HRESULT ObserverManager::init(void) {
	return S_OK;
}

void ObserverManager::release(void) {
	_vObserver.clear();
}

void ObserverManager::update(void) {
	manageRect();
}

void ObserverManager::render(void) {
}

void ObserverManager::registerObserver(Observer * observer) {
	_vObserver.push_back(observer);
}

void ObserverManager::removeObserver(Observer * observer) {
	_viObserver = _vObserver.begin();
	for (; _viObserver != _vObserver.end(); ++_viObserver) {
		if (*_viObserver == observer) {
			_vObserver.erase(_viObserver);
			break;
		}
	}
}

void ObserverManager::manageRect() {
	if (_vObserver.size() == 0) return;

	_viObserver = _vObserver.begin();
	for (; _viObserver != _vObserver.end(); ++_viObserver) {
		ObserveData observer;
		observer = (*_viObserver)->getRectUpdate();

		_viObserverCompare = _vObserver.begin();
		for (; _viObserverCompare != _vObserver.end(); ++_viObserverCompare) {
			ObserveData observerCompare;
			observerCompare = (*_viObserverCompare)->getRectUpdate();

			//Compare observer & observerCompare

			if ((*observer.type) == (*observerCompare.type)) continue;

			//Collide Plant's RecognizeRect & Zombie -> Plant Attack
			if ((*observer.type) == ObservedType::PLANT && (*observerCompare.type) == ObservedType::ZOMBIE) {
				RECT collisionRc;
				if (IntersectRect(&collisionRc, observer.recognizeRc, observerCompare.rc)) {
					(*_viObserver)->recognizeObject(observerCompare);
					continue;
				}				
			}
			
			//Collide Zombie & Plant -> Zombie Attack
			if ((*observer.type) == ObservedType::ZOMBIE && (*observerCompare.type) == ObservedType::PLANT) {
				RECT collisionRc;
				if (IntersectRect(&collisionRc, observer.recognizeRc, observerCompare.rc)) {
					(*_viObserver)->recognizeObject(observerCompare);
					continue;
				}
			}

			//Collide Bullet & Zombie -> Zombie HP Down & Remove Bullet
			if ((*observer.type) == ObservedType::BULLET && (*observerCompare.type) == ObservedType::ZOMBIE) {
				RECT collisionRc;
				if (IntersectRect(&collisionRc, observer.rc, observerCompare.rc)) {
					(*_viObserver)->collideObject(observerCompare);
					(*_viObserverCompare)->collideObject(observer);
					continue;
				}
			}

			//Collide Plant & Bullet (only Torchwood)
			if ((*observer.type) == ObservedType::BULLET && (*observerCompare.type) == ObservedType::PLANT) {
				RECT collisionRc;
				if (IntersectRect(&collisionRc, observer.rc, observerCompare.rc)) {
					(*_viObserver)->collideObject(observerCompare);
					continue;
				}
			}
		}
	}
}
