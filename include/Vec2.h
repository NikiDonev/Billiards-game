#pragma once
/*
#include <SFML/Graphics.hpp>
#include <iostream>

class vec2f
{

public:

	float x{}, y{};

	vec2f::vec2f(float x, float y) : x(x), y(y){}
	vec2f::vec2f(sf::Vector2f vector) : x(vector.x), y(vector.y){}
	vec2f::vec2f() :x(0.0f), y(0.0f){}

	sf::Vector2f vec2f::toSFVector() const{
		return sf::Vector2f(x, y);
	}

	vec2f vec2f::normalize(){
		return length() != 0 ? (*this) / length() : vec2f(0, 0);
	}
	float vec2f::length(){
		return std::sqrt(x * x + y * y);
	}

	vec2f::~vec2f(){}


#pragma region operator overloading

	vec2f operator+(const vec2f& other) const
	{
		return vec2f(x + other.x, y + other.y);
	}
	vec2f& operator+=(const vec2f& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	vec2f operator-(const vec2f& other) const
	{
		return vec2f(x - other.x, y - other.y);
	}
	vec2f& operator-=(float minus)
	{
		x -= minus;
		y -= minus;
		return *this;
	}
	vec2f& operator-=(const vec2f& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	float operator*(const vec2f& other) const
	{
		return x * other.x + y * other.y;
	}
	vec2f operator*(float multiply) const
	{
		return vec2f(x * multiply, y * multiply);
	}
	vec2f& operator*=(const vec2f& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	vec2f& operator*=(float multiply)
	{
		x *= multiply;
		y *= multiply;
		return *this;
	}
	vec2f operator/(float divide) const
	{
		return vec2f(x / divide, y / divide);
	}
    vec2f& operator/=(float divide)  
    {  
		x /= divide;  
        y /= divide;  
		return *this;
    }
	vec2f& operator/=(const vec2f& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	bool operator==(const vec2f& other)
	{
		return x == other.x && y == other.y;
	}


#pragma endregion

};

std::ostream& operator<<(std::ostream& stream, const vec2f& vector);
*/