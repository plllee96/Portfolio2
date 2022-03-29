#pragma once
#include "GameNode.h"
#include "PlantType.h"
#include "PlantManager.h"
#include "ZombieManager.h"
#include "BulletManager.h"
#include "Inventory.h"
#include "Deck.h"
#include "Sun.h"
#include "Tile.h"
#include "Progressbar.h"
#include "NumberImage.h"

enum class GameStatus {SETTING, PLAY, PAUSE, CLEAR};
enum class CursorSelect {NONE, PLANT, SHOVEL};

class GameScene : public GameNode {
private:
	//Image
	Image* _background;
	Image* _sunIcon;
	Image* _playGameButton;

	//Game Controller
	int _stageNum;
	float _stageTimer;
	vector<float> _stageWaveTimer;

	GameStatus _status;
	CursorSelect _cursor;
	RECT _camera;

	//Object & Class
	NumberImage* _sunNum;
	Progressbar* _progressbar; 

	Deck* _deck;
	Inventory* _inventory;

	Tile* _tile;
	PlantManager* _pm;
	ZombieManager* _zm;
	BulletManager* _bm;

	vector<Sun*> _vSun;
	vector<Sun*>::iterator _viSun;

	//Camera Variable
	float _cameraCount;
	float _cameraMoveRightDelay;
	float _cameraMoveLeftDelay;
	bool _cameraRight;
	bool _cameraLeft;
	float _cameraMoveSpeed;

	//Setting Variable
	float _startWaitCool;
	float _cameraSpeed;
	bool _ready;

	//Game Variable
	PlantType _selectedPlant;
	int _selectedPlantIndex;

	RECT _startbuttonRc;

	int _maxSlot;

	int _sun;
	float _sunCount;
	float _sunCooltime;
	float _sunNumX;
	float _sunNumY;

	float _zombieCount;
	float _zombieCooltime;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//Camera
	void moveCamera();

	//set, load
	void settingGame();
	void setStageNum(int stageNum) { _stageNum = stageNum; }
	void loadStage();
	void settingMouseControl();

	//play game
	void playGame();
	void mouseControl();
	void sunControl();
	void zombieControl();

	//render
	void printSelectedPlant();

	//debug
	string printPlantType(PlantType type);
};

