#include "Stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init(void) {
	_background = IMAGEMANAGER->addImage("ShopBackground", "Resources/Images/Backgrounds/Shop.bmp", 548, 384, false, RGB(255, 0, 255));
	_blackChanger = IMAGEMANAGER->addImage("blackChanger", 548, 384);
	_goingToGame = false;
	_blackAlpha = 255;
	
	_nextLevelRc = RectMake(140, 310, 170, 80);


	_money.x = 430;
	_money.y = 355;
	_money.numImage = new NumberImage;
	_money.numImage->init(&_money.x, &_money.y);

	loadShop();
	return S_OK;
}

void ShopScene::release(void) {
}

void ShopScene::update(void) {
	sceneChangerControl();
	mouseControl();
	_money.numImage->update();
	
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem) {
		(*_viItem)->update();
	}
}

void ShopScene::render(void) {
	_background->render(getMemDC());

	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem) {
		(*_viItem)->render();
	}
	_money.numImage->render(_money.money);

	_blackChanger->alphaRender(getMemDC(), _blackAlpha);
}

void ShopScene::sceneChangerControl() {
	if (_goingToGame) {
		if (_blackAlpha > 253) SCENEMANAGER->changeScene("Game");
		else _blackAlpha += 2;
	}
	else {
		_blackAlpha -= 2;
		if (_blackAlpha < 0) _blackAlpha = 0;
	}
}

void ShopScene::mouseControl() {
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		//Click NextLevel Button to go to game scene
		if (PtInRect(&_nextLevelRc, _ptMouse)) {
			_goingToGame = true;
		}

		//Click Item to buy Item
		_viItem = _vItem.begin();
		for (; _viItem != _vItem.end(); ++_viItem) {
			if (PtInRect(&(*_viItem)->getRect(), _ptMouse)) {
				if (_money.money >= (*_viItem)->getPrice()) {
					_money.money -= (*_viItem)->getPrice();
					(*_viItem)->setSoldout(true);

					if ((*_viItem)->getType() == ItemName::SLOT) {
						vector<string> vData = TEXTDATAMANAGER->load("data.txt");
						int newSlot = atoi(vData[1].c_str()) + 1; 

						char temp[32];
						vData[1] = _itoa((int)newSlot, temp, 10);
						vData[2] = _itoa((int)_money.money, temp, 10);

						TEXTDATAMANAGER->save("data.txt", vData);
					}
					if ((*_viItem)->getType() == ItemName::TWIN_SUNFLOWER) {
						vector<string> vData = TEXTDATAMANAGER->load("data.txt");

						char temp[32];
						vData[2] = _itoa((int)_money.money, temp, 10);
						vData.push_back(_itoa((int)16, temp, 10));

						TEXTDATAMANAGER->save("data.txt", vData);
					}
					break;
				}
			}
		}
	}
}

void ShopScene::loadShop() {
	vector<string> vData = TEXTDATAMANAGER->load("data.txt");
	_money.money = atoi(vData[2].c_str());


	for (int i = 0; i < 5; i++) {
		ShopItem* item = new ShopItem;

		int tempPrice;
		switch (i) {
			case 0: tempPrice = 600; break;
			case 1: tempPrice = 300; break;
			case 2: tempPrice = 250; break;
			case 3: tempPrice = 550; break;
			case 4: tempPrice = 400; break;
		}

		item->init(i, static_cast<ItemName>(i), tempPrice);
		_vItem.push_back(item);
	}

}
