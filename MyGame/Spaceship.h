// Created by 18001218
// Spaceship class 

#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
#include "GameManager.h"

class Spaceship: public GameObject
{
private:
	// Variables
	Vector2D velocity;						// player velocity
	ObjectManager* pObjectManager;			// pointer to object manager
	GameManager* pGameManager;				// pointer to game manager
	SoundFX* pSoundFX;						// pointer to soundfx handler
	int health;								// health tracker
	int ammo;								// ammo tracker
	float shootTimer;						// shoot timer - to avoid bullet spam
	float invulnerableTimer;				// invulnerable timer - player is invulnerable after respawning
	Circle2D hitbox;						// hitbox
public:
	// Functions
	Spaceship();
	void Initialise(Vector2D startPosition, ObjectManager* pOM, SoundFX* pSFX, GameManager* pGameManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};

