#include"Segment.h"

const int rightBoundary = 236;
const int bottomBoundary = 62;

Segment::Segment(){
	letter = 'H';
	head = true;
	direction = no;
	xPos = 50;
	yPos = 50;
	next = NULL;
}

Segment::Segment(Direction d, int x, int y){
	letter = 'O';
	head = false;
	direction = d;
	switch(d){
		case up:
			y++;
		break;
		case down:
			y--;
		break;
		case left:
			x++;
		break;
		case right:
			x--;
		break;
	}
	xPos = x;
	yPos = y;
	next = NULL;
}

char Segment::getLetter(int segmentPlace){
	Segment *q = this;
	if(q->next == NULL){
		return q->letter;
	}else{
		for(int i = 0; i < segmentPlace; i++)
		{
			q = q->next;
		}
		return q->letter;
	}

}
int Segment::getHeadXPos(){
	return xPos;
}
int Segment::getHeadYPos(){
	return yPos;
}


void Segment::changeDirection(char ch){

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
	case false:
	break;
	}
}
void Segment::updatePos(Segment *seg){

	switch(direction){
		case up:
			switch(yPos){
				case 0:
				break;
				default:
					seg->yPos--;
				break;
			}
		break;

		case down:
			switch(yPos){
				case bottomBoundary:
				break;
				default:
					seg->yPos++;
				break;
			}
		break;



		case right:
			switch(xPos){
				case rightBoundary:
				break;
				default:
					seg->xPos++;
				break;
			}
		break;



		case left:
			switch(xPos){
				case 0:
				break;
				default:
					seg->xPos--;
				break;
			}
		break;
	}
	if(seg->next != NULL)
		updatePos(seg->next);


}
/*Get the x position of all segments */
vector<int> Segment::getAllXPos(){
	vector<int> allXPos;
	allXPos.push_back(xPos);
	for(Segment *q =next; q != NULL; q = q->next){
		allXPos.push_back(q->xPos);
	}
	return allXPos;
}

vector<int> Segment::getAllYPos(){
	vector<int> allYPos;
	allYPos.push_back(yPos);
	for(Segment *q =next; q != NULL; q = q->next){
		allYPos.push_back(q->yPos);
	}
	return allYPos;


}
int Segment::getLastXPos(){

	int lastX;
	if(next == NULL){
		return xPos;
	}else{
		for(Segment *q= next; q->next != NULL; q = q->next){
			lastX = q->xPos;
		}
		return lastX;
	}
	return -1;
}
int Segment::getLastYPos(){
	int lastY;
	if(next == NULL){
		return yPos;
	}else{
		for(Segment *q= next; q->next != NULL; q = q->next){
			lastY = q->yPos;
		}
		return lastY;
	}
		return -1;
}




void Segment::addNext(){
	int nextXPos = getLastXPos();
	int nextYPos = getLastYPos();
	Direction d = direction;
	if(next == NULL){
		next = new Segment(d,nextXPos,nextYPos);
		return;
	}else{
		Segment *q = next;
		for(; q->next != NULL; q = q->next){
			d = q->direction;
		}
		q->next = new Segment(d,nextXPos,nextYPos);
	}

}
