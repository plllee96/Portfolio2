#include "Stdafx.h"
#include "Deck.h"

HRESULT Deck::init(void) {
	_slotImage = IMAGEMANAGER->addImage("Slot", "Resources/Images/Objects/Slot.bmp", 48, 40, true, RGB(255, 0, 255));

	return S_OK;
}

void Deck::release(void) {
}

void Deck::update(void) {
	_viCard = _vCard.begin();
	for (; _viCard != _vCard.end(); ++_viCard) {
		(*_viCard)->update();
	}
}

void Deck::render(void) {
	printSlot();
	_viCard = _vCard.begin();
	for (; _viCard != _vCard.end(); ++_viCard) {
		(*_viCard)->render();
	}
}

void Deck::render(int sun) {
	printSlot();
	_viCard = _vCard.begin();
	for (; _viCard != _vCard.end(); ++_viCard) {
		if ((*_viCard)->getPrice() > sun) (*_viCard)->disableRender();
		else (*_viCard)->render();
	}
}

void Deck::printSlot() {
	for (int i = 0; i < _maxSlot; i++) {
		_slotImage->alphaRender(getMemDC(), firstDeckCardX + i * _slotImage->getWidth(), firstDeckCardY+4, 128 );
	}
}

void Deck::disableRender() {
	_viCard = _vCard.begin();
	for (; _viCard != _vCard.end(); ++_viCard) {
		(*_viCard)->disableRender();
	}
}

void Deck::addCard(PlantType type, int price, int maxCoolTime) {
	Card* card = new Card;
	card->init(type, CardLocation::DECK, price, maxCoolTime, _vCard.size());
	_vCard.push_back(card);
}

void Deck::removeCard(int index) {
	_vCard.erase(_vCard.begin() + index);
	for (int i = 0; i < _vCard.size(); i++) {
		_vCard[i]->reloadCard(i);
	}
}

int Deck::selectCard() {
	for (int i = 0; i < _vCard.size(); i++) {
		if (PtInRect(&(_vCard[i]->getRect()), _ptMouse)) {
			return i;
		}
	}
	return -1;
}
