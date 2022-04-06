#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init(void) {
	IMAGEMANAGER->addFrameImage("Peashooter_Bullet_Hit", "Resources/Images/Plants/Bullet/Peashooter_Bullet.bmp", 84, 34, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Puffshroom_Bullet_Hit", "Resources/Images/Plants/Bullet/PuffShroom_Bullet.bmp", 528, 52, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Arm", "Resources/Images/Zombies/arm.bmp", 14, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Head", "Resources/Images/Zombies/head.bmp", 44, 40, true, RGB(255, 0, 255));
	//! Add Image here
	
	return S_OK;
}

void EffectManager::release(void) {
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect) {
		(*_viEffect)->release();
		SAFE_DELETE(*_viEffect);
		_vEffect.erase(_viEffect);
	}

	_viArmEffect = _vArmEffect.begin();
	for (; _viArmEffect != _vArmEffect.end(); ++_viArmEffect) {
		(*_viArmEffect)->release();
		SAFE_DELETE(*_viArmEffect);
		_vArmEffect.erase(_viArmEffect);
	}

	_viObjectEffect = _vObjectEffect.begin();
	for (; _viObjectEffect != _vObjectEffect.end(); ++_viObjectEffect) {
		(*_viObjectEffect)->release();
		SAFE_DELETE(*_viObjectEffect);
		_vObjectEffect.erase(_viObjectEffect);
	}
}

void EffectManager::update(void) {
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect) {
		(*_viEffect)->update();

		if (!(*_viEffect)->getIsActive()) {
			(*_viEffect)->release();
			SAFE_DELETE(*_viEffect);
			_vEffect.erase(_viEffect);
			break;
		}
	}

	_viArmEffect = _vArmEffect.begin();
	for (; _viArmEffect != _vArmEffect.end(); ++_viArmEffect) {
		(*_viArmEffect)->update();

		if (!(*_viArmEffect)->getIsActive()) {
			(*_viArmEffect)->release();
			SAFE_DELETE(*_viArmEffect);
			_vArmEffect.erase(_viArmEffect);
			break;
		}
	}

	_viObjectEffect = _vObjectEffect.begin();
	for (; _viObjectEffect != _vObjectEffect.end(); ++_viObjectEffect) {
		(*_viObjectEffect)->update();

		if (!(*_viObjectEffect)->getIsActive()) {
			(*_viObjectEffect)->release();
			SAFE_DELETE(*_viObjectEffect);
			_vObjectEffect.erase(_viObjectEffect);
			break;
		}
	}
}

void EffectManager::render(void) {
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect) {
		(*_viEffect)->render();
	}

	_viArmEffect = _vArmEffect.begin();
	for (; _viArmEffect != _vArmEffect.end(); ++_viArmEffect) {
		(*_viArmEffect)->render();
	}

	_viObjectEffect = _vObjectEffect.begin();
	for (; _viObjectEffect != _vObjectEffect.end(); ++_viObjectEffect) {
		(*_viObjectEffect)->render();
	}
}

void EffectManager::createEffect(const char * fileName, float delay, int x, int y) {
	Effect* effect = new Effect;
	effect->init(fileName, delay, x, y);
	_vEffect.push_back(effect);
}

void EffectManager::createArm(const char * fileName, int x, int y) {
	ArmEffect* effect = new ArmEffect;
	effect->init(fileName, x, y);
	_vArmEffect.push_back(effect);
}

void EffectManager::createObject(const char * fileName, int x, int y) {
	ObjectEffect* effect = new ObjectEffect;
	effect->init(fileName, x, y);
	_vObjectEffect.push_back(effect);
}
