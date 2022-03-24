#include "Stdafx.h"
#include "Card.h"

HRESULT Card::init(PlantType type, CardLocation location, int price, float maxCoolTime, int index) {
	_index = index;
	_type = type;
	_location = location;
	initCardImage();

	_price = price;
	_startCoolTime = 0.0f;
	_maxCoolTime = maxCoolTime;
	_coolTimeImageHeight = 0.0f;

	_active = true;
	if (_location == CardLocation::DECK) {
		_rc = RectMake(firstDeckCardX + _index * _cardImage->getFrameWidth(), firstDeckCardY, _cardImage->getFrameWidth(), _cardImage->getFrameHeight());
	}
	
	return S_OK;
}

void Card::release(void) {
}

void Card::update(void) {
	if (_location == CardLocation::DECK && !_active) {
		_coolTimeImageHeight = _cardImage->getFrameHeight() * ((TIMEMANAGER->getWorldTime() - _startCoolTime) / _maxCoolTime);
		if (_startCoolTime + _maxCoolTime <= TIMEMANAGER->getWorldTime()) {
			_active = true;
		}
	}
}

void Card::render(void) {
	if (_location == CardLocation::DECK) {
		if (_active) {
			_cardImage->frameRender(getMemDC(), firstDeckCardX + _index * _cardImage->getFrameWidth(), firstDeckCardY, 0, 0);
		}
		else {
			_cardImage->frameRender(getMemDC(), firstDeckCardX + _index * _cardImage->getFrameWidth(), firstDeckCardY, 1, 0);
			_cardImage->render(getMemDC(), firstDeckCardX + _index * _cardImage->getFrameWidth(), firstDeckCardY, 0, 0, _cardImage->getFrameWidth(), _coolTimeImageHeight);
		}
	}
	else if (_location == CardLocation::INVENTORY) {
		//세로 위치 수정 필요
		if (_active) {
			_cardImage->frameRender(getMemDC(), firstInventoryCardX + _index * _cardImage->getFrameWidth(), firstInventoryCardY, 0, 0);
		}
		else {
			_cardImage->frameRender(getMemDC(), firstInventoryCardX + _index * _cardImage->getFrameWidth(), firstInventoryCardY, 1, 0);
		}
	}
}

void Card::initCardImage() {
	switch (_type) {
	case PlantType::PEASHOOTER: _cardImage = IMAGEMANAGER->addFrameImage(
		"Peashooter_Icon", "Resources/Images/Plants/Icon/Peashooter_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::SUNFLOWER: _cardImage = IMAGEMANAGER->addFrameImage(
		"Sunflower_Icon", "Resources/Images/Plants/Icon/Sunflower_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::WALLNUT: _cardImage = IMAGEMANAGER->addFrameImage(
		"Wallnut_Icon", "Resources/Images/Plants/Icon/Wallnut_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::CHERRYBOMB: _cardImage = IMAGEMANAGER->addFrameImage(
		"Cherrybomb_Icon", "Resources/Images/Plants/Icon/Cherrybomb_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::POTATOMINE: _cardImage = IMAGEMANAGER->addFrameImage(
		"PotatoMine_Icon", "Resources/Images/Plants/Icon/PotatoMine_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::CHOMPER: _cardImage = IMAGEMANAGER->addFrameImage(
		"Chomper_Icon", "Resources/Images/Plants/Icon/Chomper_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;

	case PlantType::PUFFSHROOM: _cardImage = IMAGEMANAGER->addFrameImage(
		"PuffShroom_Icon", "Resources/Images/Plants/Icon/PuffShroom_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::SUNSHROOM: _cardImage = IMAGEMANAGER->addFrameImage(
		"Sunshroom_Icon", "Resources/Images/Plants/Icon/Sunshroom_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::FUMESHROOM: _cardImage = IMAGEMANAGER->addFrameImage(
		"FumeShroom_Icon", "Resources/Images/Plants/Icon/FumeShroom_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::SCAREDYSHROOM: _cardImage = IMAGEMANAGER->addFrameImage(
		"ScaredyShroom_Icon", "Resources/Images/Plants/Icon/ScaredyShroom_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::GRAVEBUSTER: _cardImage = IMAGEMANAGER->addFrameImage(
		"GraveBuster_Icon", "Resources/Images/Plants/Icon/GraveBuster_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;

		
	//아이콘 제작 후 전부 추가할 것
	}
}

void Card::disableRender() {
	_cardImage->frameRender(getMemDC(), firstDeckCardX + _index * _cardImage->getFrameWidth(), firstDeckCardY, 1, 0);
}

void Card::startCoolTime() {
	_active = false;
	_startCoolTime = TIMEMANAGER->getWorldTime();
}
