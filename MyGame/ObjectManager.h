// Created by 18001218
// Provides	an ObjectManager class, which is responsible for managing a list of all the game objects

#pragma once
#include <list>
#include "GameObject.h"
#include "Message.h"

class ObjectManager
{
private:
	// Variables
	std::list<GameObject*> pObjectList;
	int enemyCounter = 0;
public:
	// Functions
	~ObjectManager();
	void Add(GameObject* pObject);
	void RenderAll();
	void UpdateAll(float frameTime);
	void DeleteAll();
	void DeleteInactiveObjects();
	void CheckCollisions();
	int GetNumberOfEnemies();
	void HandleMessage(Message msg);
};

