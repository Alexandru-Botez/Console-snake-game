#include<iostream>
#include<conio.h>
#include<windows.h>
#include<random>
#include<time.h>
#include<chrono>
#include<array>

enum Directions { STOP, UP, DOWN, RIGHT, LEFT };
Directions direction{ STOP };
Directions lastDir;
bool chiudi = false;
int index{0};
bool pause{};

namespace constants
{
    constexpr int height{ 25 };
    constexpr int weight{ 50 };
}

namespace random
{
    std::mt19937 mt{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };
    std::uniform_int_distribution weightR{ 1,48 };
    std::uniform_int_distribution heightR{ 1,23 };
}

namespace elements
{
    int snakeHx{ 5 };
    int snakeHy{ 9 };
    std::array<int, 100> snakeEx{};
    std::array<int, 100> snakeEy{};
    int snake_lenght{ 0 };
    int fruitX{ random::weightR(random::mt) };
    int fruitY{ random::heightR(random::mt) };
    int score{ 0 };
}





void draw()
{
    for (int gridY{ 0 }; gridY < constants::height; ++gridY)
    {
        for (int gridX{ 0 }; gridX < constants::weight; ++gridX)
        {

            if (gridY == 0 || gridX == 0 || gridY == constants::height - 1 || gridX == constants::weight - 1)
            {
                std::cout << "#";
            }
            else if (gridY == elements::snakeHy && gridX == elements::snakeHx)
            {
                std::cout << "O";
            }
            else if (gridY == elements::fruitY && gridX == elements::fruitX)
            {
                std::cout << "F";
            }
            else
            {
                bool print = false;
                for (int i{ 0 }; i < elements::snake_lenght; ++i)
                {
                    if (elements::snakeEx[i] == gridX && elements::snakeEy[i] == gridY)
                    {
                        std::cout << "o";
                        print = true;
                    }
               
                }

                if(!print)
                    std::cout << " ";

            }
                




        }
        std::cout << '\n';
    }

    // display the score
    std::cout << "score: " << elements::score;

    // if the snake head picks the fruit 
    if (elements::snakeHy == elements::fruitY && elements::snakeHx == elements::fruitX)
    {
        elements::fruitX = random::weightR(random::mt);
        elements::fruitY = random::heightR(random::mt);

        for(int i{1}; i < elements::snake_lenght; ++i)
        {
            if (elements::snakeEy[i] == elements::fruitY && elements::snakeEx[i] == elements::fruitX)
            {
                elements::fruitX = random::weightR(random::mt);
                elements::fruitY = random::heightR(random::mt);

            }
        }
       

        // increment by 1 the score and lenght of the snake
        ++elements::score;
        ++elements::snake_lenght;


    }

   

    switch (elements::snakeHy)
    {
        case constants::height - 1:         elements::snakeHy = 1;  break;
        case 0:                             elements::snakeHy = 24; break;
    }
   
    switch (elements::snakeHx)
    {
        case constants::weight - 1:     elements::snakeHx = 1; break;
        case 0:                         elements::snakeHx = 49; break;
    }

}

void input()
{
    bool pause{false};

    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
        case 'A':
            if (direction == RIGHT)
            {
                break;
            }

            direction = LEFT;
            break;
        case 'd':
        case 'D':
            if (direction == LEFT)
            {
                break;
            }
          

            direction = RIGHT;
            break;
        case 's':
        case 'S':
            if (direction == UP)
            {
                break;
            }
            direction = DOWN;
            break;
        case 'w':
        case 'W':
            if (direction == DOWN)
            {
                break;
            }
            direction = UP;
            break;

        case 'p':
        case 'P':

            
            pause = true;

            while (pause)
            {
                if (_kbhit())
                {
                    if (_getch() == 'p' || _getch() == 'P')
                    {
                        pause = false;
                    }
                }
            }

            break;

        case 'x':
            chiudi = true;
        }
    }

}

void logic()
{
    int prevX = elements::snakeEx[0];
    int prevY = elements::snakeEy[0];
    int tempx{};
    int tempy{};
    elements::snakeEx[0] = elements::snakeHx;
    elements::snakeEy[0] = elements::snakeHy;

    for (int i{ 0 }; i <= elements::snake_lenght; ++i)
    {
        tempx = elements::snakeEx[i];
        tempy = elements::snakeEy[i];

        elements::snakeEx[i] = prevX;
        elements::snakeEy[i] = prevY;

        prevX = tempx;
        prevY = tempy;

    }



    switch (direction)
    {
    case UP:
        --elements::snakeHy;
        break;
    case DOWN:
        ++elements::snakeHy;
        break;
    case RIGHT:
        ++elements::snakeHx;
        break;
    case LEFT:
        --elements::snakeHx;
        break;
    default:
        break;
    }

    for (int i{ 0 }; i < elements::snake_lenght; ++i)
    {
        if (elements::snakeEx[i] == elements::snakeHx && elements::snakeEy[i] == elements::snakeHy)
            chiudi = true;

    }

}

int main()
{

    srand(time(NULL));

    while (!chiudi)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
        draw();
        input();
        logic();
        Sleep(25);
    }
}
