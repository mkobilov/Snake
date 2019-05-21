#include "game.h"
#include "control.h"
#include "view.h"
#include <functional>

using namespace std::placeholders;

void Human::onkey(int key)
{
//	printf("\r  %d",key);
	switch (key)
	{
		case 'A':
			snake->setdir(UP);
			break;
		case 'B':
			snake->setdir(DOWN);
			break;
		case 'C':
			snake->setdir(RIGHT);
			break;
		case 'D':
			snake->setdir(LEFT);
			break;
		default:
			break;
	}

}
Human::Human(Snake* s) : snake(s)
{
	//snake =s;
//	auto f = std::bind(&Human::onkeypress,this,_1);
	View* v=View::get();
	v->setonkey(this);
}
Coord Robot::distance(Coord rab)
{
   return Coord(rab.first - snake -> body.front().first, rab.second - snake -> body.front().second);
}
void Robot::onthink()
{    
    auto rab = View::get() -> game -> rabbits;
    Coord low = rab.front();
    for(auto i:rab)
    {
        if((distance(low).first*distance(low).first + distance(low).second*distance(low).second) > (distance(i).first*distance(i).first + distance(i).second * distance(i).second))
        {
            low = i;
        }
    }
    if(distance(low).first*distance(low).first > distance(low).second*distance(low).second)
    {
        if(distance(low).first > 0)
            snake -> setdir(RIGHT);
        else
            snake -> setdir(LEFT);
    }
    else
    {
        if(distance(low).second > 0)
            snake -> setdir(UP);
        else
            snake -> setdir(DOWN);
    }
}
Robot::Robot(Snake* s) : snake(s)
{
    View::get() -> setonAI(this);    
}
