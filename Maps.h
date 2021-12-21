#pragma once

#include <cmath>

#define PART_NUM 254 // Particles
#define VIEW_WIDTH 800
#define VIEW_HEIGHT 600


class Vecf2
{
public:
	float x{ 0 }, y{ 0 };

	float squaredLength() { return x * x + y * y; }
	float length() { return pow(squaredLength(), 0.5f); }
	Vecf2 normalize()
	{
		if (length() > 0)
			return *this * (1 / length());
		return Vecf2{};
	}

	Vecf2 operator-() const
	{
		return { -this->x, -this->y };
	}
	Vecf2 operator+(const Vecf2& vec) const
	{
		return { this->x + vec.x, this->y + vec.y };
	}
	Vecf2 operator*(float num) const
	{
		return { this->x * num, this->y * num };
	}
};


namespace Maps
{
	const Vecf2* getCXC();
}