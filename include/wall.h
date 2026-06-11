#pragma once 
#include <iostream>
#include <SFML/Graphics.hpp>
#include "vec.h"
#include "Ball.h"

struct wall {
	vec2f start, end, n, normal;
	sf::RectangleShape rect;
	sf::CircleShape c1, c2;
	float width{0}, len{0};
	bool init = false;
	wall() {}
	wall(vec2f s, vec2f e, float width = 1.f) : start(s), end(e), width(width) {
		setPosition(s, e, width);
		init = true;
	}
	void setPosition(vec2f s, vec2f e, float wid = 1.f) {
		init = true;
		end = e;
		start = s;
		width = wid;
		vec2f w = end - start;
		n = normalized(w);
		len = !w;
		normal = normalized(rotateDeg(end - start, 90));

		rect.setPosition(start + normal * (width / 2));
		rect.setSize({ width, len });
		rect.setRotation(angleDeg(w) - 90);
		rect.setFillColor(sf::Color::Magenta);
		c1.setOrigin(width / 2, width / 2);
		c2.setOrigin(width / 2, width / 2);
		c1.setPosition(start);
		c2.setPosition(end);
		c1.setRadius(width / 2);
		c2.setRadius(width / 2);
		rect.setFillColor(sf::Color::Red);
	}
	void collide(Ball& ball, float elasticity = 1.f) {
		if (!init) return;
		vec2f b = ball.pos - start;
		vec2f w = end - start;

		float closest = std::clamp((b | w) / length_sq(w), 0.0, 1.0);
		vec2f closestP = start + closest * w;

		vec2f toBall = ball.pos - closestP;
		float distance = !toBall;

		if (distance < ball.radius + width / 2) {
			vec2f collNormal = (distance > 0.f) ? normalized(toBall) : normal;
			elasticity = std::clamp(elasticity, 0.f, 1.f);
			ball.vel = reflect(ball.vel, collNormal, elasticity);
			float penetration = ball.radius + width / 2.f - distance;

			ball.pos += collNormal * penetration;
		}
	}
	void Draw(sf::RenderWindow& window) {
		//window.draw(rect);
		//window.draw(c1);
		//window.draw(c2);
	}
};