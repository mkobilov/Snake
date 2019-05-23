#pragma once
#include <utility>
#include <iostream>
#include <termios.h>
#include "keypress.h"
#include "game.h"
#include "control.h"

using namespace std;
using fn_type = std::function<void()>;	

class View
{
	int AI_num;
	void gotoxy(int,int);
	void hline(int,int,int,char c='#');
	void vline(int,int,int,char c='#');
	void size(int);

	static View* instance;
	
	Keypressable* keyd;
    list<Robot*> AId;
public:
	Game* game;
	int winx, winy;

	View();
	~View();
	void draw();
	void run();
	static View* get();
	void cls();
	void setonkey(Keypressable*);
    void setonAI(Robot* R);
    void rabbit_painter(Coord);
	void snake_painter(Coord, Direction);
	void setgame(Game* g);

	
	void settimer(int ms, fn_type fn);

	
	std::pair <int,fn_type> timer;
	
	struct termios oldtc;
	
};
