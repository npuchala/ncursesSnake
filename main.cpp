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


void game(char *ch, Segment *snake, vector<int> xPos,vector<int> yPos,int rows, int cols){
char currentCollision;
bool debug = false;
int rowApple;
int colApple;
bool eaten = true;
int oldLXPos, oldLYPos = 50;
int hits = 0;

	while(*ch != 'q'){
		if(*ch == 'x'){
			*ch = '\0';
			snake->addNext();
		}
		if(eaten){
			mvprintw(rand()%rows, rand()% cols,"%c", 'a');
			eaten = false;
		}


		this_thread::sleep_for(100ms);

		snake->changeDirection(*ch,snake);
		snake->updatePos(snake);

		currentCollision = mvinch(snake->getHeadYPos(), snake->getHeadXPos());
		if(debug){
			mvprintw(0,0,"%c", currentCollision);
			mvprintw(1,0,"%i", hits);
			mvprintw(2,0,"LINES %i", LINES);
			mvprintw(3,0,"COLS %i", COLS);
		}

		//Pauses the loop once an x is hit 
		if(currentCollision == 'x' && oldLXPos != snake->getLastYPos() && (*ch == 'a' || *ch == 's' || *ch == 'd' || *ch == 'w') )
		{
			hits++;
			clear();
			*ch = '\0';
			delete(snake);
			Segment *snake = new Segment(COLS-1,LINES-1);
			eaten = true;

		}

		if(currentCollision == 'a'){
			snake->addNext();
			eaten = true;
		}

		mvprintw(oldLYPos,oldLXPos,"%c", ' ');
		mvprintw(snake->getLastYPos(),snake->getLastXPos(),"%c", 'x');
		mvprintw(snake->getHeadYPos(), snake->getHeadXPos(),"%c", 'x');
		oldLYPos = snake->getLastYPos();
		oldLXPos = snake->getLastXPos();


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
