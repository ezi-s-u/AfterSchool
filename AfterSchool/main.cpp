#include<stdio.h>
#include<SFML/Graphics.hpp>
#include<stdlib.h>
#include<time.h>
#include<SFML/Audio.hpp>
#include<Windows.h>

using namespace sf;
struct Player {
	RectangleShape sprite;
	int speed;
	int score;
	int life;
	float x, y;   // 플레이어 좌표
};

struct Bullet {
	RectangleShape sprite;
	int speed;
	int is_fired;    // 발사 여부
};

struct Enemy {
	RectangleShape sprite;
	int speed;
	int life;
	int score;
	SoundBuffer explosion_buffer;
	Sound explosion_sound;
	int respawn_time;
};

struct Textures {
	Texture bg;        // 배경 이미지
	Texture enemy;     // 적 이미지
	Texture gameover;  // 게임오버 이미지
	Texture player;    // 플레이어 이미지
};

// obj1과 obj2의 충돌여부. 충돌하면 1을 반환, 충돌안하면 0을 반환.
int is_collide(RectangleShape obj1, RectangleShape obj2)
{
	return obj1.getGlobalBounds().intersects(obj2.getGlobalBounds());
}

// 전역변수
const int ENEMY_NUM = 6;  // 적(enemy)의 개수
const int W_WIDTH = 1200, W_HEIGHT = 600;   // 창의 크기
const int GO_WIDTH = 320, GO_HEIGHT = 240;  // 게임오버 화면의 크기

int main(void)
{
// console을 가리기 위한 방법
// WARNING 이 방법은 콘솔창을 제거하는 것이 아니라 메모리 낭비가 됨
#ifdef WIN32
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
#endif

	struct Textures t;
	t.bg.loadFromFile("./resources/images/background.jpg");
	t.enemy.loadFromFile("./resources/images/enemy.png");
	t.gameover.loadFromFile("./resources/images/gameover.png");
	t.player.loadFromFile("./resources/images/player.png");

	// 윈도창 생성
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AfterSchool");
	window.setFramerateLimit(60); // 1초에 60장을 보여주겠다는 의미

	srand(time(0));

	long start_time = clock();  // 게임 시작시간
	long spent_time;            // 게임 진행시간
	int is_gameover = 0;

	// BGM
	SoundBuffer BGM_buffer;
	BGM_buffer.loadFromFile("./resources/sounds/bgm.ogg");
	Sound BGM_sound;
	BGM_sound.setBuffer(BGM_buffer);
	BGM_sound.setLoop(1);    // BGM 무한반복
	BGM_sound.play();

	// text
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(Color(255, 255, 255));
	text.setPosition(5, 0);
	char info[40];

	// 배경
	Sprite bg_sprite;
	bg_sprite.setTexture(t.bg);
	bg_sprite.setPosition(0, 0);

	// 게임오버 화면
	Sprite go_sprite;
	go_sprite.setTexture(t.gameover);
	go_sprite.setPosition((W_WIDTH - GO_WIDTH) / 2, (W_HEIGHT - GO_HEIGHT) / 2);


	// 플레이어(player)
	struct Player player;
	player.sprite.setSize(Vector2f(170, 78));
	player.sprite.setTexture(&t.player);
	player.sprite.setPosition(100, 100);
	player.x = player.sprite.getPosition().x;
	player.y = player.sprite.getPosition().y;
	player.speed = 7;
	player.score = 0;
	player.life = 10;

	// 총알
	struct Bullet bullet;
	bullet.sprite.setSize(Vector2f(10, 10));
	bullet.sprite.setPosition(player.x + 50, player.y + 15);   // 임시 테스트
	bullet.speed = 20;
	bullet.is_fired = 0;

	// 적(enemy)
	struct Enemy enemy[ENEMY_NUM];


	// enemy 초기화
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// TODO : 굉장히 비효율적인 코드이므로 나중에 refactoring
		enemy[i].explosion_buffer.loadFromFile("./resources/sounds/boom.flac");
		enemy[i].explosion_sound.setBuffer(enemy[i].explosion_buffer);
		enemy[i].score = 100;   // 적을 잡을 때 얻는 점수
		enemy[i].respawn_time = 8;

		enemy[i].sprite.setTexture(&t.enemy);
		enemy[i].sprite.setSize(Vector2f(150, 71));
		enemy[i].sprite.setFillColor(Color::Yellow);
		enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
		enemy[i].life = 1;
		enemy[i].speed = -(rand() % 7 + 1);
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
				//// 스페이스 바 누르면 모든 enemy 다시 출현
				//if (event.key.code == Keyboard::Space)
				//{
				//	for (int i = 0; i < ENEMY_NUM; i++)
				//	{
				//		enemy[i].sprite.setSize(Vector2f(70, 70));
				//		enemy[i].sprite.setFillColor(Color::Yellow);
				//		enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
				//		enemy[i].life = 1;
				//		enemy[i].speed = -(rand() % 10 + 1);
				//	}
				//}
				//break;
			}

			}
		}

		spent_time = clock() - start_time;
		player.x = player.sprite.getPosition().x;
		player.y = player.sprite.getPosition().y;

		// 방향키 설정 start
		if (Keyboard::isKeyPressed(Keyboard::Left)) // else를 쓰면 키를 동시에 누를 때 다른 명령은 실행되지 않음
		{
			player.sprite.move(-player.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.sprite.move(player.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.sprite.move(0, -player.speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.sprite.move(0, player.speed);
		} // 방향키 설정 end

		if (event.key.code == Keyboard::Space)
		{
			// 총알이 발사되어있지 않다면
			if (!bullet.is_fired)
			{
				bullet.sprite.setPosition(player.x + 50, player.y + 15);
				bullet.is_fired = 1;
			}
			// 스페이스 바를 누르지 않은 상태에서도 계속 움직여야하니까 if문 바깥에 있어야함
			bullet.sprite.move(bullet.speed, 0);
		}

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			// 10초마다 적(enemy)이 젠
			if (spent_time % (1000 * enemy[i].respawn_time) < 1000 / 60 + 1)
			{
				enemy[i].sprite.setSize(Vector2f(150, 71));
				enemy[i].sprite.setFillColor(Color::Yellow);
				enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
				enemy[i].life = 1;
				// 10초마다 적(enemy)의 속도 +1
				enemy[i].speed = -(rand() % 10 + 1 + (spent_time / 10000 / enemy[i].respawn_time));
			}
			if (enemy[i].life > 0) // enemy가 살아있을 때만 충돌처리
			{
				// player, enemy 충돌
				if (is_collide(player.sprite, enemy[i].sprite))// 충돌했을 때
				{
					enemy[i].life -= 1;
					player.score += enemy[i].score;

					// TODO : 코드 refactoring 필요
					if (enemy[i].life == 0)
					{
						enemy[i].explosion_sound.play();
					}
				}
				// 적이 왼쪽 끝에 진입하려는 순간
				else if (enemy[i].sprite.getPosition().x < 0)
				{
					player.life -= 1; // player의 목숨 감소
					enemy[i].life = 0;
				}

				if(is_collide(bullet.sprite, enemy[i].sprite))
				{
					enemy[i].life -= 1;
					player.score += enemy[i].score;

					// TODO : 코드 refactoring 필요
					if (enemy[i].life == 0)
					{
						enemy[i].explosion_sound.play();
					}
					bullet.is_fired = 0;
				}

				enemy[i].sprite.move(enemy[i].speed, 0);
			}
		}

		if (bullet.is_fired)
		{
			bullet.sprite.move(bullet.speed, 0);
			if (bullet.sprite.getPosition().x > W_WIDTH)
				bullet.is_fired = 0;
		}

		if (player.life <= 0)
		{
			is_gameover = 1;
		}

		sprintf(info, "life:%d  score:%d  time:%d\n", player.life, player.score, spent_time / 1000);
		text.setString(info);

		// 계속 그려져야 하기 때문에 반복문 안에 넣어야 함

		window.clear(Color::Black);

		// draw는 나중에 호출할수록 우선순위가 높아짐
		window.draw(bg_sprite);
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (enemy[i].life > 0)
				window.draw(enemy[i].sprite);
		}
		window.draw(player.sprite);
		window.draw(text);
		if(bullet.is_fired)
			window.draw(bullet.sprite);

		if (is_gameover)
		{
			window.draw(go_sprite);
			// TODO : 게임이 멈추는 것을 구현할 것
		}

		window.display();
	}

	return 0;
}