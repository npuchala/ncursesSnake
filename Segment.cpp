#include"Segment.h"
	const int rightBoundary = 100;
	const int bottomBoundary = 100;

Segment::Segment(){
	direction = no;
	xPos = 50;
	yPos = 50;
	next = NULL;
}
Segment::Segment(Direction d, int x, int y){
	direction = d;
	xPos = x;
	yPos = y;
	next = NULL;
}

void Segment::changeDirection(char ch, bool head){

	switch(head){
	case true:
		switch(ch){
			case 'w':
				direction = up;
			break;
			case 'a':
				direction = left;
			break;
			case 's':
				direction = down;
			break;
			case 'd':
				direction = right;
			break;
		}
	break;
	}
}
void Segment::updatePos(){
	switch(direction){
		case up:
			switch(yPos){
				case 0:
				break;
				default:
					yPos--;
				break;
			}
		break;

		case down:
			switch(yPos){
				case bottomBoundary:
				break;
				default:
					yPos++;
				break;
			}
		break;



		
		case right:
			switch(xPos){
				case rightBoundary:
				break;
				default:
					xPos++;
				break;
			}
		break;
		


		case left:
			switch(xPos){
				case 0:
				break;
				default:
					xPos--;
				break;
			}
		break;
	}


}

int Segment::getXPos(){
	return xPos;
}
int Segment::getYPos(){
	return yPos;
}

void Segment::addNext(){
	Direction d = direction;
	if(next == NULL){
		next = new Segment(d,1,1);//Change
		return;
	}else{
		Segment *q = next;
		for(; q != NULL; q = q->next){
			d = q->direction;
		}
		q = new Segment(d,1,1);//change
	}

}
