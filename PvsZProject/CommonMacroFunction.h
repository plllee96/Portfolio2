#pragma once
inline POINT PointMake(int x, int y) {
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY) {
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height) {
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectangleMake(int x, int y, int width, int height) {
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height) {
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
	return rc;
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height) {
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height) {
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline RECT CollisionAreaResize(RECT &rcDest, int width, int height) {
	RECT rc = { rcDest.left + width / 2, rcDest.top + height / 2, rcDest.right - width / 2, rcDest.bottom + height / 2 };

	return rc;
}