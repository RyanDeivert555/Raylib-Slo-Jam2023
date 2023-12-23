#include "../include/raycast.h"
#include "raymath.h"

bool CheckCollisionRecRay(Rectangle rect, Ray2D ray, Vector2& point) {
    float minParam = -INFINITY;
    float maxParam = INFINITY;

    Vector2 direction = ray.direction;
    Vector2 origin = ray.origin;

    if (direction.x != 0.0f) {
        float txMin = (rect.x - origin.x) / direction.x;
        float txMax = ((rect.x + rect.width) - origin.x) / direction.x;

        minParam = std::min(minParam, std::min(txMin, txMax));
        maxParam = std::max(maxParam, std::max(txMin, txMax));
    }

    if (direction.y != 0.0f) {
        float tyMin = (rect.y - origin.y) / direction.y;
        float tyMax = ((rect.y + rect.height) - origin.y) / direction.y;

        minParam = std::min(minParam, std::min(tyMin, tyMax));
        maxParam = std::max(maxParam, std::max(tyMin, tyMax));
    }

    if (maxParam < 0.0f) {
        return false;
    }
    if (minParam > maxParam) {
        return false;
    }
    point = Vector2Add(origin, Vector2Scale(direction, minParam));
    
    return true;
}