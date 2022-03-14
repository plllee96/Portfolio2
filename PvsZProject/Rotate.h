#pragma once

#define PI 3.14159

struct RotateRect {
	int speed;
	POINT center;
	POINT head;
	POINT head2;
	POINT head3;
	POINT head4;
};
class Rotate {
private:
	POINT center;
	POINT head;
	POINT head2;
	POINT head3;
	POINT head4;

	int diagAngle;
	int rotation;
	int distance;

	RotateRect _rrc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	Rotate() {}
	~Rotate() {}

	void PrintRotatingRect(HDC hdc, RotateRect rrc);
	RotateRect MoveRotatingRect(RotateRect rrc, int rotation, int speed);
};

