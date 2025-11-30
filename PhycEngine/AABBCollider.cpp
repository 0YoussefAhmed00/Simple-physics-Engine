#include "AABBCollider.h"

void AABBCollider::updatePosition(Vector2d newPos) {
    position = newPos;
}

bool AABBCollider::checkCollision(AABBCollider other) {
    Vector2d minA(position.x + ul.x, position.y + ul.y);
    Vector2d maxA(position.x + lr.x, position.y + lr.y);

    Vector2d minB(other.position.x + other.ul.x, other.position.y + other.ul.y);
    Vector2d maxB(other.position.x + other.lr.x, other.position.y + other.lr.y);

    bool overlapX = (minA.x <= maxB.x) && (maxA.x >= minB.x);
    bool overlapY = (minA.y <= maxB.y) && (maxA.y >= minB.y);
    return overlapX && overlapY;
}