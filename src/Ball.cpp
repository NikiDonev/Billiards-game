#include <SFML/Audio.hpp>
#include <chrono>
#include <random>
#include "Ball.h"
#include "Vec2.h"
#include "Table.h"

float distance(sf::Vector2f vec1, sf::Vector2f vec2);
void DrawVector(const Vec2& vec1, const Vec2& vec2, sf::RenderWindow& window);

sf::SoundBuffer Ball::collisionBuffer;
sf::SoundBuffer Ball::pocketBuffer;

Ball::Ball(Vec2 vector, sf::Color color,float radius,int index)  
	: x(vector.x), y(vector.y), color(color), radius(radius),index(index), mass(radius* radius* radius)
{  
	ball.setRadius(radius);  
	ball.setPointCount(100);  
	ball.setPosition({ vector.x, vector.y });  
	ball.setOrigin(radius, radius);
	ball.setFillColor(color);  
	ball.setOutlineThickness(-2.0f);  
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

void Ball::CollidingWithTable(const Table& table,float deltaTime)
{
	CollidingWithRect(Vec2(table.edges[0].getPosition()), Vec2(table.edges[0].getSize()),deltaTime);
	CollidingWithRect(Vec2(table.edges[1].getPosition()), Vec2(table.edges[1].getSize()), deltaTime);
	CollidingWithRect(Vec2(table.edges[2].getPosition()), Vec2(table.edges[2].getSize()), deltaTime);
	CollidingWithRect(Vec2(table.edges[3].getPosition()), Vec2(table.edges[3].getSize()), deltaTime);
	CollidingWithRect(Vec2(table.edges[4].getPosition()), Vec2(table.edges[4].getSize()), deltaTime);
	CollidingWithRect(Vec2(table.edges[5].getPosition()), Vec2(table.edges[5].getSize()), deltaTime);

}
void Ball::CollidingWithRect(const Vec2& edge1, const Vec2& size,float deltaTime)
{

	Vec2 edge2 = edge1 + size;
	float r = radius;
	float Rx = edge1.x, Ry = edge1.y,Rw = size.x,Rh = size.y;
	if (x - r > Rx && x + r < Rx + Rw)
	{
		if (y - r < Ry + Rh && y + r > Ry)
		{
			velocity.y *= -1;
		}
	}
	else if (y - r > Ry && y + r < Ry + Rh)
	{
		if (x - r < Rx + Rw && x + r > Rx)
		{
			velocity.x *= -1;
		}
	}
	else if (x - r < Rx + Rw && x + r>Rx && y - r<Ry + Rh && y + r>Ry)
	{
		float dx = (x - Rx - Rw)/abs(x - Rx - Rw);
		float dy = (y - Ry - Rh)/abs(y - Ry - Rh);
		float correction = radius/5;
		x += dx * correction;
		y += dy * correction;
		velocity.x *= -0.9;
		velocity.y *= -0.9;
	}
}

void Ball::CollidingWithBall(Ball& other)
{
	if (distance({ x,y }, { other.x,other.y }) < radius + other.radius)
	{
		Vec2 x1(x, y);
		Vec2 x2(other.x, other.y);
		Vec2 v1(velocity);
		Vec2 v2(other.velocity);
		Vec2 n = (x1 - x2).normalize();
		float overlap = (radius + other.radius) - distance({ x, y }, { other.x, other.y });
		Vec2 correction = n * (overlap / 2.0f);
		x += correction.x;
		y += correction.y;
		other.x -= correction.x;
		other.y -= correction.y;
		ball.setPosition(x, y);
		other.ball.setPosition(other.x, other.y);

		float m1 = mass;
		float m2 = other.mass;
		float p = ((v1 - v2) * n / (m1 + m1)) * 2.0f;
		velocity = v1 - n * (p * m1);
		other.velocity = v2 + n * (p * m2);

		collisionSound.setVolume(distance((v1 + v2).toSFVector(), {0.0f,0.0f})/8);

		collisionSound.setPitch(0.7+(((double)rand()) / RAND_MAX)/2);
		collisionSound.play();

	}
}
bool Ball::InPocket(const Table& table)
{
	if (x + radius < table.start.x || x - radius>table.start.x + table.size.x ||
		y + radius<table.start.y || y - radius>table.start.y + table.size.y)
	{
		//pocketSound.setVolume(100);
		//pocketSound.play();
		return true;
	}
	return false;
}
void Ball::MoveBall(float deltaTime)
{
	float speed = 8.0f;
	x += velocity.x * deltaTime * speed;
	y += velocity.y * deltaTime * speed;
	ball.setPosition(x, y);

	velocity *= {0.9996699f, 0.9996699f};
}

void Ball::AimingCueBall(sf::RenderWindow& window,Vec2& velocityVector)
{
	velocityVector = { 0.0f,0.0f };
	bool mousePressed = false;
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		mousePressed = true;
	else
		mousePressed = false;

	if (distance(mousePos, { x,y }) <= radius && mousePressed)
	{
		startAiming = true;
	}
	if (startAiming)
	{
		velocityVector = Vec2({ x, y }) - Vec2(mousePos);
	}
	if (startAiming && !mousePressed)
	{
		velocity = Vec2({ x, y }) -  Vec2(mousePos);
		if (distance({ 0,0 }, { velocity.x,velocity.y }) > 300.0f)
		{
			velocity = velocity.normalize() * 300.0f;
		}
		startAiming = false;
	}
}

