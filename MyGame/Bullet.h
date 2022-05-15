// Created by 18001218
// Provides a Bullet class
// Bullets may award points for hitting certain objects

#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	// Variables
	Vector2D velocity;			// velocity
	float lifetime;				// lifetime - bullets expire after leaving the screen
	Circle2D hitbox;			// hitbox
public:
	// Functions
	Bullet();
	void Initialise(Vector2D startPosition, Vector2D startVelocity);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};
