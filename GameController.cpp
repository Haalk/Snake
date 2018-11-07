#include "GameController.h"

GameController::GameController()
{
	snake = new Snake;
	field = new Field;
}

GameController::~GameController()
{
	delete snake;
	delete field;
}

bool GameController::request_play()
{
	char ch;
	field->setCursorPosition(FIELD_WIDTH / 3, FIELD_HEIGHT / 2);
	std::cout << "You lose " << snake->get_nameSnake() << "! Your score " << snake->return_score() << std::endl;
	field->setCursorPosition(FIELD_WIDTH / 3, FIELD_HEIGHT / 2+1);
	std::cout << "Try again ? <(y)to play again> : ";
	ch=std::cin.get();
	if (ch != 'y' && ch != 'Y')
		return false;
	while (std::cin.get() != '\n')
		continue;
	snake->set_nameSnake();
	return true;
}

void GameController::Menu()
{
	using std::cout;
	using std::cin;
	using std::endl;
	field->setCursorPosition(FIELD_WIDTH / 3,0);
	cout << "SNAKE" << endl;
	cout << "1.Play" << endl;
	cout << "2.Scores" << endl;
	cout << "3.Help" << endl;
	cout << "4.Quit" << endl;
}

void GameController::Play()
{
	bool isGame;
	bool Play = true;
	field->drawfield();
	snake->reset_snake();
	isGame = true;
	while (isGame)
		isGame = snake->move();
	if (field->beat_record(snake->return_score()))
	{
		snake->set_nameSnake();
		field->set_record(snake->get_nameSnake(), snake->return_score());
	}
	else
		_getch();
}

void GameController::hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void GameController::Game()
{
	hidecursor();
	field->Hello();
	char choice = 0;
	while (choice != 3)
	{
		Menu();
		choice = _getch();
		switch (choice)
		{
		case '1':Play();break;
		case '2':field->score_table(); break;
		case '3':field->Help(); break;
		case '4':choice = 3; break;
		}
		system("cls");
	}
	field->Bye();
	_getch();
}
