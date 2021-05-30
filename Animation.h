#pragma once

struct Animation
{
	int index  = 1;
	int frames = 4;
	int speed = 100;

	Animation() {}
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};