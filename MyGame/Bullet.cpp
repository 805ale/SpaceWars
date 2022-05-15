// Created by 18001218
// Provides a Bullet class
// Bullets may award points for hitting certain objects

#include "Bullet.h"

// Constructor
Bullet::Bullet() : GameObject(ObjectType::BULLET)
{
	isActive = true;
	transparency = 0;
	size = 1.5f;
	angle = 0;
	image = -1;
	lifetime = 0;
}

// Initialise bullet
void Bullet::Initialise(Vector2D startPosition, Vector2D startVelocity)
{
	LoadImage(L"bullet.bmp");
	velocity = startVelocity;
	position = startPosition;
	lifetime = 1.5f;
}


void Bullet::Update(float frameTime)
{
	// bullet position
	position = position + velocity * frameTime;
	// bullet lifetime
	lifetime = lifetime - frameTime;
	if (lifetime < 1.0f)
	{
		transparency = 1 - lifetime;
		if (transparency > 1.0f)
			transparency = 1.0f;
	}
	// delete bullet
	if (lifetime <= 0)
		Deactivate();
}

IShape2D& Bullet::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 18.0f);
	return hitbox;
}

// Bullet collision
void Bullet::ProcessColision(GameObject& other)
{
	// if bullet collides with asteroid or enemy ship
	if ((other.TYPE == ObjectType::ENEMY_ASTEROID) || (other.TYPE == ObjectType::ENEMY_SHIP))
	{
		// delete game object
		Deactivate();
	}
}

// Hitbox
void Bullet::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

// No message
void Bullet::ProcessMessage(Message msg)
{
}