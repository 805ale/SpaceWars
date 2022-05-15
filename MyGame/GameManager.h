// Created by 18001218
// Provides a GameManager class, that is responsible for "services" such as the level number, score, lives, etc.

#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"

class GameManager: public GameObject
{
private:
	// Variables
	int levelNumber;						// level manager - keeps track of level number
	int score;								// score - report scores
	float respawnTimer;						// player respawn timer
	float endLevelTimer;					// end of level timer
	int enemyCounter;						// enemy counter
	int lives;								// keeps track of lives left
	bool playerActive;						// tracks if player is active
	ObjectManager objectManager;			// object manager
	SoundFX* pSoundFX;						// pointer to the soundFX class
	Point2D hitbox;							// hitbox
	
public:
	// Functions
	GameManager();
	void StartLevel();
	void NextLevel();
	void Render();
	int GetLevelNumber();
	void Update(float frameTime);
	void AddScore(int s);
	void PlayerDead();
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void ProcessMessage(Message msg);
	void DrawHitbox();
	void EndOfGame();
	int GetLives();
	ObjectManager& GetObjectManager();
};

