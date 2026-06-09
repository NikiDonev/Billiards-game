#pragma once
#include <array>
#include "vec.h"
#include "wall.h"

class Table
{
public:

	vec2f start;
	vec2f size;
	sf::RectangleShape table;
	sf::CircleShape holes[6];
	sf::RectangleShape edges[6];
	sf::RectangleShape outline;
	std::array<wall, 6> walls;

	Table(const vec2f& start,const vec2f& size,float holeRadius):start(start),size(size)
	{
		outline.setPosition({ start.x - 2 * holeRadius,start.y - 2 * holeRadius });
		outline.setSize({ size.x + 4 * holeRadius,size.y + 4 * holeRadius });
		outline.setFillColor(sf::Color(0xFFBF00FF));

		float offset = 10.0f;
		float offset2 = 35.0f;
		float offset3 = 10.0f;
		table.setPosition(start);
		table.setSize(size);
		table.setFillColor(sf::Color(0x3bc464FF));
		for (int i = 0; i < 6; i++)
		{
			holes[i].setRadius(holeRadius);
			holes[i].setFillColor(sf::Color::Black);
		}
		float edgeW = holeRadius * 2;
		holes[0].setPosition({ start.x - holeRadius * 2 + offset,start.y - holeRadius * 2 + offset });
		holes[1].setPosition({ start.x + size.x / 2.0f - holeRadius,start.y - holeRadius * 2 });
		holes[2].setPosition({ start.x + size.x - offset,start.y - holeRadius * 2 + offset });
		holes[3].setPosition({ start.x - holeRadius * 2 + offset,start.y + size.y - offset });
		holes[4].setPosition({ start.x + size.x / 2.0f - holeRadius,start.y + size.y });
		holes[5].setPosition({ start.x + size.x - offset,start.y + size.y - offset });

		edges[0].setPosition({ start.x + offset2,start.y - holeRadius * 2 });
		edges[0].setSize({ size.x / 2 - holeRadius - offset2 - offset3,holeRadius * 2 });
		edges[1].setPosition({ start.x + size.x / 2 + holeRadius + offset3,start.y - holeRadius * 2 });
		edges[1].setSize({ size.x / 2 - holeRadius - offset2 - offset3,holeRadius * 2 });
		edges[2].setPosition({ start.x - holeRadius * 2,start.y + offset2 });
		edges[2].setSize({ holeRadius * 2,size.y - offset2 *2});
		edges[3].setPosition({ start.x+size.x,start.y + offset2 });
		edges[3].setSize({ holeRadius * 2,size.y - offset2 * 2 });

		edges[4].setPosition({ start.x + offset2,start.y + size.y });
		edges[4].setSize({ size.x / 2 - holeRadius - offset2 - offset3, holeRadius * 2 });
		edges[5].setPosition({ start.x + size.x / 2 + holeRadius + offset3,start.y + size.y });
		edges[5].setSize({ size.x / 2 - holeRadius - offset2 - offset3,holeRadius * 2 });

		float wallW = 1;
		walls[0].setPosition(vec2f{ edges[0].getPosition() } + vec2f{ 0.f, edges[0].getSize().y }, edges[0].getPosition() + edges[0].getSize(), wallW);
		walls[1].setPosition(vec2f(edges[1].getPosition()) + vec2f{0.f, edges[1].getSize().y}, edges[1].getPosition() + edges[1].getSize(), wallW);
		walls[2].setPosition(vec2f{ edges[2].getPosition() } + vec2f{ edges[2].getSize().x, 0.f }, edges[2].getSize() + edges[2].getPosition(), wallW);
		walls[3].setPosition(edges[3].getPosition(), vec2f{ 0.f,edges[3].getSize().y } + vec2f{ edges[3].getPosition() }, wallW);
		walls[4].setPosition(edges[4].getPosition(), vec2f{ edges[4].getPosition() } + vec2f{ edges[4].getSize().x, 0.f }, wallW);
		walls[5].setPosition(edges[5].getPosition(), vec2f{ edges[5].getPosition() } + vec2f{ edges[5].getSize().x, 0.f }, wallW);
		for (int i = 0; i < 6; i++)
		{
			edges[i].setFillColor(sf::Color(0x9c6833FF));
		}

	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(outline);
		window.draw(table);
		for (int i = 0; i < 6; i++)
		{
			window.draw(holes[i]);
			window.draw(edges[i]);
		}
		for (int i = 0; i < 6; ++i) {
			walls[i].Draw(window);
		}
	}

};