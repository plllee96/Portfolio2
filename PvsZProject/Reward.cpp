#include "Stdafx.h"
#include "Reward.h"

HRESULT Reward::init(int stageNum) {
	switch (stageNum) {
		case 0: _image = IMAGEMANAGER->addFrameImage(
			"PuffShroom_Icon", "Resources/Images/Plants/Icon/PuffShroom_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
		case 1: _image = IMAGEMANAGER->addFrameImage(
			"Lilypad_Icon", "Resources/Images/Plants/Icon/Lilypad_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
		case 2: _image = IMAGEMANAGER->addFrameImage(
			"PuffShroom_Icon", "Resources/Images/Plants/Icon/PuffShroom_Icon.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255)); break;
	}
	_status = RewardStatus::GENERATE;
	_x = 0;
	_y = 0;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_targetY = _y + RND->getFromFloatTo(10.0f, 20.0f);
	_xspeed = RND->getFromFloatTo(-0.5f, 0.5f);
	_gravity = RND->getFromFloatTo(2.0f, 3.0f);

	_show = false;

	return S_OK;
}

void Reward::release() {
}

void Reward::update() {
	switch (_status) {
		case RewardStatus::GENERATE : {
			if (_y <= _targetY) {
				_y -= _gravity;
				_x += _xspeed;
				_gravity -= 0.1f;
			}
		} break;
		case RewardStatus::OBTAIN: {
			if (_x < WINSIZE_X / 2) _x+= 0.3;
			else if (_x > WINSIZE_X / 2) _x-= 0.3;
			if (_y < WINSIZE_Y / 2) _y+= 0.3;
			else if (_y > WINSIZE_Y / 2) _y-= 0.3;
		}
	}


	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Reward::render() {
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

void Reward::spawnReward(bool show, int x, int y) {
	if (_show) return;
	_show = show;
	_x = x;
	_y = y + 50;

	_targetY = _y + RND->getFromFloatTo(10.0f, 20.0f);
	_xspeed = RND->getFromFloatTo(-0.5f, 0.5f);
	_gravity = RND->getFromFloatTo(2.0f, 3.0f);
}
