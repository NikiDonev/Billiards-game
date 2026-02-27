#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Vec2
{

public:

	float x, y;


	Vec2(float x, float y);

	Vec2(sf::Vector2f vector);

	Vec2();
    sf::Vector2f toSFVector() const;
    //sf::Vector2f start = vec1.toSFVector();
	
	//sf::Vector2f toSFVector();

	Vec2 normalize();

	float length();

	~Vec2();


#pragma region operator overloading

	Vec2 operator+(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}
	Vec2& operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2 operator-(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}
	Vec2& operator-=(float minus)
	{
		x -= minus;
		y -= minus;
		return *this;
	}
	Vec2& operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	float operator*(const Vec2& other) const
	{
		return x * other.x + y * other.y;
	}
	Vec2 operator*(float multiply) const
	{
		return Vec2(x * multiply, y * multiply);
	}
	Vec2& operator*=(const Vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	Vec2& operator*=(float multiply)
	{
		x *= multiply;
		y *= multiply;
		return *this;
	}
	Vec2 operator/(float divide) const
	{
		return Vec2(x / divide, y / divide);
	}
    Vec2& operator/=(float divide)  
    {  
		x /= divide;  
        y /= divide;  
		return *this;
    }
	Vec2& operator/=(const Vec2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	bool operator==(const Vec2& other)
	{
		return x == other.x && y == other.y;
	}


#pragma endregion

};

std::ostream& operator<<(std::ostream& stream, const Vec2& vector);