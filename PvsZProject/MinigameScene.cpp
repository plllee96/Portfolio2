#include "Stdafx.h"
#include "MinigameScene.h"

HRESULT MinigameScene::init(void) {
	_background = IMAGEMANAGER->addImage("Stage1", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255));


	return S_OK;
}

void MinigameScene::release(void) {
}

void MinigameScene::update(void) {
}

void MinigameScene::render(void) {
}
