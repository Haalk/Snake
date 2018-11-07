#include "Snake.h"

#include <cstdlib>
#include <ctime>

using namespace std;

Snake::Snake()
{

}
Snake::~Snake()
{
}

bool Snake::move()
{
	good = true;
	if (_kbhit())
		switch (_getch())
		{
		case snake_direction::LEFT:if (m_dir != snake_direction::RIGHT)m_dir = LEFT; break;
		case snake_direction::RIGHT:if (m_dir != snake_direction::LEFT)m_dir = RIGHT; break;
		case snake_direction::UP:if (m_dir != snake_direction::DOWN)m_dir = UP; break;
		case snake_direction::DOWN:if (m_dir != snake_direction::UP)m_dir = DOWN; break;
		case snake_direction::PAUSE:_getch(); break;
		case snake_direction::EXIT:return false;
		}
	setCursorPosition(snake_head.x, snake_head.y);
	cout << ' ';
	if (nTail > 0) 
		swap_tails();
	switch (m_dir)
	{
	case LEFT:if (snake_head.x > 1 && m_dir!=snake_direction::RIGHT)snake_head.x--; else good = false;
		break;
	case RIGHT:if (snake_head.x < FIELD_WIDTH-1 && m_dir != snake_direction::LEFT)snake_head.x++; else good = false;
		break;
	case UP:if (snake_head.y > 1 && m_dir != snake_direction::DOWN)snake_head.y--; else good = false;
		break;
	case DOWN:if (snake_head.y < FIELD_HEIGHT-1 && m_dir != snake_direction::UP)snake_head.y++; else good = false;
		break;
	}
	for (int i = 0; i < nTail; i++)
		if (snake_tail[i].x == snake_head.x && snake_tail[i].y == snake_head.y)
			good = false;
	if (snake_head.x == fruitX && snake_head.y == fruitY)
		fruit_score();
	show_snake();
	Sleep(120);
	return good;
}

void Snake::setCursorPosition(int x, int y) const
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

int Snake::return_score() const
{
	return score;
}

std::string Snake::get_nameSnake() const
{
	return snake_name;
}

void Snake::set_nameSnake()
{
	setCursorPosition(FIELD_WIDTH/2-15, FIELD_HEIGHT/2+2);
	std::cout << "Enter your name: ";
	std::cin >> snake_name;
	while (std::cin.get() != '\n')
		continue;
}

void Snake::reset_snake()
{
	nTail = 0;
	snake_tail.resize(nTail);
	tails_colour.resize(nTail);
	int colour_fr = (rand() % 15) + 1;
	tails_colour.push_back(colour_fr);
	m_dir = STOP;
	score = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	setCursorPosition(0, FIELD_HEIGHT + 1);
	cout << "SCORE: " << score;
	SetConsoleTextAttribute(hConsole, 15);
	snake_head.x = FIELD_WIDTH / 2 - 1;
	snake_head.y = (FIELD_HEIGHT - 2);
	srand(time(NULL));
	fruitX = rand() % (FIELD_WIDTH - 1) + 1;
	fruitY = rand() % (FIELD_HEIGHT - 2) + 1;
	SetConsoleTextAttribute(hConsole, colour_fr);
	setCursorPosition(fruitX, fruitY);
	cout << '*';
	SetConsoleTextAttribute(hConsole, 15);
	good = true;
}

void Snake::show_snake() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	setCursorPosition(snake_head.x, snake_head.y);
	cout << 'O';
	SetConsoleTextAttribute(hConsole, 15);

	for (int k = 0; k < nTail; k++)
	{
		if (snake_tail[k].x == 0 && snake_tail[k].y == 0)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			setCursorPosition(snake_tail[k].x, snake_tail[k].y);
			std::cout << '#';
			SetConsoleTextAttribute(hConsole, 15);
		}
		else
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole,tails_colour[k]);
			setCursorPosition(snake_tail[k].x, snake_tail[k].y);
			std::cout << 'o';
			SetConsoleTextAttribute(hConsole, 15);
		}
	}
}

void Snake::swap_tails()
{
	int prevX;
	int prevY;
	int prev2X, prev2Y;
	for (int k = 0; k < nTail; k++)
	{
		setCursorPosition(snake_tail[k].x, snake_tail[k].y);
		cout << ' ';
		if (snake_tail[k].x == 0 && snake_tail[k].y == 0)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			setCursorPosition(0, 0);
			cout << '#';
			SetConsoleTextAttribute(hConsole, 15);
		}
	}
	prevX = snake_tail[0].x;
	prevY = snake_tail[0].y;
	snake_tail[0].x = snake_head.x;
	snake_tail[0].y = snake_head.y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = snake_tail[i].x;
		prev2Y = snake_tail[i].y;
		snake_tail[i].x = prevX;
		snake_tail[i].y = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
}

void Snake::fruit_score()
{
	setCursorPosition(snake_head.x, snake_head.y);
	cout << ' ';
	bool food_good = false;
	int colour_fr = (rand() % 15)+1;
	fruitX = rand() % (FIELD_WIDTH - 3);
	fruitY = rand() % (FIELD_HEIGHT - 3);
	while (!food_good)
	{
		for (int k = 0; k < nTail; k++)
		{
			if ((snake_tail[k].x == fruitX && snake_tail[k].y == fruitY) || fruitY == 0 || fruitY>FIELD_HEIGHT - 2 || fruitX == 0 || fruitX == FIELD_WIDTH - 1)
			{
				fruitX = (rand() % (FIELD_WIDTH - 1)) + 1;
				fruitY = (rand() % (FIELD_HEIGHT - 2)) + 1;
				k = 0;
			}
		}
		food_good = true;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, colour_fr);
		setCursorPosition(fruitX, fruitY);
		cout << '*';
		SetConsoleTextAttribute(hConsole, 15);
	}
	++nTail;
	snake_tail.resize(nTail);
	tails_colour.push_back(colour_fr);
	score += 10;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	setCursorPosition(0, FIELD_HEIGHT + 1);
	cout << "SCORE: " << score;
	SetConsoleTextAttribute(hConsole, 15);
}