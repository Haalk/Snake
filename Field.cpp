#include "Field.h"
#include <fstream>
#include <iomanip>
#include <algorithm>


Field::Field()
{
	m_scores.resize(SIZE_SCORES);
	std::ifstream fin;
	fin.open(File_name);
	if (!fin.is_open())
	{
		std::ofstream fout;
		fout.open(File_name);
		fout.close();
	}
	std::string temp;
	int temp_val;
	int i = 0;
	while (i!= SIZE_SCORES)
	{
		if(fin >> temp)
			fin >> temp_val;
		else
		{
			temp = "noname";
			temp_val = 0;
		}
		m_scores[i].first = temp;
		m_scores[i++].second = temp_val;	
	}
	fin.close();
}

Field::~Field()
{
}

void Field::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void Field::drawfield()
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,4 );
	for (int i = 0; i <= FIELD_WIDTH; ++i)
		for (int j = 0; j <= FIELD_HEIGHT; ++j)
			if (i == 0 || i == FIELD_WIDTH || j == 0 || j == FIELD_HEIGHT)
			{
				setCursorPosition(i, j);
				std::cout <<'#';
			}
	SetConsoleTextAttribute(hConsole, 15);
}

void Field::Hello()
{
	using std::cout;
	setCursorPosition(FIELD_WIDTH / 3, FIELD_HEIGHT / 2);
	cout << "Hello!";
	setCursorPosition(FIELD_WIDTH / 3, FIELD_HEIGHT / 2);
	cout << "It is game <SNAKE> by Denis";
	while (std::cin.get() != '\n')
		continue;
}

void Field::Bye()
{
	system("cls");
	using std::cout;
	setCursorPosition(FIELD_WIDTH / 3+8, FIELD_HEIGHT / 2-1);
	cout << "Bye!";
	setCursorPosition(FIELD_WIDTH / 3, FIELD_HEIGHT / 2);
	cout << "It is game <SNAKE> by Denis";
	while (std::cin.get() != '\n')
		continue;
}

void Field::score_table()
{
	std::ifstream fin;
	fin.open(File_name);
	std::string temp;
	int temp_val;
	int i = 0;
	while (i != SIZE_SCORES)
	{
		if (fin >> temp)
			fin >> temp_val;
		else
		{
			temp = "noname";
			temp_val = 0;
		}
		m_scores[i].first = temp;
		m_scores[i++].second = temp_val;
	}
	system("cls");
	std::cout << "\n\t\t\tSCORE" << std::endl;
	for (int i = 0; i <SIZE_SCORES; ++i)
		std::cout << '\t' << m_scores[i].first << std::setw (40- m_scores[i].first.size()) << m_scores[i].second << std::endl;
	fin.close();
	_getch();
	_getch();
}

void Field::set_record(const std::string & name, int score)
{
	std::pair<std::string, int> temp_pair;
	temp_pair.first = name;
	temp_pair.second = score;
	m_scores.push_back(temp_pair);
	rewrite_table();
}

void Field::rewrite_table()
{
	sort(m_scores.begin(), m_scores.end(), [](const std::pair<std::string, int>&a, const std::pair<std::string, int>&b)
	{
		if (a.second == b.second)
			return a.first > b.first;
		return a.second > b.second;
	});
	std::ofstream fout(File_name);
	for (int i = 0; i < SIZE_SCORES; ++i)
		fout << m_scores[i].first << " " << m_scores[i].second << std::endl;
	fout.close();
}

bool Field::beat_record(int record)
{
	bool beat = false;
	for (int i = 0; i < SIZE_SCORES; ++i)
	{
		if (record > m_scores[i].second)
			return true;
	}
	return false;
}

void Field::Help()
{
	using std::cout;
	using std::endl;
	std::setw(30);

	system("cls");	
	cout << "\tControling" << endl;
	wchar_t a = 0x2191;
	std::wcout << a<< std::endl;
	cout << "UP\t\t" << "|" << std::endl;
	cout << "DOWN\t\t" << "|" << std::endl;
	cout << "LEFT\t\t" << "|" << std::endl;
	cout << "RIGHT\t\t" << "|" << std::endl;
	cout << "PAUSE\t\t" << "P" << std::endl;
	cout << "EXIT(in game)\t" << "X" << std::endl;
	_getch();
	_getch();
}
