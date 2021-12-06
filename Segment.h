#pragma once
#include<cstddef>

class Segment{
	private:
                enum Direction{up, down, left, right, no};
                Direction direction;
		int xPos;
                int yPos;
		Segment *next;
	public:
		Segment();
		Segment(Direction,int,int);
		void changeDirection(char, bool);
		void updatePos();
		int getXPos();
		int getYPos();
		void addNext();
};
