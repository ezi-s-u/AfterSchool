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
	p.sprite.setSize(Vector2f(70, 70));
	p.sprite.setPosition(440, 340);
	p.sprite.setFillColor(Color::Magenta);
	p.speed = 7;

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

		// 방향키 설정 start
		if (Keyboard::isKeyPressed(Keyboard::Left)) // else를 쓰면 키를 동시에 누를 때 다른 명령은 실행되지 않음
		{
			p.sprite.move(-p.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.sprite.move(p.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			p.sprite.move(0, -p.speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			p.sprite.move(0, p.speed);
		} // 방향키 설정 end

		window.clear(Color::Black);

		window.draw(p.sprite);

		window.display();
	}

	return 0;
}