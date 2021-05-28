#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
	//This is a type of collision detection called Axis-Alligned Bounding Box
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};