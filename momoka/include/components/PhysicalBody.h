#pragma once

struct PhysicalBody {
	float velocityX;
	float velocityY;
	float posX;
	float posY;

	float collisionWidth;
	float collisionHeight;

	bool isObstructive;
};
