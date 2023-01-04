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
	int life = 1;
};

struct Obstacle {
	RectangleShape sprite;
	int speed;
	int life;
};

// obj1�� obj2�� �浹����. �浹�ϸ� 1�� ��ȯ, �浹���ϸ� 0�� ��ȯ.
int is_collide(RectangleShape obj1, RectangleShape obj2)
{
	return obj1.getGlobalBounds().intersects(obj2.getGlobalBounds());
}

const int W_WIDTH = 880, W_HEIGHT = 680;   // â�� ũ��
const int OBSTACLE_COUNT = 5;              // ��ֹ� ����

int main(void)
{
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MyProject");
	window.setFramerateLimit(60);

	srand((unsigned int)time(NULL));

	struct Player p;
	p.sprite.setSize(Vector2f(70, 70));
	p.sprite.setPosition(440, 340);
	p.sprite.setFillColor(Color::Magenta);
	p.speed = 7;
	p.score = 0;

	struct Obstacle oLeft[OBSTACLE_COUNT];
	struct Obstacle oRight[OBSTACLE_COUNT];

	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		oLeft[i].sprite.setSize(Vector2f(70, 70));
		oLeft[i].sprite.setPosition(rand() % -100, rand() % 680);
		oLeft[i].sprite.setFillColor(Color::White);
		oLeft[i].speed = 7;
		oLeft[i].life = 1;
	}

	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		oRight[i].sprite.setSize(Vector2f(70, 70));
		oRight[i].sprite.setPosition(rand() % -100, rand() % 680);
		oRight[i].sprite.setFillColor(Color::White);
		oRight[i].speed = 7;
		oRight[i].life = 1;
	}

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

		for (int i = 0; i < OBSTACLE_COUNT; i++)
		{
			// player, obstacle �浹
			if (is_collide(p.sprite, oLeft[i].sprite))// �浹���� ��
			{
				p.life -= 1;
			}
			oLeft[i].sprite.move(oLeft[i].speed, 0);
		}
		printf("%d\n", p.score);





		window.clear(Color::Black);

		for (int i = 0; i < OBSTACLE_COUNT; i++)
		{
			window.draw(oLeft[i].sprite);
		}
		window.draw(p.sprite);

		window.display();
	}

	return 0;
}