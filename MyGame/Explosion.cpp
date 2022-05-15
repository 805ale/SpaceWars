// Created by 18001218
// Provides an Explosion class, responsible for explosion effects

#include "Explosion.h"

// Constructor
Explosion::Explosion() : GameObject(ObjectType::EXPLOSION)
{
	isActive = true;
	transparency = 0.1f;
	size = 1.0f;
	angle = 0;
	image = -1;
	animationSpeed = 0;
	currentImage = 0;
	images[1] = 0;
}

// Initialise explosion
void Explosion::Initialise(Vector2D startPosition, float startSize, float startTime, Vector2D vel)
{
	position = startPosition;
	animationSpeed = 7 / startTime;
	size = startSize;
	velocity = vel;
	angle = (rand() % 628 / 100.0f);
	// explosion image array
	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
	images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
	images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
	images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");

	// current image index
	currentImage = 0;

	isActive = true;
}

// Update - animation system
void Explosion::Update(float frameTime)
{
	currentImage += frameTime * animationSpeed;
	// if animation finished
	if (currentImage > 7.0)
	{
		// stop animating
		Deactivate();
	}
	position = position + velocity * frameTime;
}

// Draw explosion to the screen
void Explosion::Render()
{
	if (isActive)
		MyDrawEngine::GetInstance()->DrawAt(position, images[int(currentImage)], size, angle, transparency);

}

IShape2D& Explosion::GetShape()
{
	hitbox.PlaceAt(position, GetImageSize() * 64.0f);
	return hitbox;
}

// No collision
void Explosion::ProcessColision(GameObject& other)
{
}

// No hitbox
void Explosion::DrawHitbox()
{
}

// No message
void Explosion::ProcessMessage(Message msg)
{
}