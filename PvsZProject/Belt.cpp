#include "Stdafx.h"
#include "Belt.h"

HRESULT Belt::init(void) {
	_beltImage = IMAGEMANAGER->addImage("Belt", "Resources/Images/Objects/Belt.bmp", 435, 50, false, RGB(255, 0, 255));
	return S_OK;
}

void Belt::release(void) {
}

void Belt::update(void) {
	_viCard = _vCard.begin();
	for (; _viCard != _vCard.end(); ++_viCard) {
		(*_viCard)->update();
	}
}

void Belt::render(void) {
	//print beltImage
	_beltImage->render(getMemDC(), WINSIZE_X - _beltImage->getWidth(), 2);

	_viCard = _vCard.begin();
	for (; _viCard != _vCard.end(); ++_viCard) {
		(*_viCard)->render();
	}
}

void Belt::addCard(PlantType type) {
	Card* card = new Card;
	card->init(type, CardLocation::BELT, 0, 0, _vCard.size());
	_vCard.push_back(card);
}

void Belt::removeCard(int index) {
	_vCard.erase(_vCard.begin() + index);
	for (int i = 0; i < _vCard.size(); i++) {
		_vCard[i]->reloadCard(i);
	}
}

int Belt::selectCard() {
	for (int i = 0; i < _vCard.size(); i++) {
		if (PtInRect(&(_vCard[i]->getRect()), _ptMouse)) {
			return i;
		}
	}
	return -1;
}
