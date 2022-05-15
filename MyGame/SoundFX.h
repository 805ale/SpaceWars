// Created by 18001218
// Provides a SoundFX class - load and play sound effects

#pragma once
#include "mysoundengine.h"

class SoundFX
{
private:
	// Variables
	static const int NUMEXPLOSIONS = 5;						// number of explosions
	int nextShipExplosion;									// keeps track of ship explosion
	int nextAsteroidExplosion;								// keeps track of asteroid explosion	
	SoundIndex ShipExplosions[NUMEXPLOSIONS];		
	SoundIndex AsteroidExplosions[NUMEXPLOSIONS];
	SoundIndex Thruster;									// ship engine sound effect
	SoundIndex Shoot;										// shooting sound effect
	SoundIndex EnemyShoot;									// enemy shooting sound effect

public:
	// Functions
	SoundFX();
	void LoadSounds();
	void PlayShoot();
	void PlayEnemyShoot();
	void PlayShipExplosion();
	void PlayAsteroidExplosion();
	void StartThruster();
	void StopThruster();
	void SetEngineVolume(int volume);
};

