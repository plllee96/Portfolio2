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
	else if (_location == CardLocation::INVENTORY) {
		_rc = RectMake(firstInventoryCardX +  (_index % 8) * 50, firstInventoryCardY+(_index / 8) * 50, _cardImage->getFrameWidth(), _cardImage->getFrameHeight());
	}
	if (_location == CardLocation::BELT) {
		_beltX = beltStartX;
		_rc = RectMake(_beltX, firstDeckCardY, _cardImage->getFrameWidth(), _cardImage->getFrameHeight());
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
	if (_location == CardLocation::BELT) {
		if (_beltX > firstDeckCardX + _index * _cardImage->getFrameWidth()) {
			_beltX -= 0.3f;
			_rc = RectMake(_beltX, firstDeckCardY, _cardImage->getFrameWidth(), _cardImage->getFrameHeight());
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
		if (_active) {
			_cardImage->frameRender(getMemDC(), firstInventoryCardX + (_index%8) * 50, firstInventoryCardY + (_index / 8) * 50, 0, 0);
		}
		else {
			_cardImage->frameRender(getMemDC(), firstInventoryCardX + (_index % 8) * 50, firstInventoryCardY + (_index / 8) * 50, 1, 0);
		}
	}
	else if (_location == CardLocation::BELT) {
		_cardImage->frameRender(getMemDC(), _beltX, firstDeckCardY, 0, 0);
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

	case PlantType::LILYPAD:  _cardImage = IMAGEMANAGER->addFrameImage(
		"Lilypad_Icon", "Resources/Images/Plants/Icon/Lilypad_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::CABBAGEPULT:  _cardImage = IMAGEMANAGER->addFrameImage(
		"Cabbagepult_Icon", "Resources/Images/Plants/Icon/Cabbagepult_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::JALAPENO:  _cardImage = IMAGEMANAGER->addFrameImage(
		"Jalapeno_Icon", "Resources/Images/Plants/Icon/Jalapeno_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::CACTUS:  _cardImage = IMAGEMANAGER->addFrameImage(
		"Cactus_Icon", "Resources/Images/Plants/Icon/Cactus_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::THREEPEATER:  _cardImage = IMAGEMANAGER->addFrameImage(
		"Threepeater_Icon", "Resources/Images/Plants/Icon/Threepeater_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;


	case PlantType::TWINSUNFLOWER: _cardImage = IMAGEMANAGER->addFrameImage(
		"TwinSunflower_Icon", "Resources/Images/Plants/Icon/TwinSunflower_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	
	case PlantType::WALLNUTBOWLING: _cardImage = IMAGEMANAGER->addFrameImage(
		"WallnutBowling_Icon", "Resources/Images/Plants/Icon/WallnutBowling_Icon.bmp", 48, 44, 1, 1, true, RGB(255, 0, 255)); break;
	case PlantType::EXPLODEBOWLING: _cardImage = IMAGEMANAGER->addFrameImage(
		"ExplodeBowling_Icon", "Resources/Images/Plants/Icon/ExplodeBowling_Icon.bmp", 48, 44, 1, 1, true, RGB(255, 0, 255)); break;

	case PlantType::DOOMSHROOM: _cardImage = IMAGEMANAGER->addFrameImage(
		"Doomshroom_Icon", "Resources/Images/Plants/Icon/Doomshroom_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::SEASHROOM: _cardImage = IMAGEMANAGER->addFrameImage(
		"Seashroom_Icon", "Resources/Images/Plants/Icon/Seashroom_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::BLOVER: _cardImage = IMAGEMANAGER->addFrameImage(
		"Blover_Icon", "Resources/Images/Plants/Icon/Blover_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::PLANTERN: _cardImage = IMAGEMANAGER->addFrameImage(
		"Plantern_Icon", "Resources/Images/Plants/Icon/Plantern_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::TORCHWOOD: _cardImage = IMAGEMANAGER->addFrameImage(
		"Torchwood_Icon", "Resources/Images/Plants/Icon/Torchwood_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	case PlantType::SQUASH: _cardImage = IMAGEMANAGER->addFrameImage(
		"Squash_Icon", "Resources/Images/Plants/Icon/Squash_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	}
}

void Card::disableRender() {
	_cardImage->frameRender(getMemDC(), firstDeckCardX + _index * _cardImage->getFrameWidth(), firstDeckCardY, 1, 0);
}

void Card::reloadCard(int index) {
	_index = index;

	if (_location == CardLocation::DECK) {
		_rc = RectMake(firstDeckCardX + _index * _cardImage->getFrameWidth(), firstDeckCardY, _cardImage->getFrameWidth(), _cardImage->getFrameHeight());
	}
	else if (_location == CardLocation::INVENTORY) {
		_rc = RectMake(firstInventoryCardX + (_index % 8) * 50, firstInventoryCardY + (_index / 8) * 50, _cardImage->getFrameWidth(), _cardImage->getFrameHeight());
	}
}

void Card::startCoolTime() {
	_active = false;
	_startCoolTime = TIMEMANAGER->getWorldTime();
}
