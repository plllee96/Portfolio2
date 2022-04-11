#pragma once
#include "GameNode.h"
#include "PlantType.h"
#include "PlantManager.h"
#include "ZombieManager.h"
#include "ZombieList.h"
#include "BulletManager.h"
#include "Belt.h"
#include "Tile.h"
#include "Reward.h"
#include "Progressbar.h"

enum class MinigameStatus {READY, PLAY};
enum class MinigameCursorSelect {NONE, PLANT};

class MinigameScene : public GameNode {
private:
	Image* _background;
	Image* _blackChanger;
	Image* _selectedPlantIcon;
	Image* _readyLetter;
	Image* _waveLetter;

	Tile* _tile;
	PlantManager* _pm;
	BulletManager* _bm;
	ZombieManager* _zm;
	ZombieList* _zl;
	Progressbar* _progressbar;
	Belt* _belt;
	Reward* _reward;

	RECT _camera;

	//Variable 
	MinigameStatus _status;
	MinigameCursorSelect _cursor;

	int _blackAlpha;
	bool _goingClear;

	//Camera Variable
	float _cameraCount;
	float _cameraMoveRightDelay;
	float _cameraMoveLeftDelay;
	bool _cameraRight;
	bool _cameraLeft;
	float _cameraMoveSpeed;

	//Event Variable
	bool _readyTextShow;
	bool _waveTextShow;
	float _readyTime;
	float _readyCount;
	int _readyFrame;

	//Play Game Variable
	float _stageTimer;
	vector<float> _stageWaveTimer;

	PlantType _selectedPlant;
	int _selectedPlantIndex;

	float _zombieCount;
	vector<int> _zombieType;
	float _zombieCooltime;
	
	float _beltCount;
	float _beltCooltime;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//update setting
	void updateReady();
	void sceneControl();
	void sceneChangerControl();
	void cameraControl();
	void updateReadyText();

	//update play
	void updatePlay();
	void mouseControl();
	void zombieControl();
	void beltControl();

	//render
	void printReady();
	void printPlay();

	//Sound
	void stopAllSound();
};

