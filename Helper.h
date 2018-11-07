#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
const int FIELD_HEIGHT = 28;
const int FIELD_WIDTH =89;
struct Cordinate
{
	int x;
	int y;
};
const int SIZE_SCORES=15;
const char File_name[] = "records.txt";
enum snake_direction { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, STOP, EXIT = 120,PAUSE=112};

