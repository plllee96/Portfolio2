#include "Stdafx.h"
#include "Animation.h"

Animation::Animation() :  
	_frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_frameNumWidth(0),
	_frameNumHeight(0),
	_frameUpdateSec(0.0f),
	_elapsedSec(0.0f),
	_isPlay(false),
	_loop(false)
{}

HRESULT Animation::init(int totalW, int totalH, int frameW, int frameH) {
	_frameWidth = frameW;
	_frameHeight = frameH;
	_frameNumWidth = totalW / _frameWidth;
	_frameNumHeight = totalH / _frameHeight;
	_frameNum = _frameNumWidth * _frameNumHeight;

	_frameList.clear();
	for (int i = 0; i < _frameNumHeight; i++) {
		for (int j = 0; j < _frameNumWidth; j++) {
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	setDefPlayFrame();
	return S_OK;
}

void Animation::release() {
	//# Do Nothing
}

void Animation::setDefPlayFrame(bool reverse, bool loop) {
	_loop = loop;
	_playList.clear();
	if (reverse) {
		if (_loop) {
			for (int i = 0; i < _frameNum; i++) {
				_playList.push_back(i);
			}
			for (int i = _frameNum - 2; i > 0; i--) {
				_playList.push_back(i);
			}
		}
		else {
			for (int i = 0; i < _frameNum; i++) {
				_playList.push_back(i);
			}
			for (int i = _frameNum - 2; i >= 0; i--) {
				_playList.push_back(i);
			}
		}
	}
	else {
		for (int i = 0; i < _frameNum; i++) {
			_playList.push_back(i);
		}
	}
}

void Animation::setPlayFrame(int * playArr, int arrLen, bool loop) {
	_loop = loop;
	_playList.clear();
	for (int i = 0; i < arrLen; i++) {
		_playList.push_back(playArr[i]);
	}
}

void Animation::setPlayFrame(int start, int end, bool reverse, bool loop) {
	_loop = loop;
	_playList.clear();
	if (reverse) {
		if (_loop) {
			for (int i = start; i <= end; i++) {
				_playList.push_back(i);		
			}
			for (int i = end - 1; i > start; i--) {
				_playList.push_back(i);
			}
		}
		else {
			for (int i = start; i <= end; i++) {
				_playList.push_back(i);
			}
			for (int i = end - 1; i >= start; i--) {
				_playList.push_back(i);
			}
		}
	}
	else {
		for (int i = start; i <= end; i++) {
			_playList.push_back(i);
		}
	}
}

void Animation::setFPS(int framePerSec) {
	_frameUpdateSec = 1.0f / (float)framePerSec;
}

void Animation::frameUpdate(float elapsedTime) {
	if (_isPlay) {
		_elapsedSec += elapsedTime;
		if (_elapsedSec >= _frameUpdateSec) {
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size()) {
				if (_loop) {
					_nowPlayIdx = 0;
				}
				else {
					_nowPlayIdx--;
					_isPlay = false;
				}
			}
		}
	}
}

void Animation::AniStart() {
	_isPlay = true;
	_nowPlayIdx = 0;
}

void Animation::AniStop() {
	_isPlay = false;
	_nowPlayIdx = 0;
}

void Animation::AniPause() {
	_isPlay = false;
}

void Animation::AniResume() {
	_isPlay = true;
}

