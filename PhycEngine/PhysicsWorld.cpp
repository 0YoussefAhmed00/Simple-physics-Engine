#include "PhysicsWorld.h"
#include <algorithm>

const Vector2d PhysicsWorld::gravity = Vector2d(0.0f, 98.0f);

void PhysicsWorld::addParticle(Particle* particle) {
    particles.push_back(particle);
}

void PhysicsWorld::Update(float deltaTime) {
    for (auto* p : particles) {
        p->addForce(gravity);
        p->Update(deltaTime);
    }
    checkCollision();
}

void PhysicsWorld::checkCollision() {
    checktwoCircleCollision();
    checkAABBCollision();
    checkSatCollision();
}

void PhysicsWorld::checktwoCircleCollision() {
    if (particles.size() < 2) return;
    for (auto itA = particles.begin(); itA != particles.end(); ++itA) {
        auto itB = itA; ++itB;
        for (; itB != particles.end(); ++itB) {
            Particle* a = *itA;
            Particle* b = *itB;
            if (a->collider.checkCollision(b->collider)) {
                std::swap(a->velocity.x, b->velocity.x);
                std::swap(a->velocity.y, b->velocity.y);
            }
        }
    }
}

void PhysicsWorld::checkAABBCollision() {
    if (particles.size() < 2) return;

    for (auto itA = particles.begin(); itA != particles.end(); ++itA) {
        auto itB = itA; ++itB;
        for (; itB != particles.end(); ++itB) {
            Particle* a = *itA;
            Particle* b = *itB;

            if (a->collider_aabb.checkCollision(b->collider_aabb)) {
                Vector2d minA(a->collider_aabb.position.x + a->collider_aabb.ul.x,
                    a->collider_aabb.position.y + a->collider_aabb.ul.y);
                Vector2d maxA(a->collider_aabb.position.x + a->collider_aabb.lr.x,
                    a->collider_aabb.position.y + a->collider_aabb.lr.y);
                Vector2d minB(b->collider_aabb.position.x + b->collider_aabb.ul.x,
                    b->collider_aabb.position.y + b->collider_aabb.ul.y);
                Vector2d maxB(b->collider_aabb.position.x + b->collider_aabb.lr.x,
                    b->collider_aabb.position.y + b->collider_aabb.lr.y);

                float overlapX = std::min(maxA.x, maxB.x) - std::max(minA.x, minB.x);
                float overlapY = std::min(maxA.y, maxB.y) - std::max(minA.y, minB.y);

                Vector2d delta = b->postion - a->postion;
                if (delta.x == 0 && delta.y == 0) delta.x = 0.01f;

                if (overlapX < overlapY) {
                    float push = overlapX * 0.5f;
                    float dir = (delta.x >= 0) ? 1.f : -1.f;
                    a->postion.x -= push * dir;
                    b->postion.x += push * dir;
                    a->velocity.x *= -0.5f;
                    b->velocity.x *= -0.5f;
                }
                else {
                    float push = overlapY * 0.5f;
                    float dir = (delta.y >= 0) ? 1.f : -1.f;
                    a->postion.y -= push * dir;
                    b->postion.y += push * dir;
                    a->velocity.y *= -0.5f;
                    b->velocity.y *= -0.5f;
                }
                a->collider_aabb.updatePosition(a->postion);
                b->collider_aabb.updatePosition(b->postion);
            }
        }
    }
}

void PhysicsWorld::checkSatCollision() {
    if (particles.size() < 2) return;
    for (auto itA = particles.begin(); itA != particles.end(); ++itA) {
        auto itB = itA; ++itB;
        for (; itB != particles.end(); ++itB) {
            Particle* a = *itA;
            Particle* b = *itB;

            if (a->collider_sat.points.empty() || b->collider_sat.points.empty())
                continue;

            if (a->collider_sat.checkCollision(b->collider_sat)) {
                a->velocity.x *= -0.6f;
                a->velocity.y *= -0.6f;
                b->velocity.x *= -0.6f;
                b->velocity.y *= -0.6f;
            }
        }
    }
}

void PhysicsWorld::ResolveCircleCollision(Particle* a, Particle* b, float restitution) {
    Vector2d n = b->postion - a->postion;
    float dist = n.getMagnitude();
    float rSum = a->collider.r + b->collider.r;
    if (dist <= 0.0001f) {
        n = Vector2d(1, 0);
        dist = 1.0f;
    }
    if (dist > rSum) return;

    n = n * (1.0f / dist);

    float penetration = rSum - dist;
    float totalMass = a->mass + b->mass;
    float moveA = penetration * (b->mass / totalMass);
    float moveB = penetration * (a->mass / totalMass);
    a->postion = a->postion - n * moveA;
    b->postion = b->postion + n * moveB;
    a->collider.center = a->postion;
    b->collider.center = b->postion;

    Vector2d relVel = b->velocity - a->velocity;
    float velAlongNormal = relVel.Dot(n);
    if (velAlongNormal > 0) return;

    float invMassA = 1.0f / a->mass;
    float invMassB = 1.0f / b->mass;
    float j = -(1.0f + restitution) * velAlongNormal;
    j /= (invMassA + invMassB);

    Vector2d impulse = n * j;
    a->velocity = a->velocity - impulse * invMassA;
    b->velocity = b->velocity + impulse * invMassB;
}