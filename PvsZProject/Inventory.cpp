#include "Stdafx.h"
#include "Inventory.h"

int Inventory::getPrice(PlantType type) {
	switch (type) {
		case PlantType::PEASHOOTER: return 100; break;
		case PlantType::SUNFLOWER: return 50; break;
		case PlantType::WALLNUT: return 50; break;
		case PlantType::CHERRYBOMB: return 150; break;
		case PlantType::POTATOMINE: return 25; break;
		case PlantType::CHOMPER: return 150; break;
		case PlantType::PUFFSHROOM: return 0; break;
		case PlantType::SUNSHROOM: return 25; break;
		case PlantType::FUMESHROOM: return 75; break;
		case PlantType::SCAREDYSHROOM: return 25; break;
		case PlantType::GRAVEBUSTER: return 75; break;
		case PlantType::LILYPAD: return 25; break;
		case PlantType::THREEPEATER: return 325; break;
		case PlantType::CABBAGEPULT: return 100; break;
		case PlantType::JALAPENO: return 125; break;
		case PlantType::TWINSUNFLOWER: return 150; break;
		case PlantType::DOOMSHROOM: return 125; break;
		case PlantType::SEASHROOM: return 0; break;
		case PlantType::BLOVER: return 100; break;
		case PlantType::PLANTERN: return 25; break;
		case PlantType::TORCHWOOD: return 175; break;
		case PlantType::SQUASH: return 50; break;
		default: return 0; break;
	}
}

float Inventory::getCooltime(PlantType type) {
	switch (type) {
		case PlantType::PEASHOOTER: return 7.0f; break;
		case PlantType::SUNFLOWER: return 7.0f; break;
		case PlantType::WALLNUT: return 7.0f; break;
		case PlantType::CHERRYBOMB: return 30.0f; break;
		case PlantType::POTATOMINE: return 7.0f; break;
		case PlantType::CHOMPER: return 30.0f; break;
		case PlantType::PUFFSHROOM: return 7.0f; break;
		case PlantType::SUNSHROOM: return 7.0f; break;
		case PlantType::FUMESHROOM: return 7.0f; break;
		case PlantType::SCAREDYSHROOM: return 7.0f; break;
		case PlantType::GRAVEBUSTER: return 20.0f; break;
		case PlantType::LILYPAD: return 7.0f; break;
		case PlantType::THREEPEATER: return 30.0f; break;
		case PlantType::CABBAGEPULT: return 7.0f; break;
		case PlantType::JALAPENO: return 30.0f; break;
		case PlantType::TWINSUNFLOWER: return 20.0f; break;
		case PlantType::DOOMSHROOM: return 30.0f; break;
		case PlantType::SEASHROOM: return 7.0f; break;
		case PlantType::BLOVER: return 20.0f; break;
		case PlantType::PLANTERN: return 7.0f; break;
		case PlantType::TORCHWOOD: return 20.0f; break;
		case PlantType::SQUASH: return 7.0f; break;

		default: return 7.0f; break;
	}
}

HRESULT Inventory::init(void) {
	_image = IMAGEMANAGER->addImage("Inventory", "Resources/Images/Objects/Inventory.bmp", 440, 354, true, RGB(255, 0, 255));
	return S_OK;
}

void Inventory::release(void) {
}

void Inventory::update(void) {
}

void Inventory::render(void) {
	_image->render(getMemDC(), 15, 45);
	_viCard = _vCard.begin();
	for (; _viCard != _vCard.end(); ++_viCard) {
		(*_viCard)->render();
	}
}

void Inventory::addCard(PlantType type) {
	Card* card = new Card;
	card->init(type, CardLocation::INVENTORY, getPrice(type), getPrice(type), _vCard.size());
	_vCard.push_back(card);
}

int Inventory::selectCard() {
	for (int i = 0; i < _vCard.size(); i++) {
		if (PtInRect(&(_vCard[i]->getRect()), _ptMouse)) {
			return i;
		}
	}
	return -1;
}


void Inventory::activeCard(int index, bool active) {
	_vCard[index]->setActive(active);
}

int Inventory::getIndex(PlantType type) {
	for (int i = 0; i < _vCard.size(); i++) {
		if (_vCard[i]->getPlantType() == type) return i;
	}
	return -1;
}

