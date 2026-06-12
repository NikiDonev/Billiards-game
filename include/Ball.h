#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "Table.h"
#include "vec.h"

static constexpr float cm = 0.01f;
static constexpr float mm = 0.001f;
static constexpr float m = 1.f;
inline bool holdI = 0;

class Table;

class Ball
{
public:
	float radius;                     
	vec2f pos;
	
	vec2f vel;
	sf::CircleShape ball;
	float mass;
	bool startAiming = false;
	bool inPlay = true, holdingBall = false;
	int type = -1, ind = 0;

	Ball(vec2f vector,sf::Color color,float radius, int ind);

	void Draw(sf::RenderWindow& window);

	void CollidingWithTable(const Table& table);

	void CollidingWithBall(Ball& other);

	bool InPocket(const Table& table);

	void MoveBall(float deltaTime);

	void AimingCueBall(sf::RenderWindow& window,vec2f& velocityVector);

	void HoldingBall(sf::RenderWindow& window);

	static sf::SoundBuffer collisionBuffer;
	sf::Sound collisionSound;

	static sf::SoundBuffer pocketBuffer;
	sf::Sound pocketSound;
private:	
	
};

