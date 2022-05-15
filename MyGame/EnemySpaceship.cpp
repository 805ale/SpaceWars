// Created by 18001218
// Provides an EnemySpaceship class
// Enemy spaceships can be destroyed and the player will be awarded points

#include "EnemySpaceship.h"
#include "gamecode.h"
#include "Laser.h"
#include "Explosion.h"

const float TURN_SPEED = 0.02f;

// Constructor
EnemySpaceship::EnemySpaceship() : GameObject(ObjectType::ENEMY_SHIP)
{
	isActive = true;
	health = 100;
	transparency = 0.1f;
	size = 3.0f;
	angle = 0;
	image = -1;
	pObjectManager = 0;
	pSoundFX = 0;
	pParticleSystem = 0;
	pGameManager = 0;
	shootTimer = 3.0f;
	recieveMessages = true;
	downTimer = 2.0f;
}

// Initialise enemy spaceship
void EnemySpaceship::Initialise(Vector2D startPosition, Vector2D startVelocity, float startSize, ObjectManager* pOM, SoundFX* pSFX, Particles* pPart, GameManager* pGM)
{
	LoadImage(L"enemy.bmp");
	pObjectManager = pOM;
	pSoundFX = pSFX;
	pParticleSystem = pPart;
	position = startPosition;
	velocity = startVelocity;
	pGameManager = pGM;
}

// Update 
void EnemySpaceship::Update(float frameTime)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();

	Rectangle2D screen = MyDrawEngine::GetInstance()->GetViewport();

	// enemy ship movement
	if ((position.XValue > screen.GetBottomRight().XValue && velocity.XValue > 0) || (position.XValue < screen.GetTopLeft().XValue && velocity.XValue < 0))
	{
		Message msg;
		msg.type = MessageType::TURN;
		msg.location = position;
		msg.pSource = this;
		pObjectManager->HandleMessage(msg);
	}

	shootTimer -= frameTime;
	downTimer -= frameTime;

	// enemy ship bullets
	if (shootTimer <= 0)
	{
		// play shoot effect
		pSoundFX->PlayEnemyShoot();

		// draw bullet to the screen
		Laser* pLaser = new Laser();
		Vector2D vel;
		vel.setBearing(3.14f, 500.0f);
		Vector2D pos;
		pos.setBearing(3.14f, 45.0f);
		pos = pos + position;

		pLaser->Initialise(pos, vel);

		if (pObjectManager)
			pObjectManager->Add(pLaser);

		// prevent bullet spam
		shootTimer = 3.0f;
	}

	if (downTimer <= 0) {
		position = position + Vector2D(0, -2000.0f) * frameTime;
		downTimer = 2.0f;
	}

	position = position + velocity * frameTime;
	
}

IShape2D& EnemySpaceship::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 64.0f);
	return hitbox;
}

// Collision
void EnemySpaceship::ProcessColision(GameObject& other)
{
	// if enemy spaceship is hit by a bullet
	if (other.TYPE == ObjectType::BULLET)
	{
		// delete game object
		Deactivate();
		// increase player score
		pGameManager->AddScore(5);

		// add explosion
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 4.0f, 0.5f, Vector2D(0, 0));
		pObjectManager->Add(pExp);
		pSoundFX->PlayShipExplosion();

		// add particles
		if (pParticleSystem)
		{
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::WHITE, 10);
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::YELLOW, 10);
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::RED, 10);

		}
		Game::instance.StopHit();

		Vector2D vel;
		vel.setBearing(3.14f, 600.0f);
		Vector2D pos;
		pos.setBearing(3.14f, 45.0f);
		pos = pos + position;
	}

}

// Hitbox
void EnemySpaceship::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

// Message functionality
void EnemySpaceship::ProcessMessage(Message msg)
{
	if (msg.type == MessageType::TURN)
	{
		velocity.XValue = -velocity.XValue;
	}
}