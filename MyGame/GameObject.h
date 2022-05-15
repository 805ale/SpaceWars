// Created by 18001218
// Provides a GameObject class, which stores a list of all the game objects in the game

#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "objecttypes.h"
#include "Message.h"

class GameObject
{	
protected:
	// Variables
	PictureIndex image;				// a picture index
	Vector2D position;				// position of GO
	float angle;					// angle of GO
	float size;						// size of GO
	float transparency;				// transparency of GO
	bool isActive;					// tracks if the GO is visible
public:
	const ObjectType TYPE;			// type of object

	bool recieveMessages;

	// Constructor
	explicit GameObject(ObjectType type);

	// Destructor
	virtual ~GameObject();

	void Deactivate();				// deletes GO

	float GetImageSize() const;		// get image size


	// Check if GO is active
	inline bool IsActive() const
	{
		return isActive;
	}

	// Draw GO to the screen
	virtual void Render();

	// Draw GO by using myDrawEngine and loading picture
	void LoadImage(const wchar_t* filename);
	
	// GO position
	Vector2D GetPosition() const;

	// Process frames
	virtual void Update(float frametime) = 0;

	// Get Shape of GO
	virtual IShape2D& GetShape() = 0;

	// Process Collision
	virtual void ProcessColision(GameObject& other) = 0;

	// Hitbox
	virtual void DrawHitbox() = 0;

	// Process Message
	virtual void ProcessMessage(Message msg) = 0;
};

