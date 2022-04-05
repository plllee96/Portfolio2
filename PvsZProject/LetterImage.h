#pragma once
#include "GameNode.h"
class LetterImage : public GameNode {
private:
	Image* _letterImage;
	Image* _numberImage;
	DWORD _length;
	CHAR* _letter;
public:
	HRESULT init(DWORD length, CHAR* letter);
	void release();
	void update();
	void render(int x, int y);

	void printLetter(int letter, int x, int y);
	void printNumber(int number, int x, int y);
};

