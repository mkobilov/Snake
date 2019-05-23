#include "game.h"
#include "view.h"

#include <cstdlib>
#include <random>

using namespace std;

Game::Game()
{
	rabbits.push_back(Coord(10,15));
	rabbits.push_back(Coord(15,10));
	
	View* v = View::get();
	v->View::settimer(250, std::bind(&Game::move, this));
}
void Game::add(Snake* s)
{
	snakes.push_back(s);
}
Snake::Snake()
{
	View* v=View::get();
	//random_device rd; // obtain a random number from hardware
    //mt19937 eng(rd()); // seed the generator
    //uniform_int_distribution<> distr(5, v->winx-1); // define the range
	//printf("hui %d\n",distr(eng));
	srand(time(NULL));
	int first = rand()%(v->winx-2) + 5;
	printf("hui1\n");
    
    int second = rand()%(v->winy-2) + 5;
	body.push_back(Coord(first,second));
	body.push_back(Coord(first + 1,second));
	d = LEFT;
	alive = true;
}
Snake::Snake(int a, int b)
{
	View* v=View::get();
	
	int first = a;
	printf("hui1\n");
    
    int second = b;
	body.push_back(Coord(first,second));
	body.push_back(Coord(first + 1,second));
	d = LEFT;
	alive = true;
}
void Game::rabbit_visitor(RabbitPainter p)
{
	for(auto r : rabbits)
		p(r);
		
}
void Game::snake_visitor(SnakePainter p)
{
	bool head=false;
	for(auto s : snakes) {
		Direction d = s->d;
		for(auto b : s->body)
		{
				p(b,d);
				d = BODY;
		}
	}
	
}
void Game::checkalive()
{
	
	auto headlist = new list<Coord>();
	int i = 0;
	
	for(auto s : snakes)
	{
		i = 0;
		
		Coord h = s->body.front();
		if(h.first == 1 || h.second == 1 || h.second == View::get()->winx-2 || h.second == View::get()->winy - 2)
		{
			s->alive = false;
			continue;
		}
		for(auto s2 : snakes)
		{
			for(auto c : s2->body)
			{
				if(h.first == c.first && h.second == c.second)
				{
					
					i++;
				}
			}
			printf("\e[H\e[J");
			printf("i = %d\n",i);
		}
		if(i > 1)
			s->alive = false;
			
	}
	
}
void Game::move()
{
	View* v = View::get();

	if(rand()%10 == 1)
	{
		Coord c;
		c.first = rand()%(v->winx-2) + 2;
		c.second = rand()%(v->winy-2) + 2;
		rabbits.push_back(c);
		v->rabbit_painter(c);	
	}
	checkalive();
	for(auto s : snakes)
	{
		if(s->alive == false)
		{
			continue;
		}
		s->move(rabbits);
		
	}
}
void Snake::setdir(Direction a)
{
	d = a;
}
void Snake::move(std::list<Coord> &rabbits)
{
	Coord c = next();
	body.push_front(c);

	for(auto i = rabbits.begin(); i != rabbits.end(); i++)
	{
		if(c == *i)
		{
            find = false;
			rabbits.erase(i);
			return;
		}
	}

	body.pop_back();
	
}
Coord Snake::next()
{
	Coord a = body.front();
	switch (d)
	{
		case UP:
			a.second++;
			break;
		case DOWN:
			a.second--;
			break;
		case LEFT:
			a.first--;
			break;
		case RIGHT:
			a.first++;
			break;
		default:
			break;
	}
	return a;
}
