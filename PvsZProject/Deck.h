#pragma once
#include "GameNode.h"
#include "Card.h"

class Deck : public GameNode {
private:
	Image* _slotImage;
	vector<Card*> _vCard;
	vector<Card*>::iterator _viCard;
	
	int _maxSlot;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void render(int sun);

	void printSlot();
	void disableRender();

	//Vector Control
	void addCard(PlantType type, int price, int maxCoolTime);
	void removeCard(int index);
	int selectCard();

	// Get,Set
	PlantType getPlant(int index) { return _vCard[index]->getPlantType(); }
	Card* getCard(int index) { return _vCard[index]; }
	int getCurrentSlot() { return _vCard.size(); }
	void setMaxSlot(int slot) { _maxSlot = slot; }
};

