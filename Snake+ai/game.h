#pragma once
#include <utility>
#include <list>
#include <functional>

enum Direction{UP, DOWN, LEFT,	RIGHT, BODY};

using Coord = std::pair<int,int>;
using RabbitPainter = std::function<void(Coord)>;
using SnakePainter = std::function<void(Coord, Direction)>;



class Snake
{
public:
	std::list<Coord> body;
	bool alive;
	
	Snake();
	Snake(int a, int b);
	
	void move(std::list<Coord> &rabbits);
	Coord next();
	void setdir(Direction a);
    bool find;
	Direction d;
};

class Game
{
public:
	void checkalive();
	std::list<Coord> rabbits;
	std::list<Snake*> snakes;
	Game();
	void rabbit_visitor(RabbitPainter);
	void snake_visitor(SnakePainter);
	void move();
	void add(Snake*);	
};




