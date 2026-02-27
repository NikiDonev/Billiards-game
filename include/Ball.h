#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vec2.h"
#include "Table.h"

//float distance(sf::Vector2f vec1, sf::Vector2f vec2);

class Ball
{
public:
	float radius;                     
	float x, y;
	int index;
	

	Ball(Vec2 vector,sf::Color color,float radius,int index);

	//Ball(Vec2 vector,int index);

	void Draw(sf::RenderWindow& window);

	void CollidingWithTable(const Table& table, float deltaTime);

	void CollidingWithRect(const Vec2& edge1, const Vec2& size, float deltaTime);

	void CollidingWithBall(Ball& other);

	int InPocket(const Table& table);

	void MoveBall(float deltaTime);

	Vec2 velocity;
	sf::CircleShape ball;
	float mass;

	static sf::SoundBuffer collisionBuffer;
	sf::Sound collisionSound;

	static sf::SoundBuffer pocketBuffer;
	sf::Sound pocketSound;
private:	
	sf::Color color;
	
};

class CueBall : public Ball
{
public:
	using Ball::Ball;

	void AimingCueBall(sf::RenderWindow& window,Vec2& velocityVector);
	void InPocket(const Table& table);
private:
	bool startAiming = false;


};