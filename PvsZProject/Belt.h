#pragma once
#include "GameNode.h"
#include "Card.h"
#include "PlantType.h"

class Belt : public GameNode {
private:
	Image* _beltImage;

	typedef vector<Card*> vCard;
	typedef vector<Card*>::iterator viCard;

	vCard _vCard;
	viCard _viCard;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addCard(PlantType type);
	void removeCard(int index);
	int selectCard();

	int getSize() { return _vCard.size(); }
	PlantType getPlant(int index) { return _vCard[index]->getPlantType(); }
	Card* getCard(int index) { return _vCard[index]; }
};

