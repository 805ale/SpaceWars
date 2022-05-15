// Created by 18001218
// Provides a Particles class

#include "Particles.h"

// Constructor
Particles::Particles() : GameObject(ObjectType::UNKNOWN)
{
    colours[0] = 0;
    nextParticle = 0;
}

// Initialise
void Particles::Initialise()
{
    for (int i = 0; i < NUMPARTICLES; i++)
    {
        positions[i].set(-50000.0f, -500000.0f);
        velocities[i].set(-50000.0f, -500000.0f);
    }
    nextParticle = 0;
    hitbox.PlaceAt(Vector2D(-50000.0f, -50000.0f));
    isActive = true;
}

// Update
void Particles::Update(float frameTime)
{
    for (int i = 0; i < NUMPARTICLES; i++)
        positions[i] += velocities[i] * frameTime;
}

// Render
void Particles::Render()
{
    MyDrawEngine::GetInstance()->DrawPointList(positions, colours, NUMPARTICLES);
}

IShape2D& Particles::GetShape()
{
    return hitbox;
}

// No collision
void Particles::ProcessColision(GameObject& other)
{
}

// No hitbox
void Particles::DrawHitbox()
{
}

void Particles::AddParticle(Vector2D position, Vector2D velocity, unsigned int colour)
{
    positions[nextParticle] = position;
    velocities[nextParticle] = velocity;
    colours[nextParticle] = colour;
    nextParticle++;

    if (nextParticle >= NUMPARTICLES)
        nextParticle = 0;
}

void Particles::AddParticles(Vector2D position, float maxVelocity, unsigned int colour, int numParticles)
{
    for (int i = 0; i < numParticles; i++)
    {
        Vector2D velocity;
        velocity.setBearing(rand() % 628 / 100.0f, rand() % 100 / 100.0f * maxVelocity);
        AddParticle(position, velocity, colour);
    }
}

// No message
void Particles::ProcessMessage(Message msg)
{
}
