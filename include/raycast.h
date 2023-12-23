#pragma once
#include "raylib.h"
#include <cmath>

struct Ray2D {
    Vector2 origin;
    Vector2 direction;
};

bool CheckCollisionRecRay(Rectangle rect, Ray2D ray, Vector2& point);
