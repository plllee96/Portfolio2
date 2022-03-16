#pragma once
#include "GameNode.h"
#include "Card.h"

class Deck : public GameNode {
private:
	vector<Card*> _vCard;
	vector<Card*>::iterator _viCard;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void disableRender();

	//Vector Control
	void addCard(PlantType type, int price, int maxCoolTime);
	int selectCard();

	// Get,Set
	PlantType getPlant(int index) { return _vCard[index]->getPlantType(); }
	Card* getCard(int index) { return _vCard[index]; }
};

