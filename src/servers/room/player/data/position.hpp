#ifndef _POSITION_HPP
#define _POSITION_HPP

struct Position
{
	Position()
	{
		this->x = NULL;
		this->y = NULL;
		this->z = NULL;
		this->xRot = NULL;
		this->yRot = NULL;
		this->zRot = NULL;
	}

	Position(float x, float y, float z, float xRot, float yRot, float zRot)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->xRot = xRot;
		this->yRot = yRot;
		this->zRot = zRot;
	}

	float x, y, z, xRot, yRot, zRot;
};

#endif