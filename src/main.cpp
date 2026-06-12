#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Table.h"
#include "wall.h"
#include "Ball.h"
#include "vec.h"

static const float view_height = 800.0f;
const float minWidth = 290 * cm;
vec2f velocityVector;
float r = 2.85 * cm;
bool gameMode = 0;

void ResizeView(sf::RenderWindow& window, sf::View& view)
{
	view.setSize({ minWidth, (float)window.getSize().y / (float)window.getSize().x * minWidth });
	window.setView(view);
}


void DrawVector( vec2f start, vec2f vel, sf::RenderWindow& window)  
{  
	float width = 0.7*cm;
    vec2f end = start + vel;

    vec2f direction = end - start;  
	float length = !direction * 2.f;
	length += r;
	scale(direction, length);


	sf::RectangleShape line({ length, width });
	line.setOrigin(0, width / 2);
	line.setPosition(start.x, start.y);
    line.setRotation(angleDeg(direction));
    line.setFillColor(sf::Color::White);  
	line.setOutlineThickness(4*mm);
	line.setOutlineColor(sf::Color::Black);

	float arrW = 1.2*cm, arrH = 2.1 * cm;
	sf::ConvexShape arrow;
	arrow.setPointCount(3);
	arrow.setPoint(0, { -arrW, 0.f });
	arrow.setPoint(1, { arrW, 0.f });
	arrow.setPoint(2, { 0.f, -arrH - 8*mm });
	arrow.setOutlineColor(sf::Color::Black);
	arrow.setOutlineThickness(5 * mm);
	arrow.setPosition(start + direction);
	arrow.setRotation(angleDeg(direction) + 90);

    window.draw(line); 
	window.draw(arrow);
}
unsigned int colors[2][15] = { {
	0xFFD000FF, // 1  - Canary Yellow
	0x007BFFFF, // 2  - Vibrant Blue
	0xFF3B30FF, // 3  - Crimson Red
	0x8E44ADFF, // 4  - Deep Violet
	0xFF9500FF, // 5  - Neon Orange
	0x2ECC71FF, // 6  - Bright Mint Green
	0xA62B2BFF, // 7  - Burgundy / Maroon
	0x1C1C1EFF, // 8  - True Black
	0xFFD000FF, // 9  - Yellow (Stripe base)
	0x007BFFFF, // 10 - Blue (Stripe base)
	0xFF3B30FF, // 11 - Red (Stripe base)
	0x8E44ADFF, // 12 - Purple (Stripe base)
	0xFF9500FF, // 13 - Orange (Stripe base)
	0x2ECC71FF, // 14 - Green (Stripe base)
	0xA62B2BFF  // 15 - Maroon (Stripe base)

},{
	0x007BFFFF, // 1  - Blue
	0xFF3B30FF, // 2  - Red
	0x007BFFFF, // 3  - Blue
	0x007BFFFF, // 4  - Blue
	0x1C1C1EFF, // 6  - Black
	0xFF3B30FF, // 5  - Red
	0xFF3B30FF, // 7  - Red
	0x007BFFFF, // 8  - Blue
	0xFF3B30FF, // 9  - Red
	0x007BFFFF, // 10 - Blue
	0x007BFFFF, // 11 - Blue
	0xFF3B30FF, // 12 - Red 
	0xFF3B30FF, // 13 - Red 
	0x007BFFFF, // 14 - Blue
	0xFF3B30FF, // 15 - Red 
}};

	
Table table;

int main()
{
	sf::RenderWindow window(sf::VideoMode(view_height*2, view_height), "Billiards game", sf::Style::Close | sf::Style::Titlebar 
		| sf::Style::Resize);
	sf::View view(sf::Vector2f(view_height, view_height/2), sf::Vector2f(2 * view_height, view_height));
	view.setCenter(0, 0);
	view.zoom(1.f/480.f);
	window.setView(view);
	vec2f tableSize(198*cm, 99*cm);

	
	std::vector<Ball> balls;
	balls.reserve(16);

	vec2f InitPos[15] = { 
		{0.0f,0.0f}				   //1
		,{r * sqrtf(3),r}		   //2
		,{r * sqrtf(3) ,-r}		   //3
		,{r * sqrtf(3) * 2,r * 2}  //4
		,{r * sqrtf(3) * 2,0.0f}   //5
		,{r * sqrtf(3) * 2,r * -2} //6
		,{r * sqrtf(3) * 3,r * 3}  //7
		,{r * sqrtf(3) * 3,r}	   //8
		,{r * sqrtf(3) * 3,-r}	   //9
		,{r * sqrtf(3) * 3,r * -3} //10
		,{r * sqrtf(3) * 4,r * 4}  //11
		,{r * sqrtf(3) * 4,r * 2}  //12
		,{r * sqrtf(3) * 4,0.0f}   //13
		,{r * sqrtf(3) * 4,r * -2} //14
		,{r * sqrtf(3) * 4,r * -4} //15

	};

	balls.emplace_back( Ball({ table.bw/-4.f, 0 }, sf::Color::White, r, -1));
	for (int i = 0; i < 15; i++) {
		balls.emplace_back(Ball({ table.bw/ 4.f + InitPos[i].x ,InitPos[i].y}, sf::Color(colors[gameMode][i]), r,i));
	}

	float deltaTime = 0.0f;
	sf::Clock clock;
	int bgColor = 2;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f) 
			deltaTime = 1.0f / 20.0f;
		

		sf::Event evnt;
		while (window.pollEvent(evnt)) {

			switch (evnt.type)
			{
			case evnt.Closed:
				window.close();
				break;
			case evnt.Resized:
				ResizeView(window, view);
				break;

			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))
			table.colors = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
			table.colors = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
			table.colors = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
			table.colors = 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
			table.colors = 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
			table.colors = 5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) gameMode = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) gameMode = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)
		 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
		 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
			balls[0].vel = { 0, 0 };
			balls[0].pos = { table.bw / -4.f, 0 };
			balls[0].inPlay = true;
			for (int i = 1; i < balls.size(); ++i) {
				balls[i].vel = { 0, 0 };
				balls[i].pos = { table.bw / 4.f + InitPos[i-1].x ,InitPos[i-1].y };
				balls[i].inPlay = true;
				balls[i].ball.setFillColor(sf::Color(colors[gameMode][i-1]));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && gameMode == 0)
			balls[0].vel = { 0.f, 0.f };

		
		if (evnt.type == sf::Event::KeyReleased) {
			table.setColors();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
			bgColor = (bgColor + 1) % 3;


		unsigned int bgColors[3] = { 0x1F1610FF , 0x121315FF , 0x0B0F19FF };
		window.clear(sf::Color(bgColors[bgColor]));

		


		table.Draw(window);

		for (int i = 0; i < balls.size();++i) {
			if (!balls[i].inPlay) continue;
			balls[i].Draw(window);
			balls[i].MoveBall(deltaTime);
			balls[i].CollidingWithTable(table);
			if(gameMode == 0) balls[i].HoldingBall(window);

			if (balls[i].InPocket(table)) {
				if (i == 0) {
					balls[0].pos = { table.bw/-4.f, 0 };
					balls[0].vel = { 0, 0 };
				}
				else {
					balls[i].pos.x = 10000;
					balls[i].inPlay = false;
				}
			}
		}

		if (window.hasFocus() && !balls[0].vel < 1 * mm) {
			balls[0].AimingCueBall(window, velocityVector);
			DrawVector({ balls[0].pos.x,balls[0].pos.y}, velocityVector, window);

		}
		balls[0].Draw(window);
		for (int i = 0; i < balls.size() - 1; i++) {
			if (!balls[i].inPlay) continue;
			for (int j = i + 1; j < balls.size(); j++) {
				if (!balls[j].inPlay) continue;
				balls[i].CollidingWithBall(balls[j]);
			}
		}

		window.display();
	}
}