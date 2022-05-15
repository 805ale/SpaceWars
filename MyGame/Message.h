// Created by 18001218
// Provides a Message struct, which points to the message types in the game

#pragma once
#include "messagetypes.h"
#include "vector2D.h"

class GameObject;

struct Message
{
public:
	MessageType type;			

	Vector2D location;

	GameObject* pSource;

	float other;

};

