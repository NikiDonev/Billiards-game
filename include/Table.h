#pragma once
#include "Vec2.h"

class Table
{
public:

	Vec2 start;
	Vec2 size;
	sf::RectangleShape table;
	sf::CircleShape holes[6];
	sf::RectangleShape edges[6];
	sf::RectangleShape outline;


	Table(const Vec2& start,const Vec2& size,float holeRadius):start(start),size(size)
	{
		outline.setPosition({ start.x - 2 * holeRadius,start.y - 2 * holeRadius });
		outline.setSize({ size.x + 4 * holeRadius,size.y + 4 * holeRadius });
		outline.setFillColor(sf::Color(0xFFBF00FF));

		float offset = 10.0f;
		float offset2 = 35.0f;
		float offset3 = 10.0f;
		table.setPosition(start.toSFVector());
		table.setSize(size.toSFVector());
		table.setFillColor(sf::Color(0x3bc464FF));
		for (int i = 0; i < 6; i++)
		{
			holes[i].setRadius(holeRadius);
			holes[i].setFillColor(sf::Color::Black);
		}
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
	}

};