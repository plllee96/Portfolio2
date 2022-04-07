#include "Stdafx.h"
#include "ObserverManager.h"

#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"
#include "EffectManager.h"

HRESULT ObserverManager::init(void) {
	_em = new EffectManager;
	_em->init();

	_tempRC = { 0,0,0,0 };
	return S_OK;
}

void ObserverManager::release(void) {
	_vObserver.clear();
}

void ObserverManager::update(void) {
	manageRect();
	manageBullet();
	_em->update();
}

void ObserverManager::render(void) {
	_em->render();
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

void ObserverManager::registerBulletObserver(BulletObserver * observer) {
	_vBulletObserver.push_back(observer);
}

void ObserverManager::removeBulletObserver(BulletObserver * observer) {
	_viBulletObserver = _vBulletObserver.begin();
	for (; _viBulletObserver != _vBulletObserver.end(); ++_viBulletObserver) {
		if (*_viBulletObserver == observer) {
			_vBulletObserver.erase(_viBulletObserver);
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
				bool isRecognize;
				if ((*observer.plantType) == PlantType::THREEPEATER) {
					isRecognize = (*observer.line == *observerCompare.line || *observer.line == *observerCompare.line - 1 || *observer.line == *observerCompare.line + 1);
				}
				else isRecognize = *observer.line == *observerCompare.line;

				RECT collisionRc;
				if (IntersectRect(&collisionRc, observer.recognizeRc, observerCompare.rc) && isRecognize) {
					(*_viObserver)->recognizeObject(observerCompare);

					bool emptyRC = (_tempRC.left == 0 && _tempRC.right == 0 && _tempRC.top == 0 && _tempRC.bottom == 0);
					if ((*observer.plantType) == PlantType::CABBAGEPULT && emptyRC) {
						_tempRC = (*observerCompare.rc);
					}
					continue;
				}

			}

			//Collide Zombie & Plant -> Zombie Attack, Plant HP Down
			if ((*observer.type) == ObservedType::ZOMBIE && (*observerCompare.type) == ObservedType::PLANT) {
				RECT collisionRc;
				if (IntersectRect(&collisionRc, observer.recognizeRc, observerCompare.rc) && *observer.line == *observerCompare.line) {
					(*_viObserver)->recognizeObject(observerCompare);
					(*_viObserverCompare)->collideObject(observer);
					continue;
				}
			}

			//Collide Bullet & Zombie -> Zombie HP Down & Remove Bullet
			if ((*observer.type) == ObservedType::BULLET && (*observerCompare.type) == ObservedType::ZOMBIE) {
				RECT collisionRc;
				if (IntersectRect(&collisionRc, observer.rc, observerCompare.rc)) {
					(*_viObserver)->collideObject(observerCompare);
					(*_viObserverCompare)->collideObject(observer);
					SOUNDMANAGER->play("Hit", 1.0f);
					if ((*observer.bulletType) == BulletType::PEASHOOTER_BULLET || (*observer.bulletType) == BulletType::THREEPEATER_BULLET) {
						_em->createEffect("Peashooter_Bullet_Hit", 0.08f, observer.rc->left + 35, observer.rc->top - 12);
					}
					else if ((*observer.bulletType) == BulletType::MUSHROOM_BULLET) {
						_em->createEffect("Puffshroom_Bullet_Hit", 0.08f, observer.rc->left + 35, observer.rc->top);
					}
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

void ObserverManager::manageBullet() {
	if (_vBulletObserver.size() == 0) return;

	_viBulletObserver = _vBulletObserver.begin();
	for (; _viBulletObserver != _vBulletObserver.end(); ++_viBulletObserver) {
		BulletObserveData observer;
		observer = (*_viBulletObserver)->getFireUpdate();

		_viBulletObserverCompare = _vBulletObserver.begin();
		for (; _viBulletObserverCompare != _vBulletObserver.end(); ++_viBulletObserverCompare) {
			BulletObserveData observerCompare;
			observerCompare = (*_viBulletObserverCompare)->getFireUpdate();

			if ((*observer.type) == (*observerCompare.type)) continue;

			if ((*observer.type) == BulletObservedType::OBJECT && (*observerCompare.type == BulletObservedType::BULLETMANAGER)) {
				if (*observer.fire) {
					if ((*observer.plantType) == PlantType::CABBAGEPULT) {
						(*_viBulletObserverCompare)->fireObject(observer, _tempRC);
						_tempRC = { 0,0,0,0 };
					}
					else (*_viBulletObserverCompare)->fireObject(observer);
				}
			}
		}
	}
}

