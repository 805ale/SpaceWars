// Created by 18001218
// Provides an EnemySpaceship class
// Enemy spaceships can be destroyed and the player will be awarded points

#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "SoundFX.h"
#include "Particles.h"

class EnemySpaceship : public GameObject
{
private:
	// Variables
	int health;									// health - default is 100
	Vector2D velocity;							// velocity 
	Circle2D hitbox;							// hitbox - circle collision
	ObjectManager* pObjectManager;				// pointer to ObjectManager class
	GameManager* pGameManager;					// pointer to GameManager class
	SoundFX* pSoundFX;							// pointer to SoundFX class
	Particles* pParticleSystem;					// pointer to ParticleSystem class
	float shootTimer;							// interval between enemy spaceship shots
	float downTimer;							// interval between enemy spaceship rest time

public:
	// Functions
	EnemySpaceship();
	void Initialise(Vector2D startPosition, Vector2D startVelocity, float startSize, ObjectManager* pOM, SoundFX* pSFX, Particles* pPart, GameManager* pGameManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};