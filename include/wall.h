#pragma once 
#include <iostream>
#include "Vec2.h"
#include <SFML/Graphics.hpp>

struct wall {
	Vec2 start, end, n;
	sf::RectangleShape rect;
	sf::CircleShape c1, c2;
	float width{10}, len{200};
	wall(Vec2 s, Vec2 e) : start(s), end(e) {
		Vec2 w = e - s;
		n = w.normalize();
		len = w.length();
		rect.setPosition(start.toSFVector());
		rect.setSize({ width, len });
		//rect.setRotation(atan2(w.y, w.x));
		c1.setPosition(start.toSFVector());
		c2.setPosition(end.toSFVector());
		c1.setRadius(5);
		c2.setRadius(5);
		rect.setFillColor(sf::Color::Red);
	}
	void collide(Ball& ball) {
		Vec2 pos = { ball.x, ball.y };
		Vec2 diff = pos - start;
		float closest = (n * pos) / len;
		Vec2 dist = pos - (n * closest);
		//std::cout << closest << std::endl;
		//std::cout << dist << std::endl;
		if (0 < closest && closest < 1 &&
			dist.length() <= width + ball.radius) {
			//std::cout << "Colliding"  << std::endl;
			Vec2 norm = dist.normalize();
			float l = 2 * (norm * ball.velocity);
			ball.velocity -= norm * l;
		}
	}
	void Draw(sf::RenderWindow& window) {
		window.draw(rect);
		window.draw(c1);
		window.draw(c2);
	}
};