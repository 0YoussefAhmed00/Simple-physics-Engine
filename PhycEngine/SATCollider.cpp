#include "SATCollider.h"
#include <limits>
#include <cmath>

void SATCollider::updatePosition(Vector2d pos) {
    position = pos;
}

vector<Vector2d> SATCollider::getNormals() {
    vector<Vector2d> normals;
    if (points.size() < 2) return normals;

    for (size_t i = 0; i < points.size(); ++i) {
        Vector2d p1 = points[i];
        Vector2d p2 = points[(i + 1) % points.size()];
        Vector2d edge = p2 - p1;
        Vector2d normal = edge.getNormal().getNormalized();
        normals.push_back(normal);
    }
    return normals;
}

Vector2d SATCollider::projectShape(Vector2d axis) {
    float minProj = std::numeric_limits<float>::infinity();
    float maxProj = -std::numeric_limits<float>::infinity();

    for (auto& localPt : points) {
        Vector2d worldPt = localPt + position;
        float proj = worldPt.Dot(axis);
        if (proj < minProj) minProj = proj;
        if (proj > maxProj) maxProj = proj;
    }
    return Vector2d(minProj, maxProj);
}

bool SATCollider::checkCollision(SATCollider other) {
    vector<Vector2d> axes = getNormals();
    vector<Vector2d> otherAxes = other.getNormals();
    axes.insert(axes.end(), otherAxes.begin(), otherAxes.end());

    for (auto& axis : axes) {
        if (axis.getMagnitude() == 0) continue;
        Vector2d normAxis = axis.getNormalized();
        Vector2d projA = projectShape(normAxis);
        Vector2d projB = other.projectShape(normAxis);

        if (projA.y < projB.x || projB.y < projA.x) {
            return false;
        }
    }
    return true;
}