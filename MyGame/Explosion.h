// Created by 18001218
// Provides an Explosion class, responsible for explosion effects

#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Explosion : public GameObject
{
private:
	// Variables
	Vector2D velocity;				// velocity
	Circle2D hitbox;				// hitbox
	float animationSpeed;			// the interval between the sequence of images
	float currentImage;				// keeps track of current image
	PictureIndex images[7];			// array of images - for this game, there are 7 explosion sprites
public:
	// Functions
	Explosion();
	void Initialise(Vector2D startPosition, float startSize, float startTime, Vector2D vel = Vector2D(0,0));
	void Update(float frameTime);
	void Render() override;
	IShape2D& GetShape();
	void ProcessColision(GameObject& other);
	void DrawHitbox();
	void ProcessMessage(Message msg);
};

