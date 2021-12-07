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
vector<int> xPos;
vector<int> yPos;

void game(char *ch){
	//mvprintw(0,0,"\n");
	if(*ch == 'x'){
		*ch = '1';
		n.addNext();
	}
	n.changeDirection(*ch,&n);
	n.updatePos(&n);
	this_thread::sleep_for(100ms);
	clear();
	xPos.clear();
	yPos.clear();
	xPos = n.getAllYPos();
	yPos = n.getAllXPos();
	for(int i = 0; i < xPos.size(); i++){
		mvprintw(0,0,"xPos.size()%i",xPos.size());//don't forget the \n
		mvprintw(1,0,"Head xPos: %i yPos: %i",n.getHeadXPos(), n.getHeadYPos());
		mvprintw(2,0,"Tail xPos: %i yPos: %i",n.getLastXPos(), n.getLastYPos());
		
		//mvprintw(1,0,"Head xPos: %i",n.getHeadXPos());
		//mvprintw(2,0,"Head yPos: %i",n.getHeadYPos());
		mvprintw(xPos[i],yPos[i],"%c", n.getLetter(i));
	}

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


	//xPos = n.getXPos();
	//yPos = n.getYPos();
	threads.push_back(thread(loop,&game,&ch));
	threads.push_back(thread(loop,&chooseChar,&ch));




	for (auto& t : threads){ 	/*a loop that goes through the vector not carrying about the type*/
		t.join();		/*Joining the threads*/
	}

	endwin();			/* End curses mode		  */

	return 0;
}
