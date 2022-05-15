// Created by 18001218
// Provides a SoundFX class - load and play sound effects

#include "SoundFX.h"

// Constructor
SoundFX::SoundFX()
{
	nextShipExplosion = 0;
	nextAsteroidExplosion = 0;
	ShipExplosions[0]=0;
	AsteroidExplosions[0]=0;
	Thruster = 0;
	Shoot = 0;
	EnemyShoot = 0;
}

// Load sounds
void SoundFX::LoadSounds()
{
	nextShipExplosion = 0;
	nextAsteroidExplosion = 0;

	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
	// player shoot sound effect
	Shoot = pSoundEngine->LoadWav(L"shoot.wav");
	// enemy shoot sound effect
	EnemyShoot = pSoundEngine->LoadWav(L"shot2.wav");
	// engine sound effect
	Thruster = pSoundEngine->LoadWav(L"engineloop.wav");
	
	// ship explosion sound effect
	for(int i=0;i<NUMEXPLOSIONS; i++)
		ShipExplosions[i] = pSoundEngine->LoadWav(L"explosion2.wav");
	
	// asteroid explosion sound effect
	for (int i = 0; i < NUMEXPLOSIONS; i++)
		AsteroidExplosions[i] = pSoundEngine->LoadWav(L"explosion3.wav");
}

// Play ship sound effect
void SoundFX::PlayShoot()
{
	MySoundEngine::GetInstance()->Play(Shoot);
}

// Play enemy shoot sound effect
void SoundFX::PlayEnemyShoot()
{
	MySoundEngine::GetInstance()->Play(EnemyShoot);
}


// Play ship explosion sound effect
void SoundFX::PlayShipExplosion()
{
	MySoundEngine::GetInstance()->Play(ShipExplosions[nextShipExplosion]);
	nextShipExplosion++;
	if (nextShipExplosion >= NUMEXPLOSIONS)
		nextShipExplosion = 0;
}

// Play asteroid explosion sound effect
void SoundFX::PlayAsteroidExplosion()
{
	MySoundEngine::GetInstance()->Play(AsteroidExplosions[nextAsteroidExplosion]);
	nextAsteroidExplosion++;
	if (nextAsteroidExplosion >= NUMEXPLOSIONS)
		nextAsteroidExplosion = 0;
}
 
// Play engine loop sound effect - when ship moves
void SoundFX::StartThruster()
{
	MySoundEngine::GetInstance()->Play(Thruster, true);
}

// Stop engine loop sound effect - when ship is not moving
void SoundFX::StopThruster()
{
	MySoundEngine::GetInstance()->Stop(Thruster);
}

// Set volume
void SoundFX::SetEngineVolume(int volume)
{
	volume = (volume - 100) * 35;
	MySoundEngine::GetInstance()->SetVolume(Thruster, volume);
}
