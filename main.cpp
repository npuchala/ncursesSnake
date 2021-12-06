#include<ncurses.h>
#include"Segment.h"
#include<string>
#include<thread>
#include<vector>
#include<chrono>
using namespace std;


void chooseChar(char *ch){//& sends a reference to the function
	*ch = getch();

}




Segment n;//don't keep this here
void game(char *ch){
	//mvprintw(0,0,"\n");
	n.changeDirection(*ch,true);
	n.updatePos();

	this_thread::sleep_for(50ms);
	clear();
	

	mvprintw(n.getYPos(),n.getXPos(),"X");


	//mvprintw(0,0,"Character pressed %i", n.getDirection());
	refresh();




}
void loop(void (*func)(char *ch), char *ch){
	while(*ch != 'q'){
		func(ch);
	}
}

int main()
{
	char ch;
	initscr();			/* Start curses mode 		  */
	cbreak();
	vector<thread> threads;		/*use a vector to hold the threads while*/
	noecho();
	keypad(stdscr,true);
	
	threads.push_back(thread(loop,&game,&ch));
	threads.push_back(thread(loop,&chooseChar,&ch));




	for (auto& t : threads){ 	/*a loop that goes through the vector not carrying about the type*/
		t.join();		/*Joining the threads*/
	}

	endwin();			/* End curses mode		  */

	return 0;
}
