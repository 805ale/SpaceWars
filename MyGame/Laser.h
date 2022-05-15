// Created by 18001218
// Provides a Laser class, which represents the enemy bullets

#pragma once
#include "GameObject.h"

class Laser : public GameObject
{
private:
	// Variables
	Vector2D velocity;			// bullet velocity
	float lifetime;				// bullet lifetime
	Circle2D hitbox;			// hitbox
public:
	// Functions
	Laser();
	void Initialise(Vector2D startPosition, Vector2D startVelocity);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};


