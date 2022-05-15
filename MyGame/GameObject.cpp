// Created by 18001218
// Provides a GameObject class, which stores a list of all the game objects in the game
#include "GameObject.h"
#include "myinputs.h"


// Constructor
GameObject::GameObject(ObjectType type) : TYPE(type)
{
	isActive = true;
	size = 1.0;
	angle = 0;
	transparency = 0;
	image = -1;
	recieveMessages = false;
}

// Position of GO
Vector2D GameObject::GetPosition() const
{
	return position;
}

// Destructor
GameObject::~GameObject()
{
	isActive = false;
}

// Delete GO
void GameObject::Deactivate()
{
	isActive = false;
}

// Size of GO
float GameObject::GetImageSize() const
{
	return size;
}

// Load image
void GameObject::LoadImage(const wchar_t* filename)
{
	image = MyDrawEngine::GetInstance()->LoadPicture(filename);
}

// Render GO
void GameObject::Render()
{
	if(isActive)
		MyDrawEngine::GetInstance()->DrawAt(position, image, size, angle, transparency);
}

