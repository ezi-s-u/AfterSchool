#include<stdio.h>
#include<SFML/Graphics.hpp>
#include<stdlib.h>
#include<time.h>
#include<SFML/Audio.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int speed;
	int score;
	int life;
};

const int W_WIDTH = 880, W_HEIGHT = 680;   // 창의 크기

int main(void)
{
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MyProject");
	window.setFramerateLimit(60);

	struct Player p;
	p.sprite.setSize(Vector2f(80, 80));
	p.sprite.setPosition(440, 340);
	p.sprite.setFillColor(Color::Magenta);

	// 윈도가 열려있을 때까지 반복
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// 종료(x) 버튼을 누르면 Event::Closed(0)
			case Event::Closed:
				window.close();  // 윈도를 닫는다
			}
		}

		window.draw(p.sprite);

		window.display();
	}

	return 0;
}