#include "Stdafx.h"
#include "ShopItem.h"

HRESULT ShopItem::init(int index, ItemName itemName, int price) {
	_soldoutImage = IMAGEMANAGER->addImage("Soldout", "Resources/Images/Objects/Soldout.bmp", 54, 80, true, RGB(255, 0, 255));
	_index = index;
	_itemName = itemName;
	_soldout = false;
	
	_x = 170 + index % 3 * 84 - (index / 3) * 42;
	_y = 30 + index / 3 * 105;

	_priceX = _x + 25;
	_priceY = _y + 67;

	_number = new NumberImage;
	_number->init(&_priceX, &_priceY);

	_price = price;

	_rc = RectMake(_x, _y, itemWidth, itemHeight);
	return S_OK;
}

void ShopItem::release(void) {
}

void ShopItem::update(void) {
	
}

void ShopItem::render(void) {
	_number->render(_price);
	if (_soldout)  _soldoutImage->render(getMemDC(), _rc.left + 10, _rc.top);
}
