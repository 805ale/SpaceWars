// Created by 18001218
// Provides	an ObjectManager class, which is responsible for managing a list of all the game objects

#include "ObjectManager.h"
#include "myinputs.h"

MyInputs* pInputs = MyInputs::GetInstance();

// Constructor
void ObjectManager::Add(GameObject* pObject)
{
	pObjectList.push_back(pObject);
	if ((pObject->TYPE == ObjectType::ENEMY_ASTEROID) || (pObject->TYPE == ObjectType::ENEMY_SHIP))
		enemyCounter++;
}

// Render objects
void ObjectManager::RenderAll()
{
	for (GameObject* pNextObject : pObjectList) 
	{
		if (pNextObject)
			pNextObject->Render();
	}
	MyInputs::GetInstance()->SampleKeyboard();


	if (MyInputs::GetInstance()->KeyPressed(DIK_H))
	{
		MyDrawEngine* pDraw = MyDrawEngine::GetInstance();
		pDraw->WriteText(Vector2D(-1750.0f, -700.0f), L"Game Objects on screen: ", MyDrawEngine::LIGHTRED);
		pDraw->WriteInt(Vector2D(-1340.0f, -700.0f), pObjectList.size(), MyDrawEngine::LIGHTRED);
		
		pDraw->WriteText(Vector2D(-1750.0f, -760.0f), L"Enemies on screen: ", MyDrawEngine::LIGHTRED);
		pDraw->WriteInt(Vector2D(-1420.0f, -760.0f), enemyCounter, MyDrawEngine::LIGHTRED);

		for (GameObject* pNextObject : pObjectList)
		{
			if (pNextObject && pNextObject->IsActive())
				pNextObject->DrawHitbox();
		}
	}
}

// Update game objects
void ObjectManager::UpdateAll(float frameTime)
{
	for (GameObject* pNextObject : pObjectList)
	{
		if(pNextObject)
			pNextObject->Update(frameTime);
	}
}

// Delete game objects
void ObjectManager::DeleteAll()
{
	for (GameObject* pNextObject : pObjectList)
	{
		delete pNextObject;
		pNextObject = nullptr;
	}
	pObjectList.clear();
	enemyCounter = 0;

	auto it = std::remove(pObjectList.begin(), pObjectList.end(), nullptr);
	pObjectList.erase(it, pObjectList.end());

}

// Delete inactive game objects - enemies destroyed
void ObjectManager::DeleteInactiveObjects()
{

	for (GameObject* &pNextObject : pObjectList)
	{
		if(pNextObject && !pNextObject->IsActive())
		{ 
			if ((pNextObject->TYPE == ObjectType::ENEMY_ASTEROID) || (pNextObject->TYPE == ObjectType::ENEMY_SHIP))
				enemyCounter--;
			delete pNextObject;
			pNextObject = nullptr;
		}
	}

	
	auto it = std::remove(pObjectList.begin(), pObjectList.end(), nullptr);
	pObjectList.erase(it, pObjectList.end());
}


// Check for collision
void ObjectManager::CheckCollisions()
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;

	for (it1 = pObjectList.begin(); it1!=pObjectList.end();it1++)
		for (it2 = std::next(it1); it2 != pObjectList.end(); it2++)
		{
			if ((*it1) && ((*it1)->IsActive()) && (*it2) && ((*it2)->IsActive()) && (*it1)->GetShape().Intersects((*it2)->GetShape()))
			{
				(*it1)->ProcessColision(**it2);
				(*it2)->ProcessColision(**it1);
			}
		}
}

// Enemy counter
int ObjectManager::GetNumberOfEnemies()
{
	return enemyCounter;
}


// Message handler
void ObjectManager::HandleMessage(Message msg)

{

	for (GameObject*& pNextObject : pObjectList)

	{

		if (pNextObject->recieveMessages == true)
			pNextObject->ProcessMessage(msg);

	}

}

// Destructor
ObjectManager::~ObjectManager()
{
	DeleteAll();
}
