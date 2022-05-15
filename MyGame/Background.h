// Created by 18001218
// Provides a Background class, sets the game background

#pragma once
#include "GameObject.h"

class Background : public GameObject
{
private:
	// Variables
	Vector2D velocity;			// velocity
	Circle2D hitbox;			// hitbox
public:
	// Functions
	Background();
	void Initialise(Vector2D startPosition);
	void Update(float frameTime);
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};
