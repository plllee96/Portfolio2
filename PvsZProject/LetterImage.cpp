#include "Stdafx.h"
#include "LetterImage.h"

HRESULT LetterImage::init(DWORD length, CHAR* letter) {
	_letterImage = IMAGEMANAGER->addFrameImage("LetterImage", "Resources/Images/Objects/UpperAlphabet.bmp", 520, 30, 26, 1, true, RGB(255, 0, 255));
	_numberImage = IMAGEMANAGER->addFrameImage("NumberImage", "Resources/Images/Objects/CharNumber.bmp", 200, 30, 10, 1, true, RGB(255, 0, 255));
	_length = length;
	_letter = letter;
	
	return S_OK;
}

void LetterImage::release() {
}

void LetterImage::update() {
}

void LetterImage::render(int x, int y) {
	int index = 0;
	int tempX = x;
	while (_letter[index] != '\0') {
		bool isNumber = static_cast<int>(_letter[index]) >= 48 && static_cast<int>(_letter[index]) <= 57;
		bool isUpperAlphabet = static_cast<int>(_letter[index]) >= 65 && static_cast<int>(_letter[index]) <= 90;
		bool isLowerAlphabet = static_cast<int>(_letter[index]) >= 97 && static_cast<int>(_letter[index]) <= 122;

		if (isNumber) printNumber(static_cast<int>(_letter[index]) - 48, x + index * 17, y);
		else if (isUpperAlphabet) printLetter(static_cast<int>(_letter[index]) - 65, x + index * 17, y);
		else if (isLowerAlphabet) printLetter(static_cast<int>(_letter[index]) - 97, x + index * 17, y);

		index++;
	}
}

void LetterImage::printLetter(int letter, int x, int y) {
	_letterImage->frameRender(getMemDC(), x, y, letter, 0);
}

void LetterImage::printNumber(int number, int x, int y) {
	_numberImage->frameRender(getMemDC(), x, y, number, 0);
}
