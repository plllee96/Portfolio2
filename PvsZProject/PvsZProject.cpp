#include "Stdafx.h"
#include "Lecture2101.h"

HRESULT Lecture2101::init() {
	_rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 200, 40, 40);
	_health = RectMakeCenter(WINSIZE_X / 2 + 250, WINSIZE_Y / 2 - 350, 200, 40);
	_maxhealth = RectMakeCenter(WINSIZE_X / 2 + 250, WINSIZE_Y / 2 - 350, 200, 40);

	_invTime = 0;

	for (int i = 0; i < ENEMY_MAX; i++) {
		_enemy[i].rc = RectMakeCenter(RND->getFromIntTo(20, WINSIZE_X - 20),
			-(RND->getFromIntTo)(80, WINSIZE_Y * 2), 20, 20);
		_enemy[i].speed = RND->getFromIntTo(2, 8);
		_enemy[i].die = false;

	}

	return S_OK;
}

void Lecture2101::release() {
}

void Lecture2101::update() {
	if (_invTime > 0) _invTime--;
	if (_health.right - _health.left < 0) _health.right = _health.left;

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _rc.right) {
		_rc.left += PLAYER_SPEED;
		_rc.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && 0 < _rc.left) {
		_rc.left -= PLAYER_SPEED;
		_rc.right -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && 0 < _rc.top) {
		_rc.top -= PLAYER_SPEED;
		_rc.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && WINSIZE_Y > _rc.bottom) {
		_rc.top += PLAYER_SPEED;
		_rc.bottom += PLAYER_SPEED;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		fire();
	}
	for (int i = 0; i < BULLET_MAX; i++) {
		if (!_bullet[i].fire) continue;
		_bullet[i].rc.top -= 14;
		_bullet[i].rc.bottom -= 14;

		if (_bullet[i].rc.bottom < 0) _bullet[i].fire = false;

		POINT bpt = { _bullet[i].rc.left+3, _bullet[i].rc.top+3 };
		for (int j = 0; j < ENEMY_MAX; j++) {
			if (!_enemy[j].die && PtInRect(&_enemy[j].rc, bpt)) {
				_enemy[j].die = true;
				_bullet[i].fire = false;
			}
		}
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (_enemy[i].die) continue;
		_enemy[i].rc.top += _enemy[i].speed;
		_enemy[i].rc.bottom += _enemy[i].speed;

		if (_enemy[i].rc.top > WINSIZE_Y) {
			_enemy[i].rc = RectMakeCenter(RND->getFromIntTo(20, WINSIZE_X - 20),
				-(RND->getFromIntTo(80, WINSIZE_Y * 2)), 20, 20);
		}

		if (PtInRect(&_rc, { _enemy[i].rc.left, _enemy[i].rc.top }) && _invTime == 0) {
			if(_health.right - _health.left > 15) _health.right -= 15;
			else _health.right = _health.left;
			_invTime = 50;
		}
	}
}

void Lecture2101::render(HDC hdc) {
	HBRUSH redbrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH yellowbrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH greenbrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH blackbrush = CreateSolidBrush(RGB(0, 0, 0));

	if (_health.right - _health.left > 0) {
		Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
		if (_invTime > 0) FillRect(hdc, &_rc, redbrush);
		else  FillRect(hdc, &_rc, blackbrush);
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (_enemy[i].die) continue;
		Rectangle(hdc, _enemy[i].rc.left, _enemy[i].rc.top, _enemy[i].rc.right, _enemy[i].rc.bottom);
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		if (!_bullet[i].fire) continue;
		Ellipse(hdc, _bullet[i].rc.left, _bullet[i].rc.top, _bullet[i].rc.right, _bullet[i].rc.bottom);
	}

	Rectangle(hdc, _maxhealth.left, _maxhealth.top, _maxhealth.right, _maxhealth.bottom);
	Rectangle(hdc, _health.left, _health.top, _health.right, _health.bottom);
	if (_health.right - _health.left > 120) FillRect(hdc, &_health, greenbrush);
	else if (_health.right - _health.left > 40)  FillRect(hdc, &_health, yellowbrush);
	else FillRect(hdc, &_health, redbrush);

	DeleteObject(redbrush);
	DeleteObject(yellowbrush);
	DeleteObject(greenbrush);
	DeleteObject(blackbrush);
}

void Lecture2101::fire() {
	for (int i = 0; i < BULLET_MAX; i++) {
		if (_bullet[i].fire) continue;
		_bullet[i].fire = true;
		_bullet[i].rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2,
			_rc.top + (_rc.bottom - _rc.top) / 2 - 24, 7, 7);

		break;
	}
}

/*
실습1. 종스크롤 슈팅 게임
- 플레이어 체력바 설정 : 적과 충돌하면 체력 감소
- 플레이어가 발사한 총알로 적 제거

*/