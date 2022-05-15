// Created by 18001218
// Provides an Asteroid class

#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "SoundFX.h"
#include "Particles.h"

class Asteroid : public GameObject
{
private:
	// Variables
	int health;								// asteroid health			
	Vector2D velocity;						// asteroid velocity
	Circle2D hitbox;						// asteroid hitbox
	ObjectManager* pObjectManager;			// pointer to ObjectManager class
	GameManager* pGameManager;				// pointer to GameManager class
	SoundFX* pSoundFX;						// pointer to SoundFX class
	Particles* pParticleSystem;				// pointer to ParticleSystem class

public:
	// Functions
	Asteroid();					
	void Initialise(Vector2D startPosition, Vector2D startVelocity, float startSize, ObjectManager* pOM, SoundFX* pSFX, Particles* pPart, GameManager* pGameManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};
