#pragma once

class Animation {
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

private:
	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameNum;
	int _frameWidth;
	int _frameHeight;
	int _frameNumWidth;
	int _frameNumHeight;

	float _frameUpdateSec;
	float _elapsedSec;

	bool _isPlay;
	bool _loop;
	DWORD _nowPlayIdx;

public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	void setDefPlayFrame(bool reverse = false, bool loop = false);
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0, bool loop = false);
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);

	void setFPS(int framePerSec);
	void frameUpdate(float elapsedTime);

	void AniStart();
	void AniStop();
	void AniPause();
	void AniResume();
	
	inline bool isPlay() { return _isPlay; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIdx]]; }
	inline int getFrameIdx() {
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }
	inline DWORD getNowPlayIndex() { return _nowPlayIdx; }



	Animation();
	~Animation() {}
};

