#pragma once
#include<cstddef>
#include<vector>
using namespace std;
class Segment{
	private:
                enum Direction{up, down, left, right, no};
                Direction direction;
		int xPos;
                int yPos;
		Segment *next;
		bool head;
		char letter;

	public:
		Segment();
		Segment(Direction,int,int);
		char getLetter(int);
		int getHeadXPos();
		int getHeadYPos();
		void changeDirection(char);
		void updatePos(Segment*);
		vector<int> getAllXPos();
		vector<int> getAllYPos();
		int getLastXPos();
		int getLastYPos();
		void addNext();
};
