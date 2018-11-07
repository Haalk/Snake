#pragma once
#include "Helper.h"
#include <utility>
class Field
{
public:
	Field();
	~Field();
	void setCursorPosition(int, int);
	void drawfield();
	void Hello();
	void Bye();
	void score_table();
	void set_record(const std::string &, int);
	bool beat_record(int record);
	void Help();
private:
	std::vector<std::pair<std::string, int>> m_scores;
	void rewrite_table();
};

