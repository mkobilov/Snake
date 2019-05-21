#include <stdio.h>

#include "control.h"
#include "view.h"
#include "game.h"
#include <cstdlib>

int main()
{
	View* v=View::get();
	Snake* s = new Snake(5,5);
	Human h(s);
	Game g;
	srand(time(NULL));
	Snake* s1 = new Snake(10,10);
	Robot r(s1);
	Snake* s2 = new Snake(15,15);
	Robot r2(s2);
	
		
	g.add(s);
	g.add(s1);
	g.add(s2);
	v->setgame(&g);

	v->draw();
	v->run();
	
	delete v;
	return 0;
}
