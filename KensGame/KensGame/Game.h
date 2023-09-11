#pragma once

#include<map>
#include<sstream>
#include <fstream>
#include <algorithm>

#include "Player.h"
#include "World.h"
#include "Enemy.h"
#include "bullet.h"
#include "Item.h"

class Game
{
private:
	//name and frame
	sf::Font THfont;
	sf::RectangleShape nameBar;
	sf::Text nameText;
	sf::Texture frameTexture;
	sf::Sprite frame;
	void nameTextBar();

	//window
	sf::RenderWindow* window;
	void initWindow();
	void initSound();
	bool menu = true;
	bool play = false;
	bool holdESC = false;
	bool pause;
	bool leaderboard = false;
	bool gamerOver = false;

	//menu
	void initMenu();
	void updateMenu();
	void renderMenu();

	sf::Font Westernfont;
	sf::Sprite menuPlay;
	sf::Texture menuPlayTexture;
	sf::Sprite menuLeaderboard;
	sf::Texture menuLeaderboardTexture;
	sf::Sprite menuExit;
	sf::Texture menuExitTexture;
	sf::Sprite menuBG;
	sf::Texture menuBGTexture;

	//pause
	bool surrender;
	sf::Sprite pauseSpirte;
	sf::Texture pauseTexture;
	sf::Sprite resume;
	sf::Texture resumeTexture;
	sf::Sprite pauseBack;
	sf::Texture pauseBackTexture;

	void initPause();
	void updatePause();
	void renderPause();

	//gameOver
	sf::Sprite gameOverBG;
	sf::Texture gameOverBGTexture;
	sf::Sprite mainmenu;
	sf::Texture mainmenuTexture;
	sf::Sprite gameOverExit;
	sf::Texture gameOverExitTexture;
	sf::Sprite gameOverSave;
	sf::Texture gameOverSaveTexture;
	std::stringstream ssScore;
	sf::Text gameOverScore;
	sf::Text nameShow;
	sf::Event event;
	std::string saveName;
	int mark;

	void gameEnd();
	void initgameOver();
	void updategameOver();
	void rendergameOver();

	//leaderboard
	sf::Sprite boardBG;
	sf::Texture boardBGTexture;
	sf::Sprite backButton;
	sf::Texture backButtonTexture;
	sf::Text boardH;
	sf::Text leadersScore[10];
	std::stringstream ssleaderScore;

	void sorting();
	void initboard();
	void updateboard();
	void renderboard();

	//playmap
	World* world;

	//playGUI
	sf::Text scoreText;
	sf::Sprite scoreSpirte;
	sf::Texture scoreTexture;

	sf::Text lifeText;
	sf::Sprite lifeSpirte;
	sf::Texture lifeTexture;

	sf::Sprite itemGUISprite;
	sf::Texture itemGUITexture;

	sf::Texture itemSpriteTexture;
	sf::Texture itemEmptyTexture;
	sf::Sprite itemSprite;

	sf::Sprite Instruction;
	sf::Texture InstructionTexture;

	//playSystem
	unsigned life;
	unsigned score;
	int itemNow;
	int itemUsing;
	sf::Clock itemDuration;

	//player Enemies Bullets Items
	Player* player;
	sf::Clock spawnTimer;
	float timeMax;
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	std::vector<Item*> items;

	//playfunction
	void initPlay();
	void initWorldAndSystem();
	void initplayGUI();
	void initPlayer();
	void initEnemies();

	//sounds
	sf::SoundBuffer BGMBuffer;
	sf::Sound BGM;
	sf::SoundBuffer hitBuffer;
	sf::Sound hitS;
	sf::SoundBuffer badgeBuffer;
	sf::Sound badgeS;
	sf::SoundBuffer bootBuffer;
	sf::Sound bootS;
	sf::SoundBuffer hitedBuffer;
	sf::Sound hitedS;
	sf::SoundBuffer lifeBuffer;
	sf::Sound lifeS;
	sf::SoundBuffer nukeBuffer;
	sf::Sound nukeS;
	sf::SoundBuffer shotgunBuffer;
	sf::Sound shotgunS;

public:
	Game();
	virtual ~Game();

	void run();

	//play
	void updateGUI();
	void updateMoveInput();
	void combatInput();
	void updatePlay();
	void updateEnemies();
	void updatebullets();
	void updateCombat();
	void updateItems();
	void updateItemBuff();
	void nukeAll();
	void buffByItem();

	void renderPlay();
	void renderGUI();

};

