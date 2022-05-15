// Created by 18001218
// Provides an Asteroid class

#include "Asteroid.h"
#include "gamecode.h"
#include "Explosion.h"


const float TURN_SPEED = 0.02f;

// Constructor
Asteroid::Asteroid() : GameObject(ObjectType::ENEMY_ASTEROID)
{
	isActive = true;
	health = 100;
	transparency = 0.1f;
	size = 1.0f;
	angle = 0;
	image = -1;
	pObjectManager = 0;
	pSoundFX = 0;
	pParticleSystem = 0;
	pGameManager = 0;
}

// Initialise asteroid game object
void Asteroid::Initialise(Vector2D startPosition, Vector2D startVelocity, float startSize, ObjectManager* pOM, SoundFX* pSFX, Particles* pPart, GameManager* pGM)
{
	LoadImage(L"rock.bmp");
	pObjectManager = pOM;
	pSoundFX = pSFX;
	pParticleSystem = pPart;
	position = startPosition;
	velocity = startVelocity;
	size = startSize;
	pGameManager = pGM;
}

// Track asteroid on screen and set velocity of game object
void Asteroid::Update(float frameTime)
{
	Rectangle2D screen = MyDrawEngine::GetInstance()->GetViewport();

	if (position.YValue > screen.GetTopLeft().YValue-50 && velocity.YValue > 0)
	{
		velocity.YValue = -velocity.YValue;
		velocity = velocity * 0.7;
	}

	if (position.YValue < screen.GetBottomRight().YValue+50 && velocity.YValue < 0)
	{
		velocity.YValue = -velocity.YValue;
		velocity = velocity * 0.7;
	}

	if (position.XValue > screen.GetBottomRight().XValue-50 && velocity.XValue > 0)
	{
		velocity.XValue = -velocity.XValue;
		velocity = velocity * 0.7;
	}

	if (position.XValue < screen.GetTopLeft().XValue+50 && velocity.XValue < 0)
	{
		velocity.XValue = -velocity.XValue;
		velocity = velocity * 0.7;
	}

	position = position + velocity*frameTime;
	angle += TURN_SPEED* frameTime;
}

// Set hitbox
IShape2D& Asteroid::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize()*64.0f);
	return hitbox;
}

// Collision 
void Asteroid::ProcessColision(GameObject& other)
{
	// if the asteroid is hit by a bullet
	if (other.TYPE == ObjectType::BULLET)
	{
		// delete asteroid
		Deactivate();
		// increment player score
		pGameManager->AddScore(5);
		// play explosion sound effect
		pSoundFX->PlayAsteroidExplosion();
		// explosion
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 4.0f, 0.5f, Vector2D(0, 0));
		pObjectManager->Add(pExp);
		pSoundFX->PlayShipExplosion();
		Asteroid* pAst = new Asteroid();
		Vector2D pos = position + Vector2D(float(rand() % 150 - 75), float((rand() % 150 - 75)));
		Vector2D vel(float(rand() % 200 - 100), float(rand() % 200 - 100));
		pAst->Initialise(pos, vel + velocity, size / 2.0f, pObjectManager, pSoundFX, pParticleSystem, pGameManager);

		// add particles when asteroid explodes
		if (pParticleSystem)
		{
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::WHITE, 10);
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::YELLOW, 10);
			pParticleSystem->AddParticles(position, 400, MyDrawEngine::RED, 10);

		}
		Game::instance.StopHit();
	}

	if (other.TYPE == ObjectType::ENEMY_ASTEROID)
	{
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
			velocity = 0.7f * velocity;
		}
	}
}

// Asteroid hitbox
void Asteroid::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

// No message
void Asteroid::ProcessMessage(Message msg)
{
}