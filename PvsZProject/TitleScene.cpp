#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void) {
	wsprintf(_text, "TITLE SCENE");
	return S_OK;
}

void TitleScene::release(void) {
}

void TitleScene::update(void) {
}

void TitleScene::render(void) {
	TextOut(getMemDC(), CENTER_X, CENTER_Y, _text, strlen(_text));
}
