#include "Stdafx.h"
#include "HomeWork.h"

/*
과제1 . 1vs1 횡스크롤 슈팅 게임
- 왼쪽 1p (wasd)
- 오른쪽 2p (방향키)
- 체력바는 대전 게임처럼 중앙 기준 좌우 배치
- 공격을 당한쪽은 체력 감소
- 체력 상태에 따라 체력바 색상 변경(초록, 노랑, 빨강)
- 각각 스킬 3개씩

1. 조작법
- 왼쪽 1P		(검정색.		WASD로 이동, LShift로 공격)
- 오른쪽 2p		(회색.			방향키로 이동, RShift로 공격)

2. 스킬
- 스킬 활성화 조건 : 해당 스킬을 시전중이 아니라면 언제든 가능.
						   (2P 스킬은 1P의 시간 정지 스킬 시전중일 때는 사용불가)

A플레이어 스킬
[Z]				갈고리 : 갈고리에 맞은 플레이어는 바로 앞까지 끌려옴
[X]				방패 : 오른쪽으로 느리게 움직이는 방패. 방패는 총알을 막아줌.
[C]				시간정지 : 잠깐동안 자신을 제외하고 모두 정지

B플레이어 스킬
[Delete]		프리즘 : 프리즘 장벽을 통과한 총알은 적을 유도하며 빠르게 발사됨
[End]			시간역행 : 한번 누르면 현재 상태(체력,위치) 저장, 다시 누르면 해당 상태로 이동
[Pgdn]		혼란 탄환 : 맞은 적은 일정 시간 키 조작이 반대로 움직임

*/
HRESULT HomeWork::init() {

	_playerA.rc = RectMakeCenter(WINSIZE_X / 2 - 200, WINSIZE_Y / 2, 40, 40);
	_playerA.die = false;
	_playerA.health = 300;
	_playerA.confuse = false;
	_playerA.confuseTimer = 0;

	_playerB.rc = RectMakeCenter(WINSIZE_X / 2 + 200, WINSIZE_Y / 2, 40, 40);
	_playerB.die = false;
	_playerB.health = 300;

	AinvTime = 0;
	BinvTime = 0;


	//스킬 관련 초기화
#pragma region Skill
	_stopTimeEffect = { 0, 0, 0, 0 };

	_hook.casting = false;
	_hook.pull = false;
	_hook.grab = false;
	_hook.hookhead = { _playerA.rc.left + 40, _playerA.rc.top, _playerA.rc.right + 40, _playerA.rc.bottom };
	_hook.hookline = { _playerA.rc.right, _playerA.rc.top + 19, _hook.hookhead.left, _playerA.rc.bottom - 19 };

	_shield.casting = false;

	_playerB.castTimeRewind = false;
	_playerB.rewindTimer = 0;

	stopTime = false;
	stopTime_timer = 0;

	_prism.casting = false;
	_prism.timer = 0;

	_cBullet.fire = false;

	_maxhealthA = RectMakeCenter(WINSIZE_X / 2 + 200, 100 , 302, 22);
	_healthA = RectMakeCenter(WINSIZE_X / 2 - 200 , 100 , _playerA.health, 20);
	_maxhealthB = RectMakeCenter(WINSIZE_X / 2 - 200, 100, 302, 22);
	_healthB = RectMakeCenter(WINSIZE_X / 2 + 200, 100, _playerB.health, 20);


#pragma endregion

	return S_OK;
}

void HomeWork::release() {
}

void HomeWork::update() {
#pragma region Player&Health&Bullet
	if (AinvTime > 0) AinvTime--;
	if (BinvTime > 0) BinvTime--;
	if (_playerA.confuseTimer > 0) _playerA.confuseTimer--;
	if (_playerA.confuseTimer == 0) _playerA.confuse = false;

	_healthA.right = _healthA.left + _playerA.health;
	_healthB.left = _healthB.right - _playerB.health;

	if (_playerA.health <= 0) _playerA.die = true;
	if (_playerB.health <= 0) _playerB.die = true;

	movePlayerA();
	if(!stopTime) movePlayerB();

	if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT) && !_playerA.die) fireA();
	if (KEYMANAGER->isOnceKeyDown(VK_RSHIFT) && !_playerB.die && !stopTime) fireB();

	if (!stopTime) {
		for (int i = 0; i < A_BULMAX; i++) {
			if (!_bulletA[i].fire) continue;
			_bulletA[i].rc.left += 5;
			_bulletA[i].rc.right += 5;
			if (_bulletA[i].rc.left > WINSIZE_X) _bulletA[i].fire = false;

			if (PtInRect(&_playerB.rc, { _bulletA[i].rc.left, _bulletA[i].rc.top }) && !_playerB.die) {
				_bulletA[i].fire = false;
				if (BinvTime == 0) {
					_playerB.health -= 30;
					BinvTime = 50;
				}
			}
		}
		for (int i = 0; i < B_BULMAX; i++) {
			if (!_bulletB[i].fire) continue;
			_bulletB[i].rc.left -= 5;
			_bulletB[i].rc.right -= 5;
			if (_bulletB[i].homing) {
				_bulletB[i].rc.left -= 5;
				_bulletB[i].rc.right -= 5;
				if (!_playerA.die) {
					_bulletB[i].rc.top += (_bulletB[i].homingpos.y - _bulletB[i].rc.bottom) / 10;
					_bulletB[i].rc.bottom += (_bulletB[i].homingpos.y - _bulletB[i].rc.bottom) / 10;
				}
			}
			if (_bulletB[i].rc.left < 0) {
				_bulletB[i].fire = false;
				_bulletB[i].homing = false;
			}

			if (PtInRect(&_playerA.rc, { _bulletB[i].rc.left, _bulletB[i].rc.top }) && !_playerA.die) {
				_bulletB[i].fire = false;
				_bulletB[i].homing = false;
				if (AinvTime == 0) {
					_playerA.health -= 30;
					AinvTime = 50;
				}
			}

			if (PtInRect(&_shield.rc, { _bulletB[i].rc.left, _bulletB[i].rc.top }) && _shield.casting) {
				_bulletB[i].fire = false;
				_bulletB[i].homing = false;
				_shield.health -= 5;
			}

			if (PtInRect(&_prism.rc, { _bulletB[i].rc.left, _bulletB[i].rc.top }) && _prism.casting) {
				_bulletB[i].homing = true;
				_bulletB[i].homingpos = {_playerA.rc.left + (_playerA.rc.right - _playerA.rc.left) / 2, _playerA.rc.top + (_playerA.rc.bottom - _playerA.rc.top) / 2, };
			}
		}
	}
#pragma endregion

	if (KEYMANAGER->isOnceKeyDown('Z') && !_playerA.die) castHook();
	Hook();
	if (KEYMANAGER->isOnceKeyDown('X') && !_playerA.die) castShield();
	Shield();
	if (KEYMANAGER->isOnceKeyDown('C') && !_playerA.die) castStopTime();
	StopTime();

	if (KEYMANAGER->isOnceKeyDown(VK_DELETE) && !_playerB.die && !stopTime) castPrism();
	Prism();
	if (KEYMANAGER->isOnceKeyDown(VK_END) && !_playerB.die && !stopTime) castTimeRewind();
	TimeRewind();
	if (KEYMANAGER->isOnceKeyDown(VK_NEXT) && !_playerB.die && !stopTime) castConfuse();
	ConfuseShot();

}

void HomeWork::render(HDC hdc) {
#pragma region Brush
	HBRUSH redbrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH yellowbrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH greenbrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH purplebrush = CreateSolidBrush(RGB(128, 0, 128));
	HBRUSH skybluebrush = CreateSolidBrush(RGB(0, 255, 255));
	HBRUSH blackbrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH graybrush = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH lightgraybrush = CreateSolidBrush(RGB(220, 220, 220));
#pragma endregion



	if (stopTime) {
		Rectangle(hdc, _stopTimeEffect.left, _stopTimeEffect.top, _stopTimeEffect.right, _stopTimeEffect.bottom);
		FillRect(hdc, &_stopTimeEffect, lightgraybrush);
	}

#pragma region HealthBar
	Rectangle(hdc, _maxhealthA.left, _maxhealthA.top, _maxhealthA.right, _maxhealthA.bottom);
	Rectangle(hdc, _maxhealthB.left, _maxhealthB.top, _maxhealthB.right, _maxhealthB.bottom);

	Rectangle(hdc, _healthA.left, _healthA.top, _healthA.right, _healthA.bottom);
	if (_healthA.right - _healthA.left > 200) FillRect(hdc, &_healthA, greenbrush);
	else if (_healthA.right - _healthA.left > 100)  FillRect(hdc, &_healthA, yellowbrush);
	else  FillRect(hdc, &_healthA, redbrush);

	Rectangle(hdc, _healthB.left, _healthB.top, _healthB.right, _healthB.bottom);
	if (_healthB.right - _healthB.left > 200) FillRect(hdc, &_healthB, greenbrush);
	else if (_healthB.right - _healthB.left > 100)  FillRect(hdc, &_healthB, yellowbrush);
	else  FillRect(hdc, &_healthB, redbrush);
#pragma endregion

	//TimeRewind Skill
	if (_playerB.castTimeRewind) Rectangle(hdc, _playerB.prevRc.left, _playerB.prevRc.top, _playerB.prevRc.right, _playerB.prevRc.bottom);

#pragma region Player
	if (!_playerA.die) {
		Rectangle(hdc, _playerA.rc.left, _playerA.rc.top, _playerA.rc.right, _playerA.rc.bottom);
		if (AinvTime > 0) FillRect(hdc, &_playerA.rc, redbrush);
		else if (_playerA.confuse) FillRect(hdc, &_playerA.rc, purplebrush);
		else FillRect(hdc, &_playerA.rc, blackbrush);
	}
	if (!_playerB.die) {
		Rectangle(hdc, _playerB.rc.left, _playerB.rc.top, _playerB.rc.right, _playerB.rc.bottom);
		if (BinvTime > 0) FillRect(hdc, &_playerB.rc, redbrush);
		else FillRect(hdc, &_playerB.rc, graybrush);
	}
#pragma endregion

#pragma region Bullet
	//총알
	for (int i = 0; i < A_BULMAX; i++) {
		if (!_bulletA[i].fire) continue;
		Ellipse(hdc, _bulletA[i].rc.left, _bulletA[i].rc.top, _bulletA[i].rc.right, _bulletA[i].rc.bottom);
	}
	for (int i = 0; i < B_BULMAX; i++) {
		if (!_bulletB[i].fire) continue;
		Ellipse(hdc, _bulletB[i].rc.left, _bulletB[i].rc.top, _bulletB[i].rc.right, _bulletB[i].rc.bottom);
	}
#pragma endregion

	//스킬관련
	if (_hook.casting) {
		Ellipse(hdc, _hook.hookhead.left, _hook.hookhead.top, _hook.hookhead.right, _hook.hookhead.bottom);
		Rectangle(hdc, _hook.hookline.left, _hook.hookline.top, _hook.hookline.right, _hook.hookline.bottom);
	}

	if (_shield.casting) {
		Ellipse(hdc, _shield.rc.left, _shield.rc.top, _shield.rc.right, _shield.rc.bottom);
	}

	if (_cBullet.fire) {
		Ellipse(hdc, _cBullet.rc.left, _cBullet.rc.top, _cBullet.rc.right, _cBullet.rc.bottom);
	}

	if (_prism.casting) {
		Rectangle(hdc, _prism.rc.left, _prism.rc.top, _prism.rc.right, _prism.rc.bottom);
		FillRect(hdc, &_prism.rc, skybluebrush);
	}

#pragma region Comment
	char str1P_1[128]; 	char str1P_2[128]; char str1P_3[128]; char str1P_4[128];
	char str2P_1[128]; 	char str2P_2[128]; char str2P_3[128]; char str2P_4[128];
	wsprintf(str1P_1, "1P (WASD로 이동, LShift로 공격, ZXC로 스킬");
	wsprintf(str1P_2, "Z : 갈고리    X : 방어막   C : 타임스톱");
	wsprintf(str2P_1, "2P (방향키로 이동, RShift로 공격, Delete,End,PgDn으로 스킬");
	wsprintf(str2P_2, "Delete. 프리즘    End : 시간역행    PgDn : 혼란 탄환");

	TextOut(hdc, 0, 760, str1P_1, strlen(str1P_1));
	TextOut(hdc, 0, 780, str1P_2, strlen(str1P_2));
	TextOut(hdc, 390, 760, str2P_1, strlen(str2P_1));
	TextOut(hdc, 450, 780, str2P_2, strlen(str2P_2));
	
#pragma endregion
#pragma region KillBrush
	DeleteObject(redbrush);
	DeleteObject(yellowbrush);
	DeleteObject(greenbrush);
	DeleteObject(purplebrush);
	DeleteObject(blackbrush);
	DeleteObject(graybrush);
	DeleteObject(lightgraybrush);
	DeleteObject(skybluebrush);
#pragma endregion
}

void HomeWork::movePlayerA() {
	if (KEYMANAGER->isStayKeyDown('D')) {
		if (!_playerA.confuse) {
			if (_playerA.rc.right < WINSIZE_X) {
				_playerA.rc.left += PLAYERB_SPEED;
				_playerA.rc.right += PLAYERB_SPEED;
			}
		}
		else {
			if (_playerA.rc.left > 0) {
				_playerA.rc.left -= PLAYERB_SPEED;
				_playerA.rc.right -= PLAYERB_SPEED;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown('A')) {
		if (!_playerA.confuse) {
			if (_playerA.rc.left > 0) {
				_playerA.rc.left -= PLAYERB_SPEED;
				_playerA.rc.right -= PLAYERB_SPEED;
			}
		}
		else {
			if (_playerA.rc.right < WINSIZE_X) {
				_playerA.rc.left += PLAYERB_SPEED;
				_playerA.rc.right += PLAYERB_SPEED;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown('W')) {
		if (!_playerA.confuse) {
			if (_playerA.rc.top > 0) {
				_playerA.rc.top -= PLAYERB_SPEED;
				_playerA.rc.bottom -= PLAYERB_SPEED;
			}
		}
		else {
			if (_playerA.rc.bottom < WINSIZE_Y) {
				_playerA.rc.top += PLAYERB_SPEED;
				_playerA.rc.bottom += PLAYERB_SPEED;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown('S')) {
		if (!_playerA.confuse) {
			if (_playerA.rc.bottom < WINSIZE_Y) {
				_playerA.rc.top += PLAYERB_SPEED;
				_playerA.rc.bottom += PLAYERB_SPEED;
			}
		}
		else {
			if (_playerA.rc.top > 0) {
				_playerA.rc.top -= PLAYERB_SPEED;
				_playerA.rc.bottom -= PLAYERB_SPEED;
			}
		}
	}
}
void HomeWork::movePlayerB() {
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _playerB.rc.right) {
		_playerB.rc.left += PLAYERB_SPEED;
		_playerB.rc.right += PLAYERB_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && 0 < _playerB.rc.left) {
		_playerB.rc.left -= PLAYERB_SPEED;
		_playerB.rc.right -= PLAYERB_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && 150 < _playerB.rc.top) {
		_playerB.rc.top -= PLAYERB_SPEED;
		_playerB.rc.bottom -= PLAYERB_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && WINSIZE_Y > _playerB.rc.bottom) {
		_playerB.rc.top += PLAYERB_SPEED;
		_playerB.rc.bottom += PLAYERB_SPEED;
	}
}

void HomeWork::fireA() {
	for (int i = 0; i < A_BULMAX; i++) {
		if (_bulletA[i].fire) continue;
		_bulletA[i].fire = true;
		_bulletA[i].rc = RectMakeCenter(_playerA.rc.right, _playerA.rc.top + (_playerA.rc.bottom - _playerA.rc.top)/2, 10, 10);
		break;
	}
}
void HomeWork::fireB() {
	for (int i = 0; i < A_BULMAX; i++) {
		if (_bulletB[i].fire) continue;
		_bulletB[i].fire = true;
		_bulletB[i].rc = RectMakeCenter(_playerB.rc.left, _playerB.rc.top + (_playerB.rc.bottom - _playerB.rc.top) / 2, 10, 10);
		break;
	}
}

void HomeWork::castHook() {
	if (_hook.casting) return;
	_hook.casting = true;
	_hook.hookhead = { _playerA.rc.left + 40, _playerA.rc.top, _playerA.rc.right + 40, _playerA.rc.bottom };
	_hook.hookline = { _playerA.rc.right, _playerA.rc.top + 19, _hook.hookhead.left, _playerA.rc.bottom - 19 };
}
void HomeWork::Hook() {
	if (_hook.casting) {
		static int range = 0;

		if (RectInRect(_playerB.rc, _hook.hookhead)) {
			_hook.pull = true;
			_hook.grab = true;
		}
		_hook.hookhead.left = _playerA.rc.left + 40 + range;
		_hook.hookhead.right = _playerA.rc.right + 40 + range;
		_hook.hookhead.top = _playerA.rc.top;
		_hook.hookhead.bottom = _playerA.rc.bottom;

		_hook.hookline.left = _playerA.rc.right;
		_hook.hookline.right = _hook.hookhead.left;
		_hook.hookline.top = _playerA.rc.top + 19;
		_hook.hookline.bottom = _playerA.rc.bottom - 19;
		if (!_hook.pull) {
			range += 15;
			if (_hook.hookhead.right > WINSIZE_X) _hook.pull = true;
		}
		else {
			range -= 30;
			if (_hook.hookhead.left < _playerA.rc.right + 50) {
				_hook.pull = false;
				_hook.grab = false;
				_hook.casting = false;
			}
		}

		if (_hook.grab) {
			_playerB.rc.left = _hook.hookhead.left;
			_playerB.rc.right = _hook.hookhead.right;
			_playerB.rc.top = _hook.hookhead.top;
			_playerB.rc.bottom = _hook.hookhead.bottom;
		}

	}
}

void HomeWork::castShield() {
	if (_shield.casting) return;
	_shield.casting = true;
	_shield.castpos = { _playerA.rc.right, _playerA.rc.top + (_playerA.rc.bottom - _playerA.rc.top) / 2 };
	_shield.health = 100;
	_shield.rc.left = _shield.castpos.x;
	_shield.rc.right = _shield.castpos.x + 30;
	_shield.rc.top = _shield.castpos.y - 10;
	_shield.rc.bottom = _shield.castpos.y + 10;
}
void HomeWork::Shield() {
	if (_shield.casting && !stopTime) {
		if (_shield.rc.bottom - _shield.rc.top < 200) {
			_shield.rc.top -= 10;
			_shield.rc.bottom += 10;
		}
		if (_shield.rc.left < _shield.castpos.x + 100) {
			_shield.rc.left += 15;
			_shield.rc.right += 15;
		}
		else {
			_shield.rc.left += 1;
			_shield.rc.right += 1;
		}
		if (_shield.health <= 0) _shield.casting = false;
		else if (_shield.rc.left > WINSIZE_X - 200) _shield.casting = false;

	}
}

void HomeWork::castStopTime() {
	if (stopTime) return;
	stopTime = true;
	stopTime_timer = 150;
	_stopTimeEffect = { _playerA.rc.left, _playerA.rc.top, _playerA.rc.right, _playerA.rc.bottom };
}
void HomeWork::StopTime() {
	if (stopTime_timer > 0) stopTime_timer--;
	else stopTime = false;
	if (stopTime) {
		if (stopTime_timer < 10) {
			if (_stopTimeEffect.right - _stopTimeEffect.left >= 0) {
				_stopTimeEffect.right -= 50;
				_stopTimeEffect.left += 50;
				_stopTimeEffect.top += 50;
				_stopTimeEffect.bottom -= 50;
			}
		}
		else if (_stopTimeEffect.right - _stopTimeEffect.left < WINSIZE_X * 2) {
			_stopTimeEffect.right += 50;
			_stopTimeEffect.left -= 50;
			_stopTimeEffect.top -= 50;
			_stopTimeEffect.bottom += 50;
		}
	}
}

void HomeWork::castPrism() {
	if (_prism.casting) return;
	_prism.casting = true;
	_prism.rc.left = _playerB.rc.left - 100;
	_prism.rc.right = _prism.rc.left + 10;
	_prism.rc.top = _playerB.rc.top - 150;
	_prism.rc.bottom = _playerB.rc.bottom + 150;
	_prism.timer = 500;
}
void HomeWork::Prism() {
	if (!_prism.casting) return;
	_prism.timer--;
	if (_prism.timer == 0) _prism.casting = false;
}

void HomeWork::castTimeRewind() {
	if (!_playerB.castTimeRewind) {
		_playerB.prevRc = _playerB.rc;
		_playerB.prevHealth = _playerB.health;
		_playerB.castTimeRewind = true;
	}
	else {
		_playerB.rc = _playerB.prevRc;
		_playerB.health = _playerB.prevHealth;
		_playerB.castTimeRewind = false;
	}
}
void HomeWork::TimeRewind() {
	if (_playerB.castTimeRewind) _playerB.rewindTimer++;
	if (_playerB.rewindTimer > 500) {
		_playerB.castTimeRewind = false;
		_playerB.rewindTimer = 0;
	}
}

void HomeWork::castConfuse() {
	if (_cBullet.fire) return;
	_cBullet.rc = RectMakeCenter(_playerB.rc.left, _playerB.rc.top + (_playerB.rc.bottom - _playerB.rc.top) / 2, 18, 18);
	_cBullet.fire = true;
}
void HomeWork::ConfuseShot() {
	if (!_cBullet.fire) return;
	if (!stopTime) {
		_cBullet.rc.left -= 15;
		_cBullet.rc.right -= 15;
		if (PtInRect(&_playerA.rc, { _cBullet.rc.left, _cBullet.rc.top }) && !_playerA.die) {
			_playerA.confuse = true;
			_playerA.confuseTimer = 500;
			_cBullet.fire = false;
		}
		if (_cBullet.rc.right < 0) _cBullet.fire = false;
	}
}

bool HomeWork::RectInRect(RECT rc1, RECT rc2) {
	POINT pt1 = { rc2.left, rc2.top };
	POINT pt2 = { rc2.right, rc2.top };
	POINT pt3 = { rc2.left, rc2.bottom };
	POINT pt4 = { rc2.right, rc2.bottom };

	if (PtInRect(&rc1, pt1) || PtInRect(&rc1, pt2) || PtInRect(&rc1, pt3) || PtInRect(&rc1, pt4)) return true;
	else return false;
}