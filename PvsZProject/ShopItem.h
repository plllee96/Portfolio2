#pragma once
#include "GameNode.h"
#include "ShopItemName.h"
#include "NumberImage.h"

const int itemWidth = 70;
const int itemHeight = 65;

class ShopItem : GameNode {
private:
	Image* _soldoutImage;
	NumberImage* _number;
	ItemName _itemName;
	float _x;
	float _y;
	float _priceX;
	float _priceY;
	RECT _rc;
	int _index;
	int _price;
	bool _soldout;
public:
	HRESULT init(int index, ItemName itemName, int price);
	void release(void);
	void update(void);
	void render(void);

	RECT getRect() { return _rc; }
	bool isSoldout() { return _soldout; }
	void setSoldout(bool soldout) { _soldout = soldout; }
	int getPrice() { return _price; }
};

