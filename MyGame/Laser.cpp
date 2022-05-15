// Created by 18001218
// Provides a Laser class, which represents the enemy bullets

#include "Laser.h"

// Constructor
Laser::Laser() : GameObject(ObjectType::LASER)
{
	isActive = true;
	transparency = 0;
	size = 0.9f;
	angle = 0;
	image = -1;
	lifetime = 0;
}

// Initialise enemy bullet
void Laser::Initialise(Vector2D startPosition, Vector2D startVelocity)
{
	LoadImage(L"laser.bmp");
	velocity = startVelocity;
	position = startPosition;
	lifetime = 5.0f;
}

// Update - same as the player bullet 
void Laser::Update(float frameTime)
{
	position = position + velocity * frameTime;
	lifetime = lifetime - frameTime;
	if (lifetime < 1.0f)
	{
		transparency = 1 - lifetime;
		if (transparency > 1.0f)
			transparency = 1.0f;
	}
	if (lifetime <= 0)
		Deactivate();
}

IShape2D& Laser::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 18.0f);
	return hitbox;
}

// Collision
void Laser::ProcessColision(GameObject& other)
{
	// if enemy bullet collides with player ship
	if (other.TYPE == ObjectType::SHIP)
	{
		// delete GO
		Deactivate();
	}
}

// Hitbox
void Laser::DrawHitbox()
{
	MyDrawEngine::GetInstance()->FillCircle(hitbox.GetCentre(), hitbox.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

// No message
void Laser::ProcessMessage(Message msg)
{
}