#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Table.h"
#include "wall.h"
#include "Ball.h"
#include "vec.h"

static const float view_height = 800.0f;

void ResizeView(sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(view_height * aspectRatio, view_height);
}

float distance(sf::Vector2f vec1, sf::Vector2f vec2f)
{
	return sqrt((vec2f.x - vec1.x) * (vec2f.x - vec1.x) + (vec2f.y - vec1.y) * (vec2f.y - vec1.y));
}

vec2f velocityVector;



void DrawVector(const vec2f& vec1, const vec2f& vec2f, sf::RenderWindow& window)  
{  
	float width = 2.0f;
	float pi = 2 * acos(0.0);
	sf::Vector2f start = { vec1.x ,vec1.y};
    sf::Vector2f end = vec1 + vec2f;

    sf::Vector2f direction = end - start;  
	float length = sqrt(direction.x * direction.x + direction.y * direction.y)*2;
	//if (length > 150.0f)
	//{
	//	length = 150.0f;
	//}
	length += 10.0f;

    sf::RectangleShape line(sf::Vector2f(length, width));
	line.setOrigin(0, width / 2);
	line.setPosition(start.x, start.y);
    line.setRotation(atan2(direction.y, direction.x) * 180.0f / pi);
    line.setFillColor(sf::Color::White);  
	line.setOutlineThickness(2.0f);
	line.setOutlineColor(sf::Color::Black);

    window.draw(line);  
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(view_height*2, view_height), "Billiards game", sf::Style::Close | sf::Style::Titlebar 
		| sf::Style::Resize);
	sf::View view(sf::Vector2f(view_height, view_height/2), sf::Vector2f(2 * view_height, view_height));

	vec2f tableStart(60.0f, 60.0f);
	vec2f tableSize(896.0f, 448.0f);
	Table table(tableStart ,tableSize, 26.0f);

	
	float r = 12.0f;
	int ballCount = 16; 
	std::vector<Ball> balls;
	balls.reserve(ballCount);
	unsigned int colors[15] = {0xFFFF00FF,0x0000FFFF,0xFF0000FF,0x800080FF,0xFFA500FF,0x01FD00FF,0x800000FF,0x000000FF
		,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF };
	float sqr3 = sqrtf(3);
	vec2f InitPos[15] = { 
		{0.0f,0.0f}
		,{r * sqrtf(3),r}
		,{r * sqrtf(3) ,-r}
		,{r * sqrtf(3) * 2,r * 2}
		,{r * sqrtf(3) * 2,0.0f}
		,{r * sqrtf(3) * 2,r * -2}
		,{r * sqrtf(3) * 3,r * 3}
		,{r * sqrtf(3) * 3,r}
		,{r * sqrtf(3) * 3,-r}
		,{r * sqrtf(3) * 3,r * -3}
		,{r * sqrtf(3) * 4,r * 4}
		,{r * sqrtf(3) * 4,r * 2}
		,{r * sqrtf(3) * 4,r * -2}
		,{r * sqrtf(3) * 4,r * -4}
		,{r * sqrtf(3) * 4,0.0f}

	};

	balls.emplace_back( Ball({ table.start.x + table.size.x / 4,
							   table.start.y + table.size.y / 2 }, 
							   sf::Color::White, r, -1));
	for (int i = 0; i < ballCount-1; i++) {
		balls.emplace_back(Ball({ tableStart.x+InitPos[i].x+650.0f ,
								  tableStart.y + tableSize.y / 2 + InitPos[i].y}, 
								  sf::Color(colors[i]), r, i));
	}
	

	float deltaTime = 0.0f;
	sf::Clock clock;

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			balls[0].vel = {0.0f,0.0f};
		}

		view.setCenter(tableStart.x + tableSize.x / 2, tableStart.y + tableSize.y / 2);
		window.clear(sf::Color::White);
		window.setView(view);

		


		table.Draw(window);

		for (int i = 0; i < ballCount;++i) {
			balls[i].Draw(window);
			balls[i].MoveBall(deltaTime);
			balls[i].CollidingWithTable(table);

			if (balls[i].InPocket(table)) {
				if (i == 0) {
					balls[0].pos.x = table.start.x + table.size.x / 4;
					balls[0].pos.y = table.start.y + table.size.y / 2;
					balls[0].vel = { 0, 0 };
				}
				else {
					balls[i].pos.x = 10000;
				}
			}
		}

		balls[0].AimingCueBall(window, velocityVector);
		DrawVector({ balls[0].pos.x,balls[0].pos.y}, velocityVector, window);
		balls[0].Draw(window);
		for (int i = 0; i < ballCount-1; i++) {
			for (int j = i + 1; j < ballCount; j++) {
				balls[i].CollidingWithBall(balls[j]);
			}
		}

		window.display();
	}
}