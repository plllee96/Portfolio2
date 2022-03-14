#pragma once

class Animation;

class Image {
public:
	enum IMAGE_LOAD_IKIND {LOAD_RESOURCE = 0,
	LOAD_FILE, LOAD_EMPTY, LOAD_END};
	
	typedef struct tagImage {
		DWORD		resID;	
		HDC			hMemDC;		
		HBITMAP	hBit;				
		HBITMAP	hOBit;				
		float			x;
		float			y;
		int				width;
		int				height;
		int				currentFrameX;
		int				currentFrameY;
		int				maxFrameX;
		int				maxFrameY;
		int				frameWidth;
		int				frameHeight;
		BYTE			loadType;

		tagImage() {	resID = 0; hMemDC = NULL; hBit = NULL; hOBit = NULL;
		x = 0; y = 0;  width = 0; height = 0; currentFrameX = 0; currentFrameY = 0;
		maxFrameX = 0; maxFrameY = 0; frameWidth = 0; frameHeight = 0;
		loadType = LOAD_RESOURCE;	}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	CHAR*			_fileName;
	BOOL				_isTrans;			
	COLORREF		_transColor;		

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO		_blendImage;


public:
	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height,BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend(void);

	void setTransColor(BOOL isTrans, COLORREF transColor);
	void release(void);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight); //Å¬¸®ÇÎ render

	void resizeRender(HDC hdc, int destX, int destY, int width, int height);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, Animation* ani);

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
	inline float getX() { return _imageInfo->x; }
	inline float getY() { return _imageInfo->y; }
	inline void setX(float x) { _imageInfo->x = x; }
	inline void setY(float y) { _imageInfo->y = y; }
	inline void setCenter(float x, float y) {_imageInfo->x = x - (_imageInfo->width / 2); _imageInfo->y = y - (_imageInfo->height / 2); }
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }
	
	inline RECT boundingBox() {
		RECT rc{(int) _imageInfo->x, (int)_imageInfo->y, (int)_imageInfo->x + _imageInfo->width, (int)_imageInfo->y + _imageInfo->height };
		return rc;
	}
	inline RECT boundingBoxWithFrame() {
		RECT rc{ (int)_imageInfo->x, (int)_imageInfo->y, (int)_imageInfo->x + _imageInfo->width, (int)_imageInfo->y + _imageInfo->height };
		return rc;
	}

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameX(int frameX) {
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	inline void setFrameY(int frameY) {
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }
	Image();
	~Image() {}

};

