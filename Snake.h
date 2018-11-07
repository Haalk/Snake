#pragma once
#include "Helper.h"
#include <vector>

class Snake
{
public:
	Snake();
	~Snake();
	bool move();
	void setCursorPosition(int, int) const;
	int return_score() const;
	std::string get_nameSnake() const;
	void fruit_score();
	void set_nameSnake();
	void reset_snake();
	void show_snake() const;
	void swap_tails();
private:
	Cordinate snake_head;
	int fruitX, fruitY;
	int score;
	std::vector<Cordinate> snake_tail;
	int nTail;
	snake_direction m_dir;
	bool good;
	std::string snake_name;
	int colour_fruit;
	std::vector<int> tails_colour;
};

