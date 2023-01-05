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
	int respawn_time;
};

// obj1과 obj2의 충돌여부. 충돌하면 1을 반환, 충돌안하면 0을 반환.
int is_collide(RectangleShape obj1, RectangleShape obj2)
{
	return obj1.getGlobalBounds().intersects(obj2.getGlobalBounds());
}

const int W_WIDTH = 880, W_HEIGHT = 680;   // 창의 크기
const int OBSTACLE_COUNT = 5;              // 장애물 개수

int main(void)
{
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MyProject");
	window.setFramerateLimit(60);

	srand((unsigned int)time(NULL));

	long start_time = clock();
	long spent_time;

	struct Player p;
	p.sprite.setSize(Vector2f(50, 50));
	p.sprite.setPosition(440, 340);
	p.sprite.setFillColor(Color::Magenta);
	p.speed = 13;
	p.score = 0;

	struct Obstacle oLeft[OBSTACLE_COUNT];
	struct Obstacle oRight[OBSTACLE_COUNT];

	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		oLeft[i].sprite.setSize(Vector2f(30, 30));
		oLeft[i].sprite.setPosition(rand() % -100, rand() % 680);
		oLeft[i].sprite.setFillColor(Color::White);
		oLeft[i].speed = 10;
		oLeft[i].life = 1;

		oRight[i].sprite.setSize(Vector2f(30, 30));
		oRight[i].sprite.setPosition(rand() % 980 + W_WIDTH, rand() % 680);
		oRight[i].sprite.setFillColor(Color::White);
		oRight[i].speed = 10;
		oRight[i].life = 1;
	}

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

		spent_time = clock() - start_time;

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

		for (int i = 0; i < OBSTACLE_COUNT; i++)
		{
			// 10초마다 적(enemy)이 젠
			if (spent_time % 1000 < 1000 / 60 + 1)
			{
				oLeft[i].sprite.setSize(Vector2f(70, 70));
				oLeft[i].sprite.setPosition(rand() % -100, rand() % 680);
				oLeft[i].sprite.setFillColor(Color::White);
				oLeft[i].speed = 15;
				oLeft[i].life = 1;

				oRight[i].sprite.setSize(Vector2f(70, 70));
				oRight[i].sprite.setPosition(rand() % 980 + W_WIDTH, rand() % 680);
				oRight[i].sprite.setFillColor(Color::White);
				oRight[i].speed = 15;
				oRight[i].life = 1;
				// 10초마다 적(enemy)의 속도 +1
				oLeft[i].speed += 1;
				oRight[i].speed += 1;
			}

			if (oLeft[i].life > 0)
			{
				// player, obstacle 충돌
				if (is_collide(p.sprite, oLeft[i].sprite))// 충돌했을 때
				{
					p.life -= 1;
					oLeft[i].life = 0;
				}

				// 적이 왼쪽 끝에 진입하려는 순간
				else if (oLeft[i].sprite.getPosition().x > 880)
				{
					oLeft[i].life = 0;
				}

				oLeft[i].sprite.move(oLeft[i].speed, 0);
			}

			if (oRight[i].life > 0)
			{
				if (is_collide(p.sprite, oRight[i].sprite))// 충돌했을 때
				{
					p.life -= 1;
					oRight[i].life = 0;
				}
				// 적이 왼쪽 끝에 진입하려는 순간
				else if (oRight[i].sprite.getPosition().x < 0)
				{
					oRight[i].life = 0;
				}

				oRight[i].sprite.move(-oRight[i].speed, 0);
			}

			printf("%d\n", p.score);





			window.clear(Color::Black);

			for (int i = 0; i < OBSTACLE_COUNT; i++)
			{
				if (oLeft[i].life > 0)
					window.draw(oLeft[i].sprite);
				if (oRight[i].life > 0)
					window.draw(oRight[i].sprite);
			}
			window.draw(p.sprite);

			window.display();
		}
	}
}