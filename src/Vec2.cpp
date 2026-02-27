#include "Vec2.h"

Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

Vec2::Vec2(sf::Vector2f vector) : x(vector.x), y(vector.y)
{
}
Vec2::Vec2() :x(0.0f),y(0.0f)
{
}

sf::Vector2f Vec2::toSFVector() const
{
	return sf::Vector2f(x,y);
}


Vec2 Vec2::normalize ()
{
	return length() != 0 ? (*this) / length() : Vec2(0, 0);
}

float Vec2::length()
{
	return std::sqrt(x * x + y * y);
}

Vec2::~Vec2()
{
}

std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
{
	stream << vector.x << ", " << vector.y << std::endl;
	return stream;
}
