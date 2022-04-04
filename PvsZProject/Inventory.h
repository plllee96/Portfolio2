#pragma once
#include "GameNode.h"
#include "Card.h"

class Inventory : public GameNode {
private:
	Image* _image;
	vector<Card*> _vCard;
	vector<Card*>::iterator _viCard;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addCard(PlantType type);
	int selectCard();
	Card* getCard(int index) { return _vCard[index]; }
	void activeCard(int index, bool active);
	int getIndex(PlantType type);

	int getPrice(PlantType type);
	float getCooltime(PlantType type);

	int getSize() { return _vCard.size(); }
};

