// GameApp.cpp : Defines the entry point for the application.
//
#define NOMINMAX
// Windows Header Files
#include <Windows.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sf;
constexpr auto GAME_NAME = "Snake Game";
enum class Screen {
    WIDTH = 640,
    HEIGHT = 480
};

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * M;

int dir, num = 4;

struct Snake
{
    int x, y;
} s[100];

struct Fruit
{
    int x, y;
} f;

void Tick()
{
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    if (dir == 0)
        s[0].y += 1;
    if (dir == 1)
        s[0].x -= 1;
    if (dir == 2)
        s[0].x += 1;
    if (dir == 3)
        s[0].y -= 1;

    if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
    }

    if (s[0].x > N)
        s[0].x = 0;
    if (s[0].x < 0)
        s[0].x = N;
    if (s[0].y > M)
        s[0].y = 0;
    if (s[0].y < 0)
        s[0].y = M;

    for (int i = 1; i < num; i++){
        if (s[0].x == s[i].x && s[0].y == s[i].y){
            num = i;
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, // HANDLE TO AN INSTANCE.  This is the "handle" to YOUR PROGRAM ITSELF.
    HINSTANCE hPrevInstance,            // USELESS on modern windows (totally ignore hPrevInstance)
    LPSTR szCmdLine,                    // Command line arguments.  similar to argv in standard C programs
    int iCmdShow)                       // Start window maximized, minimized, etc.
{
    srand(time(0));
    Texture t1;
    Texture t2;
    t1.loadFromFile("assets/images/white.png");
    t2.loadFromFile("assets/images/red.png");
    
    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer = 0;
    float delay = 0.1f;

    f.x = 10;
    f.y = 10;

    sf::RenderWindow window(sf::VideoMode(w, h), GAME_NAME);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
            dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right))
            dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up))
            dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down))
            dir = 0;

        if (timer > delay)
        {
            timer = 0;
            Tick();
        }

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                sprite1.setPosition(i * size, j * size);
                window.draw(sprite1);
            }

        for (int i = 0; i < num; i++)
        {
            sprite2.setPosition(s[i].x * size, s[i].y * size);
            window.draw(sprite2);
        }

        sprite2.setPosition(f.x * size, f.y * size);
        window.draw(sprite2);

        window.display();
    }
    return EXIT_SUCCESS;
}