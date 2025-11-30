#include "Particle.h"

Particle::Particle(Vector2d postion, float mass, float drag)
    : postion(postion),
    velocity(0, 0),
    acceleration(0, 0),
    forces(0, 0),
    mass(mass),
    drag(drag)
{
   
    collider.center = postion;
    collider.r = 10.0f;

    collider_aabb.ul = Vector2d(-10, -10);
    collider_aabb.lr = Vector2d(10, 10);
    collider_aabb.position = postion;

}

void Particle::Update(float dt)
{
    acceleration = forces * (1.0f / mass);
    velocity += acceleration * dt;

    velocity *= (1.0f - drag * dt);

    postion += velocity * dt;

    forces = Vector2d(0, 0);

    collider.center = postion;
    collider_aabb.updatePosition(postion);
    collider_sat.updatePosition(postion);
}

void Particle::addForce(Vector2d force)
{
    forces += force;
}