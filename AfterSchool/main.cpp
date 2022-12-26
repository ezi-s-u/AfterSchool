#include<stdio.h>
#include<SFML/Graphics.hpp>

using namespace sf;

int main(void)
{
	// 윈도창 생성
	RenderWindow window(VideoMode(640, 480),"AfterSchool");
	window.setFramerateLimit(60); // 1초에 60장을 보여주겠다는 의미

	RectangleShape player;
	player.setSize(Vector2f(40, 40));
	player.setPosition(100, 100);
	player.setFillColor(Color::Red);
	int player_speed = 5; // player의 속도 변수처리

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
		}

		// 계속 그려져야 하기 때문에 반복문 안에 넣어야 함
		window.clear(Color::Black);
		window.draw(player); // 윈도 화면에 player를 그려주겠다는 코드
		window.display();
	}

	return 0;
}