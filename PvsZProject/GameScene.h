#pragma once
#include "GameNode.h"
#include "PlantType.h"
#include "PlantManager.h"
#include "ZombieList.h"
#include "ZombieManager.h"
#include "BulletManager.h"
#include "Inventory.h"
#include "Deck.h"
#include "Sun.h"
#include "Tile.h"
#include "Progressbar.h"
#include "NumberImage.h"
#include "Reward.h"

enum class GameStatus {SETTING, PLAY, PAUSE, CLEAR};
enum class CursorSelect {NONE, PLANT, SHOVEL};

class GameScene : public GameNode {
private:
	//Image
	Image* _background;
	Image* _sunIcon;
	Image* _playGameButton;
	Image* _shopButton;
	Image* _selectedPlantIcon;
	Image* _readyLetter;
	Image* _waveLetter;


	//Game Controller
	int _money;
	int _stageNum;
	float _stageTimer;
	vector<float> _stageWaveTimer;

	GameStatus _status;
	CursorSelect _cursor;
	RECT _camera;

	//Object & Class
	NumberImage* _sunNum;
	Progressbar* _progressbar; 
	Reward* _reward;

	Deck* _deck;
	Inventory* _inventory;

	Tile* _tile;
	PlantManager* _pm;
	ZombieManager* _zm;
	ZombieList* _zl;
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

	//Effect Variable
	bool _readyTextShow;
	float _readyTime;
	float _readyCount;
	int _readyFrame;

	bool _waveTextShow;

	//Setting Variable
	float _startWaitCool;
	float _cameraSpeed;
	bool _ready;

	//Game Variable
	PlantType _selectedPlant;
	int _selectedPlantIndex;

	RECT _startbuttonRc;
	RECT _shopbuttonRc;

	int _maxSlot;

	int _sun;
	float _sunCount;
	float _sunCooltime;
	float _sunNumX;
	float _sunNumY;

	vector<int> _zombieType;
	float _zombieCount;
	float _zombieCooltime;

	//sceneChange
	Image* _whiteChanger;
	Image* _blackChanger;
	int _whiteAlpha;
	int _blackAlpha;

	bool _goingToClear;	//Active SceneChanger when true
	bool _goingToShop;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//Camera & Scene
	void moveCamera();
	void sceneChangerControl();

	//set, load
	void settingGame();
	void setStageNum(int stageNum) { _stageNum = stageNum; }
	void loadStage();
	void settingMouseControl();
	void updateReadyText();

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

