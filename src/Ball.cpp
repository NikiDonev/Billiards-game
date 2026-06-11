#include <SFML/Audio.hpp>
#include <chrono>
#include <random>
#include "Ball.h"
#include "Table.h"


sf::SoundBuffer Ball::collisionBuffer;
sf::SoundBuffer Ball::pocketBuffer;

Ball::Ball(vec2f vector, sf::Color color,float radius, int ind)  
	: pos(vector), color(color), radius(radius), mass(radius* radius* radius)
{  
	if (ind == 0 || ind == 8) type = -1;
	else type = ind % 2;

	ball.setRadius(radius);  
	ball.setPointCount(100);  
	ball.setPosition({ vector.x, vector.y });  
	ball.setOrigin(radius, radius);
	ball.setFillColor(color);  
	ball.setOutlineThickness(-4*mm);  
	ball.setOutlineColor(sf::Color::Black); 


	if (collisionBuffer.getSampleCount() == 0)
		collisionBuffer.loadFromFile(RESOURCES_PATH "ball_collision.wav");
	collisionSound.setBuffer(collisionBuffer);

	if (pocketBuffer.getSampleCount() == 0)
		pocketBuffer.loadFromFile(RESOURCES_PATH "ball_in_pocket.wav");
	pocketSound.setBuffer(pocketBuffer);


	srand(time(0));

}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(ball);
}

void Ball::CollidingWithTable(const Table& table)
{
	for (auto edge : table.walls) {
		edge.collide(*this, 0.9);
	}
}

void Ball::CollidingWithBall(Ball& other)
{
	if (dist(pos, other.pos) < radius + other.radius)
	{
		vec2f x1 = pos;
		vec2f x2 = other.pos;
		vec2f v1(vel);
		vec2f v2(other.vel);
		vec2f n = normalize(x1 - x2);
		float overlap = (radius + other.radius) - dist(pos, other.pos);
		vec2f correction = n * (overlap / 2.0f);
		pos += correction;
		other.pos -= correction;
		ball.setPosition(pos);
		other.ball.setPosition(other.pos.x, other.pos.y);

		float m1 = mass;
		float m2 = other.mass;
		vec2f diff = v1 - v2;
		float p = ((diff | n) / (m1 + m1)) * 2.0f;
		vel = v1 - n * (p * m1);
		other.vel = v2 + n * (p * m2);

		collisionSound.setVolume(dist((v1 + v2), {0.0f,0.0f})/8);

		collisionSound.setPitch(0.7+(((double)rand()) / RAND_MAX)/2);
		collisionSound.play();

	}
}
bool Ball::InPocket(const Table& table)
{
	if (pos.x + radius < table.bw/ -2.f || pos.x - radius>table.bw/2.f ||
		pos.y + radius<table.bh/ -2.f || pos.y - radius>table.bh/2.f)
	{
		if (inPlay) {
			pocketSound.setVolume(70);
			pocketSound.play();
		}
		return true;
	}
	return false;
}
void Ball::MoveBall(float deltaTime)
{
	float speed = 8.0f;
	pos += vel * deltaTime * speed;
	ball.setPosition(pos);
	float k = 0.002f, m = 0.17f, g = 9.80665f;
	vec2f a = k * g * normalized(vel) * deltaTime;
	if (length(vel) < length(a) || length(vel) < 0.00001f) vel = { 0.f,0.f };
	else vel -= a;
	//vel *= {0.9996699f, 0.9996699f};
}

void Ball::AimingCueBall(sf::RenderWindow& window,vec2f& velocityVector)
{
	velocityVector = { 0.0f,0.0f };
	bool mousePressed = false;
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		mousePressed = true;
	else
		mousePressed = false;

	if (dist(vec2f(mousePos),  pos) <= 20*cm && mousePressed)
	{
		startAiming = true;
	}
	if (startAiming)
	{
		velocityVector = pos - (vec2f)mousePos;
	}
	if (startAiming && !mousePressed)
	{
		vel = pos - (vec2f)mousePos;
		if (dist({ 0,0 }, vel) > 8.0f)
		{
			vel = normalize(vel) * 8.0f;
		}
		startAiming = false;
	}
}

