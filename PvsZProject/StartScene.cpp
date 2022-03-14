#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void) {
	wsprintf(_text, "START SCENE");
	return S_OK;
}

void StartScene::release(void) {

}

void StartScene::update(void) {

}

void StartScene::render(void) {
	TextOut(getMemDC(), CENTER_X, CENTER_Y, _text, strlen(_text));
}
