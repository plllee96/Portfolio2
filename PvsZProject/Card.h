#pragma once
#include "GameNode.h"
#include "PlantType.h"

const int firstDeckCardX = 120;
const int firstDeckCardY = 0;
const int firstInventoryCardX = 30;
const int firstInventoryCardY = 80;

enum class CardLocation {DECK, INVENTORY};
class Card : public GameNode {
private:
	Image* _cardImage;
	PlantType _type;
	CardLocation _location;
	RECT _rc;

	int _index;
	int _price;
	float _startCoolTime;
	float _maxCoolTime;
	float _coolTimeImageHeight;
	bool _active;	//DECK : 선택가능여부, INVENTORY : 덱 삽입가능여부

public:
	HRESULT init(PlantType type, CardLocation location, int price, float maxCoolTime, int index);
	void release(void);
	void update(void);
	void render(void);

	void initCardImage();
	void disableRender();

	int getPrice() { return _price; }
	float getCurrentCoolTime() { return _startCoolTime; }
	float getMaxCoolTime() { return _maxCoolTime; }
	bool isActive() { return _active; }

	void reloadCard(int index);
	void setActive(bool active) { _active = active; }
	void startCoolTime();

	Image* getCardImage() { return _cardImage; }
	PlantType getPlantType() { return _type; }
	RECT getRect() { return _rc; }
};

