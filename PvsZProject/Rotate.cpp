#include "Stdafx.h"
#include "Rotate.h"

HRESULT Rotate::init(void) {
	rotation = 0;
	distance = 50;
	diagAngle = 60;
	_rrc.center = { 400, 400 };
	_rrc.head = { (long)(center.x + cos(rotation * PI / 180) * distance) , (long)(center.y + sin(rotation * PI / 180) * distance) };
	_rrc.head2 = { 0, 0 };
	_rrc.speed = 5;
	return S_OK;
}

void Rotate::release(void) {
}

void Rotate::update(void) {

	_rrc.head.x = _rrc.center.x + cos((rotation - diagAngle / 2) * PI / 180) * distance;
	_rrc.head.y = _rrc.center.y + sin((rotation - diagAngle / 2) * PI / 180) * distance;
	_rrc.head2.x = _rrc.center.x + cos((rotation+diagAngle/2) * PI / 180) * distance;
	_rrc.head2.y = _rrc.center.y + sin((rotation+ diagAngle/2) * PI / 180) * distance;
	_rrc.head3.x = _rrc.center.x + cos((rotation + 180 - diagAngle / 2) * PI / 180) * distance;
	_rrc.head3.y = _rrc.center.y + sin((rotation + 180 - diagAngle / 2) * PI / 180) * distance;
	_rrc.head4.x = _rrc.center.x + cos((rotation + 180 + diagAngle/2) * PI / 180) * distance;
	_rrc.head4.y = _rrc.center.y + sin((rotation + 180 + diagAngle/2) * PI / 180) * distance;

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) rotation+= 3;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) rotation-= 3;
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		_rrc = MoveRotatingRect(_rrc, rotation, _rrc.speed);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		_rrc = MoveRotatingRect(_rrc, rotation, -_rrc.speed);
	}
}

void Rotate::render(HDC hdc) {
	char str[128];
	char strComment[128];
	wsprintf(strComment, "좌우 방향키로 회전, 상하 방향키로 앞뒤 이동");
	wsprintf(str, "X : %d, Y : %d  Rotation : %d", _rrc.head.x, _rrc.head.y, rotation);
	TextOut(hdc, 0, 50, strComment, strlen(strComment));
	TextOut(hdc, 0, 70, str, strlen(str));

	PrintRotatingRect(hdc, _rrc);
}

void Rotate::PrintRotatingRect(HDC hdc, RotateRect rrc) {
	MoveToEx(hdc, rrc.head.x, rrc.head.y, NULL);
	LineTo(hdc, rrc.head2.x, rrc.head2.y);
	LineTo(hdc, rrc.head3.x, rrc.head3.y);
	LineTo(hdc, rrc.head4.x, rrc.head4.y);
	LineTo(hdc, rrc.head.x, rrc.head.y);
}

RotateRect Rotate::MoveRotatingRect(RotateRect rrc, int rotation, int speed) {
	int movex = cos(rotation * PI / 180) * speed;
	int movey = sin(rotation * PI / 180) * speed;
	rrc.center.x += movex;
	rrc.head.x += movex;
	rrc.head2.x += movex;
	rrc.head3.x += movex;
	rrc.head4.x += movex;

	rrc.center.y += movey;
	rrc.head.y += movey;
	rrc.head2.y += movey;
	rrc.head3.y += movey;
	rrc.head4.y += movey;

	return rrc;
}

