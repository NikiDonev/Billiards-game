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
	wall() {}
	wall(vec2f s, vec2f e, float width = 1.f) : start(s), end(e), width(width) {
		setPosition(s, e, width);
	}
	void setPosition(vec2f s, vec2f e, float wid = 1.f) {
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
	void collide(Ball& ball) {
		vec2f b = ball.pos - start;
		vec2f w = end - start, n = normalized(w);
		vec2f pr = (n | b) * n;
		vec2f dst = b - pr;

		float closest = !pr / !w;
		if (angleDeg(w) - angleDeg(pr) > 90) closest *= -1;

		if (!dst < ball.radius + width / 2) {
			vec2f collV;
			if (closest > 0.f && closest < 1.f) {
				collV = dst * -1.f - normal * (width / 2);
			}
			else if (dist(ball.pos , start) <= ball.radius + width/2) {
				collV = ball.pos - start;
			}
			else if (dist(ball.pos, end) <= ball.radius + width / 2) {
				collV = ball.pos - end;
			}
			ball.vel = reflect(ball.vel, normalized(collV), 0.9f);
		}
	}
	void Draw(sf::RenderWindow& window) {
		//window.draw(rect);
		//window.draw(c1);
		//window.draw(c2);
	}
};