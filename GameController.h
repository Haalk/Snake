#pragma once
#include "Helper.h"
#include "Snake.h"
#include "Field.h"


class GameController
{
public:
	GameController();
	~GameController();
	bool request_play();
	void Menu();
	void Play();
	void hidecursor();
	void Game();
private:
	Snake  *snake;
	Field  *field;
};

