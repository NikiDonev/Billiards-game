#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Vec2
{

public:

	float x{}, y{};

	Vec2::Vec2(float x, float y) : x(x), y(y){}
	Vec2::Vec2(sf::Vector2f vector) : x(vector.x), y(vector.y){}
	Vec2::Vec2() :x(0.0f), y(0.0f){}

	sf::Vector2f Vec2::toSFVector() const{
		return sf::Vector2f(x, y);
	}

	Vec2 Vec2::normalize(){
		return length() != 0 ? (*this) / length() : Vec2(0, 0);
	}
	float Vec2::length(){
		return std::sqrt(x * x + y * y);
	}

	Vec2::~Vec2(){}


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