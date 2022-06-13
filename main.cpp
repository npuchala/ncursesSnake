/*
https://github.com/npuchala
A snake-like game
*/
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

void checkCollision(Segment *snake, int *hits, bool *eaten, char *ch, char currentCollision){
	switch(currentCollision){
		//resets the game once an x or wall is hit 
		case 'x':
			if(snake->getDirection() != no ){
				*hits += 1;
				clear();
				*ch = '\0';
				delete(snake);
				Segment *snake = new Segment(COLS-1,LINES-1);
				*eaten = true;
			}
		break;
		//increases the length of the snake if an apple is eaten
		case 'a':
			snake->addNext();
			*eaten = true;
		break;
	}
}



//The game loop
void game(char *ch, Segment *snake, vector<int> xPos,vector<int> yPos,int rows, int cols){

	const char QUIT = 'q';
	const char APPLE = 'a';
	char currentCollision;
	int rowApple;
	int colApple;
	bool eaten = true;
	bool debug = false;
	int oldLXPos, oldLYPos;
	int hits = 0;
	while(*ch != QUIT){
		if(*ch == 'x'){
			*ch = '\0';
			snake->addNext();
		}
		if(debug){
			mvprintw(0,0,"%c", currentCollision);
			mvprintw(1,0,"%i", hits);
			mvprintw(2,0,"LINES %i", LINES);
			mvprintw(3,0,"COLS %i", COLS);
		}
		if(eaten){
			mvprintw(rand()%rows, rand()% cols,"%c", APPLE);
			eaten = false;
		}
		this_thread::sleep_for(100ms);

		snake->changeDirection(*ch,snake);
		snake->updatePos(snake);
		currentCollision = mvinch(snake->getHeadYPos(), snake->getHeadXPos());
		checkCollision(snake, &hits, &eaten, ch, currentCollision);

		mvprintw(oldLYPos,oldLXPos,"%c", ' ');//Erase old tail
		mvprintw(snake->getLastYPos(),snake->getLastXPos(),"%c", 'x');//Print new tail
		mvprintw(snake->getHeadYPos(), snake->getHeadXPos(),"%c", 'x');//Print new head
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
