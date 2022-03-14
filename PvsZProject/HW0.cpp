#include "Stdafx.h"
#include "HW0.h"

HRESULT HW0::init(void) {

	return S_OK;
}

void HW0::release(void) {
}

void HW0::update(void) {
}

void HW0::render(void) {
	char strLec1[128];
	char strLec2[128];
	char strLec3[128];
	char strLec4[128];
	char strLec5[128];
	char strLec6[128];
	wsprintf(strLec1, "[1] 강의 22.02.04");
	wsprintf(strLec2, "[2] 과제1. 리듬게임");
	wsprintf(strLec3, "[3] 과제");
	wsprintf(strLec4, "[4] 강의");
	wsprintf(strLec5, "[5] 과제.");
	wsprintf(strLec6, "[6] 과제.");
	TextOut(getMemDC(), 300, 300, strLec1, strlen(strLec1));
	TextOut(getMemDC(), 300, 320, strLec2, strlen(strLec2));
	TextOut(getMemDC(), 300, 340, strLec3, strlen(strLec3));
	TextOut(getMemDC(), 300, 370, strLec4, strlen(strLec4));
	TextOut(getMemDC(), 300, 390, strLec5, strlen(strLec5));
	TextOut(getMemDC(), 300, 410, strLec6, strlen(strLec6));
}
