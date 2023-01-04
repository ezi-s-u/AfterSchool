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

const int W_WIDTH = 880, W_HEIGHT = 680;   // â�� ũ��

int main(void)
{
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MyProject");
	window.setFramerateLimit(60);

	struct Player p;
	p.sprite.setSize(Vector2f(70, 70));
	p.sprite.setPosition(440, 340);
	p.sprite.setFillColor(Color::Magenta);
	p.speed = 7;

	// ������ �������� ������ �ݺ�
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// ����(x) ��ư�� ������ Event::Closed(0)
			case Event::Closed:
				window.close();  // ������ �ݴ´�
			}
		}

		// ����Ű ���� start
		if (Keyboard::isKeyPressed(Keyboard::Left)) // else�� ���� Ű�� ���ÿ� ���� �� �ٸ� ����� ������� ����
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
		} // ����Ű ���� end

		window.clear(Color::Black);

		window.draw(p.sprite);

		window.display();
	}

	return 0;
}