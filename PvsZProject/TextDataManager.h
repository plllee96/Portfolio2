#pragma once
#include "SingletonBase.h"

#define SAVE_BUFFER 128
#define LOAD_BUFFER 128

class TextDataManager : public SingletonBase<TextDataManager> {
public:
	HRESULT init();
	void release();
	
	void save(const char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	vector<string> load(const char* fileName);
	vector<string> charArraySeperation(char charArray[]);

	TextDataManager() {}
	~TextDataManager() {}
};

