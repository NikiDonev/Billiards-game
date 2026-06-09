#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "Table.h"
#include "vec.h"

class Table;

class Ball
{
public:
	float radius;                     
	int index;
	vec2f pos;
	
	vec2f vel;
	sf::CircleShape ball;
	float mass;
	bool startAiming = false;

	Ball(vec2f vector,sf::Color color,float radius,int index);

	void Draw(sf::RenderWindow& window);

	void CollidingWithTable(const Table& table, float deltaTime);

	void CollidingWithTable(const Table& table);

	void CollidingWithBall(Ball& other);

	bool InPocket(const Table& table);

	void MoveBall(float deltaTime);
	void AimingCueBall(sf::RenderWindow& window,vec2f& velocityVector);

	static sf::SoundBuffer collisionBuffer;
	sf::Sound collisionSound;

	static sf::SoundBuffer pocketBuffer;
	sf::Sound pocketSound;
	sf::Color color;
private:	
	
};

