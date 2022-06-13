#pragma once
#include<cstddef>
#include"utility.h"
#include<vector>
#include<queue>
using namespace std;

struct DirectionXY{
	public:
		int x;
		int y;
		Direction direction;
};


class Segment{
	private:
		Direction direction;
		int xPos;
	        int yPos;
		int bottomBoundary;
		int rightBoundary;
		Segment *next;
		bool head;
		char letter;
		queue<DirectionXY> segTurns;
	public:
		Segment(int,int);
		Segment(Direction,int,int,queue<DirectionXY>);
		void deleteLastSegment(Segment*);
		char getLetter(int);
		int getHeadXPos();
		int getHeadYPos();
		void changeDirection(char,Segment*);
		void updateDirection(Segment*);
		void updatePos(Segment*);
		vector<int> getAllXPos();
		vector<int> getAllYPos();
		int getLastXPos();
		int getLastYPos();
		void addNext();
		Direction getDirection();
};
