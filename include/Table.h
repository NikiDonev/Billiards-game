#pragma once
#include <array>
#include "vec.h"
#include "wall.h"

class Table
{
public:


	int colors = 5;
	//   width			height
	float bw = 198 * cm, bh = 99 * cm;
	//   pocket radius	      table edge     hole offset   cushion width
	float r = 4 * sqrt(2) * cm, te = 19 * cm, ho = 3.5*cm, cw = 5 * cm;
	sf::RectangleShape table;
	sf::CircleShape holes[6];
	sf::CircleShape corners[4];
	sf::RectangleShape rails[2];
	sf::ConvexShape cushions[6];
	sf::ConvexShape diamonds[18];
	wall walls[18];

	struct Pallete {
		const sf::Color tableColor, cushionColor, railsColor, cornerColor, pocketColor, diamondsColor;
	};
	Pallete p[7] = {
		{ sf::Color(0x3bc464FF) ,sf::Color(0x19940cFF) ,sf::Color(0x9c6833FF),sf::Color(0x824e05FF),sf::Color::Black, sf::Color(0xA06B37FF) },
		{ sf::Color(0x5A2784FF) ,sf::Color(0x431C63FF) ,sf::Color(0x9c6833FF),sf::Color(0x824e05FF),sf::Color::Black, sf::Color(0xA06B37FF) },
		{ sf::Color(0x1F7A43FF) ,sf::Color(0x16572FFF) ,sf::Color(0x835824FF),sf::Color(0x794404FF),sf::Color::Black, sf::Color(0x805623FF) },//green
		{ sf::Color(0x1D63B3FF) ,sf::Color(0x13437AFF) ,sf::Color(0xA6AEB5FF),sf::Color(0xE6E6E6FF),sf::Color::Black, sf::Color(0xADB5BBFF) },//blue
		{ sf::Color(0x5A2784FF) ,sf::Color(0x3D1A59FF) ,sf::Color(0xD2A172FF),sf::Color(0xF3E5ABFF),sf::Color::Black, sf::Color(0xD6A77AFF) },//purple
		{ sf::Color(0x4682B4FF) ,sf::Color(0x2E5678FF) ,sf::Color(0xCDB89CFF),sf::Color(0x3A3B3CFF),sf::Color::Black, sf::Color(0xD4BFA4FF) }//light blue
	};

	Table()
	{
		placeTable();

		setWalls();

		setColors();

		placeDiamonds();
	}
	void placeTable() {
		table.setPosition({ bw / -2.f - cw, bh / -2.f - cw });
		table.setSize({ bw + 2 * cw, bh + 2 * cw });



		rails[0].setPosition({ bw / -2.f - te, bh / -2.f });
		rails[0].setSize({ bw + 2 * te, bh });

		rails[1].setPosition({ bw / -2.f, bh / -2.f - te });
		rails[1].setSize({ bw, bh + 2 * te });


		corners[0].setPosition({ bw / -2.f, bh / -2.f });
		corners[1].setPosition({ corners[0].getPosition().x, -1 * corners[0].getPosition().y });
		corners[2].setPosition({ -1 * corners[0].getPosition().x, -1 * corners[0].getPosition().y });
		corners[3].setPosition({ -1 * corners[0].getPosition().x, corners[0].getPosition().y });

		for (int i = 0; i < 4; ++i) {
			corners[i].setRadius(te);

			corners[i].setOrigin({ te, te });

			vec2f offset = { -1.f + 2.f * signbit(corners[i].getPosition().x), -1.f + 2.f * signbit(corners[i].getPosition().y) };
			holes[i].setPosition((vec2f)corners[i].getPosition() - vec2f(offset * ho));
			holes[i].setRadius(r);

			holes[i].setOrigin({ r, r });
			holes[i].setFillColor(p[colors].pocketColor);
		}
		holes[4].setPosition({ 0.f, bh / 2.f + r });
		holes[4].setRadius(r);
		holes[4].setOrigin({ r, r });
		holes[4].setFillColor(p[colors].pocketColor);
		holes[5].setPosition({ 0.f, bh / -2.f - r });
		holes[5].setRadius(r);
		holes[5].setOrigin({ r, r });
		holes[5].setFillColor(p[colors].pocketColor);
	}
	void setWalls() {
		for (int i = 0; i < 6; ++i) {
			cushions[i].setPointCount(4);
		}

		float spw = 13 * cm;  // side pocket width
		float cp = 8.0 * cm;  // corner pocket distance


		cushions[0].setPoint(0, { -spw / 2.f + 1.0f * cm, bh / -2.f - cw });
		cushions[0].setPoint(1, { -spw / 2.f, bh / -2.f });
		cushions[0].setPoint(2, { bw / -2.f + cp, bh / -2.f });
		cushions[0].setPoint(3, { bw / -2.f + cp - cw, bh / -2.f - cw });

		cushions[4].setPoint(0, { bw / -2.f - cw, bh / -2.f + cp - cw });
		cushions[4].setPoint(1, { bw / -2.f, bh / -2.f + cp });
		cushions[4].setPoint(2, { bw / -2.f, bh / 2.f - cp });
		cushions[4].setPoint(3, { bw / -2.f - cw, bh / 2.f - cp + cw });


		for (int i = 0; i < 4; ++i)
			cushions[1].setPoint(i, { cushions[0].getPoint(i).x * -1.f,cushions[0].getPoint(i).y });
		for (int i = 0; i < 4; ++i)
			cushions[2].setPoint(i, { cushions[0].getPoint(i).x,cushions[0].getPoint(i).y * -1.f });
		for (int i = 0; i < 4; ++i)
			cushions[3].setPoint(i, { cushions[0].getPoint(i) * -1.f });

		for (int i = 0; i < 4; ++i)
			cushions[5].setPoint(i, { cushions[4].getPoint(i).x * -1.f ,cushions[4].getPoint(i).y });

		for (int i = 0; i < 6; ++i) {
			walls[3 * i].setPosition(cushions[i].getPoint(0), cushions[i].getPoint(1), 5 * mm);
			walls[3 * i + 1].setPosition(cushions[i].getPoint(1), cushions[i].getPoint(2), 5 * mm);
			walls[3 * i + 2].setPosition(cushions[i].getPoint(2), cushions[i].getPoint(3), 5 * mm);
		}
	}
	void setColors() {
		table.setFillColor(p[colors].tableColor);
		for (int i = 0; i < 4; ++i) 
			corners[i].setFillColor(p[colors].cornerColor);
		for (int i = 0; i < 6; ++i) 
			cushions[i].setFillColor(p[colors].cushionColor);
		rails[0].setFillColor(p[colors].railsColor);
		rails[1].setFillColor(p[colors].railsColor);
		for(int i=0;i<18;++i)
			diamonds[i].setFillColor(p[colors].diamondsColor);
		
	}
	void placeDiamonds() {
		//  diamond width diamond height
		float dw = 1*cm, dh = 2*cm;
		//   quarter width	quarter height	
		float  qw = bw / 8.f, qh = bh / 4.f;

		diamonds[0].setPointCount(4);
		diamonds[0].setPoint(0, {0.f, -dh});
		diamonds[0].setPoint(1, { dw, 0.f });
		diamonds[0].setPoint(2, { 0.f, dh });
		diamonds[0].setPoint(3, { -dw, 0.f });
		for (int i = 1; i < 18; ++i) 
			diamonds[i] = diamonds[0];
		
		float topY = -bh / 2.f - te / 2.f - cw + dh, topX = -bw / 2.f - cw - te / 2.f + 3*dw;
		diamonds[0].setPosition({ -3.f * qw,  topY});
		diamonds[1].setPosition({ -2.f* qw, topY });
		diamonds[2].setPosition({ -1.f* qw, topY });
		diamonds[12].setPosition({  topX, -1.f* qh });
		diamonds[13].setPosition({  topX, 0.f });
		diamonds[14].setPosition({  topX, 1.f* qh });
		for (int i = 0; i < 3; ++i) 
			diamonds[3+i].setPosition(-diamonds[i].getPosition().x, diamonds[i].getPosition().y);
		for (int i = 0; i < 3; ++i)
			diamonds[6 + i].setPosition(diamonds[i].getPosition().x, -diamonds[i].getPosition().y);
		for (int i = 0; i < 3; ++i)
			diamonds[9 + i].setPosition(-diamonds[i].getPosition());
		for (int i = 0; i < 3; ++i)
			diamonds[15 + i].setPosition(-diamonds[12+i].getPosition().x, diamonds[12+i].getPosition().y);
	}
	void Draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < 4; ++i) {
			window.draw(corners[i]);
		}
		window.draw(rails[0]);
		window.draw(rails[1]);
		window.draw(table);
		for (int i = 0; i < 6; ++i) {
			window.draw(cushions[i]);
			window.draw(holes[i]);
		}
		for (int i = 0; i < 18; ++i) {
			window.draw(diamonds[i]);
		}
	}

};