#include<stdio.h>
#include<SFML/Graphics.hpp>
#include<stdlib.h>
#include<time.h>

using namespace sf;

int main(void)
{
	// 윈도창 생성
	RenderWindow window(VideoMode(640, 480),"AfterSchool");
	window.setFramerateLimit(60); // 1초에 60장을 보여주겠다는 의미

	srand(time(0));

	RectangleShape player;
	player.setSize(Vector2f(40, 40));
	player.setPosition(100, 100);
	player.setFillColor(Color::Red);
	int player_speed = 5; // player의 속도 변수처리
	int player_score = 0;

	RectangleShape enemy[5];
	int enemy_life[5];
	int enemy_score = 100;   // 적을 잡을 때 얻는 점수
	// enemy 초기화
	for (int i = 0; i < 5; i++)
	{
		enemy[i].setSize(Vector2f(70, 70));
		enemy[i].setFillColor(Color::Yellow);
		enemy_life[i] = 1;
		enemy[i].setPosition(rand()%300+200, rand()%380);
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
				break;
			// 키보드를 눌렀을 때(누른 순간만을 감지)
			case Event::KeyPressed:
			{
				// 스페이스 바 누르면 모든 enemy 다시 출현
				if (event.key.code == Keyboard::Space)
				{
					for (int i = 0; i < 5; i++)
					{
						enemy[i].setSize(Vector2f(70, 70));
						enemy[i].setFillColor(Color::Yellow);
						enemy_life[i] = 1;
						enemy[i].setPosition(rand() % 300 + 200, rand() % 380);
					}
				}
				break;
			}

			}
		}

		// 방향키 설정 start
		if (Keyboard::isKeyPressed(Keyboard::Left)) // else를 쓰면 키를 동시에 누를 때 다른 명령은 실행되지 않음
		{
			player.move(-player_speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.move(player_speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.move(0, -player_speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.move(0, player_speed);
		} // 방향키 설정 end


		// enemy와의 충돌
		for (int i = 0; i < 5; i++)
		{
			if (enemy_life[i] > 0) // enemy가 살아있을 때만 충돌처리
			{
				if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds())) // 충돌했을 때
				{
					printf("enemy[%d]와 충돌\n",i);
					enemy_life[i] -= 1;
					player_score += enemy_score;
				}
			}
		}

		printf("score : %d\n", player_score);

		// 계속 그려져야 하기 때문에 반복문 안에 넣어야 함
		
		window.clear(Color::Black);

		// draw는 나중에 호출할수록 우선순위가 높아짐 ★★★
		for (int i = 0; i < 5; i++) {
			if (enemy_life[i] > 0)
				window.draw(enemy[i]);
		}
		window.draw(player);

		window.display();
	}

	return 0;
}