#include<ncurses.h>
#include"Segment.h"
#include<string>
#include<thread>
#include<vector>
#include<chrono>
#include<cstdlib>

using namespace std;

/*A function the gets the key inputs*/
void chooseChar(char *ch){//& sends a reference to the function
	while(*ch != 'q'){
		*ch = getch();
	}
}


void game(char *ch, Segment *n, vector<int> xPos,vector<int> yPos,int rows, int cols){
char a;

int rowApple;
int colApple;
bool eaten = true;
int oldLXPos, oldLYPos = 50;
int hits = 0;

	while(*ch != 'q'){
		if(*ch == 'x'){
			*ch = '\0';
			n->addNext();
		}
		if(eaten){
			mvprintw(rand()%rows, rand()% cols,"%c", 'a');
			eaten = false;
		}


		this_thread::sleep_for(100ms);

		n->changeDirection(*ch,n);
		n->updatePos(n);


		//Option 1 for drawing the snake;
		/*clear();
		xPos.clear();
		yPos.clear();
		yPos = n.getAllYPos();
		xPos = n.getAllXPos();

		for(int i = 0; i < xPos.size(); i++){
			mvprintw(0,0,"xPos.size()%i",xPos.size());
			mvprintw(1,0,"Head xPos: %i yPos: %i",n.getHeadXPos(), n.getHeadYPos());
			mvprintw(2,0,"Tail xPos: %i yPos: %i",n.getLastXPos(), n.getLastYPos());
			mvprintw(yPos[i],xPos[i],"%c", n.getLetter(i));
		}*/
		//Option 1 for drawing the snake

		a = mvinch(n->getHeadYPos(), n->getHeadXPos());
		mvprintw(0,0,"%c", a);
		mvprintw(1,0,"%i", hits);
		mvprintw(2,0,"LINES %i", LINES);
		mvprintw(3,0,"COLS %i", COLS);



		//Pauses the loop once an x is hit 
		if(a == 'x' && oldLXPos != n->getLastYPos() && (*ch == 'a' || *ch == 's' || *ch == 'd' || *ch == 'w') )//put this in segment
		{
			hits++;

			clear();
			*ch = '\0';
			delete(n);
			Segment *n = new Segment(COLS-1,LINES-1);
			eaten = true;

		}

		if(a == 'a'){
			n->addNext();
			eaten = true;
		}
		 //Not exactly this but you know what 



		mvprintw(oldLYPos,oldLXPos,"%c", ' ');
		mvprintw(n->getLastYPos(),n->getLastXPos(),"%c", 'x');
		mvprintw(n->getHeadYPos(), n->getHeadXPos(),"%c", 'x');
		oldLYPos = n->getLastYPos();
		oldLXPos = n->getLastXPos();


		refresh();
	}
}


int main()
{
	char *ch;
	initscr();			/* Start curses mode 		  */
	cbreak();
	vector<thread> threads;		/*use a vector to hold the threads while*/
	noecho();
	keypad(stdscr,true);

	Segment *n = new Segment(COLS-1,LINES-1);
	vector<int> xPos;
	vector<int> yPos;

	threads.push_back(thread(game,ch,n,xPos,yPos,LINES,COLS));
	threads.push_back(thread(chooseChar,ch));



	for (auto& t : threads){ 	/*a loop that goes through the vector not carrying about the type*/
		t.join();		/*Joining the threads*/
	}

	endwin();			/* End curses mode		  */

	return 0;
}
