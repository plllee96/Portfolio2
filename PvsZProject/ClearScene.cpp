#include "Stdafx.h"
#include "ClearScene.h"

HRESULT ClearScene::init(void) {
	wsprintf(_text, "CLEAR SCENE");
	return S_OK;
}

void ClearScene::release(void) {
}

void ClearScene::update(void) {
}

void ClearScene::render(void) {
	TextOut(getMemDC(), CENTER_X, CENTER_Y, _text, strlen(_text));
}
