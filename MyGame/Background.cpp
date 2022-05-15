// Created by 18001218
// Provides a Background class, sets the game background

#include "Background.h"

// Constructor
Background::Background() : GameObject(ObjectType::BACKGROUND)
{
	isActive = true;
	transparency = 0;
	size = 1.0f;
	angle = 0;
	image = -1;
	velocity = Vector2D(0,0);
}

// Initialise background
void Background::Initialise(Vector2D startPosition)
{
	LoadImage(L"background.jpg");
	position = startPosition;
}

// Background position does not update
void Background::Update(float frameTime)
{
}

IShape2D& Background::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 64.0f);
	return hitbox;
}

// No collision
void Background::ProcessColision(GameObject& other)
{
}

// No hitbox
void Background::DrawHitbox()
{
}

// No message
void Background::ProcessMessage(Message msg)
{
}