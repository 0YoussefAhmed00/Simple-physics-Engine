#pragma once
#include "Particle.h"
#include <list>

class PhysicsWorld
{
private:
    std::list<Particle*> particles;
public:
    void addParticle(Particle* particle);
    void Update(float deltaTime);

    void checkCollision();
    void checktwoCircleCollision();
    void checkAABBCollision();
    void checkSatCollision();

    static void ResolveCircleCollision(Particle* a, Particle* b, float restitution = 0.8f);

    static const Vector2d gravity;
};