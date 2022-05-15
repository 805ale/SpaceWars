// Created by 18001218
// Provides a GameManager class, that is responsible for "services" such as the level number, score, lives, etc.

#include "GameManager.h"
#include "Spaceship.h"
#include "Particles.h"
#include "Asteroid.h"
#include "Background.h"
#include "EnemySpaceship.h"
#include "mydrawengine.h"
#include "gamecode.h"

const int NUM_SPACE_INVADERS = 5;			// number of enemy spaceships
const int NUM_ROWS = 3;						// number of rows
const int NUM_ASTEROIDS = 5;				// number of asteroids

// Constructor
GameManager::GameManager() : GameObject(ObjectType::LEVELMANAGER)
{
	levelNumber = 0;					// set level number - default is 0 
	score = 0;							// set score - default is 0
	respawnTimer = 3.0f;				// player respawn timer
	endLevelTimer = 5.0f;				// end of level timer
	lives = 3;							// set lives - default is 3
	pSoundFX = 0;						// soundFX functionality
	enemyCounter = 0;					
	playerActive = false;
}


// Start of level
void GameManager::StartLevel()
{
	// set background
	Background* pBackground = new Background();
	pBackground->Initialise(Vector2D(0,0));
	objectManager.Add(pBackground);

	// draw ship to the screen
	LoadImage(L"ship.bmp");

	// set level number, player score and player lives
	levelNumber = 1;
	score = 0;
	lives = 3;

	// particle system - will be triggered if player destroys enemy objects (asteroids and enemy spaceships)
	Particles* pParticles = new Particles();
	pParticles->Initialise();
	objectManager.Add(pParticles);

	// load sound effects
	pSoundFX = new SoundFX();
	pSoundFX->LoadSounds();

	// initialise spaceship
	Spaceship* pShip = new Spaceship();
	pShip->Initialise(Vector2D(0, -700), &objectManager, pSoundFX, &*this);
	objectManager.Add(pShip);
	playerActive = true;

	
	// arranges enemy spaceships into rows (there are 15 enemy spaceships, organised in 3 rows)
	for (int rows = 0; rows < NUM_ROWS; rows++)
	{
		for (int i = 0; i < NUM_SPACE_INVADERS; i++)
		{
			EnemySpaceship* pEnemy = new EnemySpaceship();
			Vector2D pos(float(-1300 + (300 * i)), float(850 - 250 * rows));
			Vector2D vel;
			vel.setBearing(1.57f, 100.0f);
			pEnemy->Initialise(pos, vel, 2.0f, &objectManager, pSoundFX, pParticles, &*this);
			objectManager.Add(pEnemy);
		}
	}
}

// Level 2
void GameManager::NextLevel()
{
	// go to the next level
	levelNumber++;
	// if the last level has been completed, go to level 2
	if (levelNumber == 2)
	{
		// add particles
		Particles* pParticles = new Particles();
		pParticles->Initialise();
		objectManager.Add(pParticles);

		// draw asteroids to the screen and make them move around
		for (int i = 0; i < NUM_ASTEROIDS; i++)
		{
			Asteroid* pAsteroid = new Asteroid();
			Vector2D pos;
			pos.setBearing(rand() % 600 / 100.0f, float(rand() % 600 + 800));
			Vector2D vel;
			vel.setBearing(rand() % 628 / 100.0f, float(rand() % 1000));
			pAsteroid->Initialise(pos, vel, 2.0f, &objectManager, pSoundFX, pParticles, &*this);
			objectManager.Add(pAsteroid);
		}
	}

	// end game 
	if (levelNumber == 3)
	{
		EndOfGame();
	}
}


void GameManager::Render()
{
	MyDrawEngine* pDraw = MyDrawEngine::GetInstance();
	pDraw->WriteText(Vector2D(-1750.0f, -880.0f), L"Level: ", MyDrawEngine::WHITE);
	pDraw->WriteInt(Vector2D(-1650.0f, -880.0f), levelNumber, MyDrawEngine::WHITE);

	pDraw->WriteText(Vector2D(-1750.0f, -820.0f), L"Score: ", MyDrawEngine::WHITE);
	pDraw->WriteInt(Vector2D(-1645.0f, -820.0f), score, MyDrawEngine::WHITE);

	pDraw->WriteText(Vector2D(1400.0f, -880.0f), L"Lives: ", MyDrawEngine::WHITE);
	for (int i = 0; i < lives; i++)
	{
		pDraw->DrawAt(Vector2D(float(1550 + 80 * i), -900.0f), image);
	}

}

// Update
void GameManager::Update(float frameTime)
{
	objectManager.UpdateAll(frameTime);
	objectManager.RenderAll();
	objectManager.CheckCollisions();
	objectManager.DeleteInactiveObjects();
	enemyCounter = objectManager.GetNumberOfEnemies();
	MyDrawEngine* pDraw = MyDrawEngine::GetInstance();

	// if player gets hit
	if (!playerActive)
	{
		if (lives)
		{
			// respawn player
			pDraw->WriteText(890, 400, L"Respawn in: ", MyDrawEngine::WHITE);
			pDraw->WriteInt(1000, 400, int(respawnTimer) + 1, MyDrawEngine::WHITE);
			respawnTimer -= frameTime;
			if (respawnTimer <= 0) {
				// respawn spaceship
				Spaceship* pShip = new Spaceship();
				pShip->Initialise(Vector2D(0, -700), &objectManager, pSoundFX, &*this);
				objectManager.Add(pShip);
				playerActive = true;
			}
		}
		else
		{
			EndOfGame();
		}
	}

	

	// if enemy spaceships are defeated
	if (enemyCounter <= 0)
	{
		// end level and prepare for the next one
		endLevelTimer -= frameTime;

		// if first level has been completed
		if (levelNumber == 1)
		{
			// draw text to the screen
			pDraw->WriteText(670, 500, L"Enemies defeated, dodge and shoot asteroids to win ", MyDrawEngine::WHITE);
		}
		
		// if second level has been completed
		if (levelNumber == 2)
		{
			// draw text to the screen
			pDraw->WriteText(850, 500, L"You win! ", MyDrawEngine::WHITE);
		}

		if (endLevelTimer <= 0)
		{
			NextLevel();
			endLevelTimer = 5.0f;
		}
	}
}

// Increment player score
void GameManager::AddScore(int s)
{
	score += s;
}


// Decrement player lives and respawn
void GameManager::PlayerDead()
{
	lives--;
	playerActive = false;
	respawnTimer = 3.0f;
}

IShape2D& GameManager::GetShape()
{
	return hitbox;
}

// No collision
void GameManager::ProcessColision(GameObject& other)
{
}

// No message
void GameManager::ProcessMessage(Message msg)
{
}

// No hitbox
void GameManager::DrawHitbox()
{
}

// End of game - delete objects
void GameManager::EndOfGame()
{
	objectManager.DeleteAll();

	delete pSoundFX;
	pSoundFX = nullptr;

	Game::instance.PlayerDead(score);
}

// Return lives left
int GameManager::GetLives()
{
	return lives;
}

// Return level number
int GameManager::GetLevelNumber()
{
	return levelNumber;
}

ObjectManager& GameManager::GetObjectManager()
{
	return objectManager;
}