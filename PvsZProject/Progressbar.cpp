#include "Stdafx.h"
#include "Progressbar.h"

HRESULT Progressbar::init(float maxTime, vector<float> flagTime) {
	_frameImage = IMAGEMANAGER->addImage("Progress", "Resources/Images/Objects/Progress.bmp", 233, 19, true, RGB(255, 0, 255));
	_gaugeImage = IMAGEMANAGER->addImage("Progressbar", "Resources/Images/Objects/Progressbar.bmp", 221, 7, false, RGB(255, 0, 255));
	_gaugeHeadImage = IMAGEMANAGER->addImage("ProgressHead", "Resources/Images/Objects/ProgressHead.bmp", 15, 17, true, RGB(255, 0, 255));
	_flagImage = IMAGEMANAGER->addImage("ProgressFlag", "Resources/Images/Objects/ProgressFlag.bmp", 18, 19, true, RGB(255, 0, 255));

	_maxTime = maxTime;
	for (int i = 0; i < flagTime.size(); i++) {
		pair<float, bool> temp = make_pair(flagTime[i], false);
		_flagTime.push_back(temp);
	}
	_startTime = _currentTime = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void Progressbar::release(void) {
}

void Progressbar::update(void) {
	if (isEndWave()) return;
	isHugeWaveTime();
	_currentTime = TIMEMANAGER->getWorldTime();

	_gaugeWidth = _gaugeImage->getWidth() * ((_currentTime - _startTime) / _maxTime);
	if (_gaugeWidth > _gaugeImage->getWidth()) _gaugeImage->getWidth();	
}

void Progressbar::render(void) {
	_frameImage->render(getMemDC(), barX, barY);
	_gaugeImage->render(getMemDC(), barX + 6 + _gaugeImage->getWidth() - _gaugeWidth, barY + 6, 0, 0, _gaugeWidth, _gaugeImage->getHeight());
	for (flagInfo iter : _flagTime) {
		float flagX = _gaugeImage->getWidth() - (_gaugeImage->getWidth() * (iter.first / _maxTime));
		_flagImage->render(getMemDC(), barX + flagX + 6, barY - 5);
	}
	_gaugeHeadImage->render(getMemDC(), barX + _gaugeImage->getWidth() - _gaugeWidth, barY);
}

bool Progressbar::isHugeWaveTime() {
	for (int i = 0; i < _flagTime.size(); i++) {
		if (_currentTime > _startTime + _flagTime[i].first && !_flagTime[i].second) {
			_flagTime[i].second = true;
			return true;
		}
		else continue;
	}
	return false;
}

bool Progressbar::isEndWave() {
	if (_currentTime >= _startTime + _maxTime) return true;
	else return false;
}
