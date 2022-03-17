#include "Stdafx.h"
#include "Deck.h"

HRESULT Deck::init(void) {
	addCard(PlantType::PEASHOOTER, 100, 10.0f);
	addCard(PlantType::SUNFLOWER, 50, 10.0f);
	addCard(PlantType::WALLNUT, 50, 10.0f);
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
	_viCard = _vCard.begin();
	for (; _viCard != _vCard.end(); ++_viCard) {
		(*_viCard)->render();
	}
}

void Deck::render(int sun) {
	_viCard = _vCard.begin();
	for (; _viCard != _vCard.end(); ++_viCard) {
		if ((*_viCard)->getPrice() > sun) (*_viCard)->disableRender();
		else (*_viCard)->render();
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

int Deck::selectCard() {
	for (int i = 0; i < _vCard.size(); i++) {
		if (PtInRect(&(_vCard[i]->getRect()), _ptMouse)) {
			return i;
		}
	}
	return -1;
}
