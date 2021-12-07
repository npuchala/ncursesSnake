#include"Segment.h"

const int rightBoundary = 236;
const int bottomBoundary = 62;

Segment::Segment(){
	//
	letter = 'H';
	head = true;
	direction = no;
	xPos = 50;
	yPos = 50;
	segTurns.empty();
	next = NULL;
}

Segment::Segment(Direction d, int x, int y,queue<DirectionXY> oldQueue){
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
	int oldSize = oldQueue.size();
	segTurns = oldQueue;
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


void Segment::changeDirection(char ch, Segment *seg){

	switch(seg->head){
	case true:
		switch(ch){
			case 'w':
				seg->direction = up;
			break;
			case 'a':
				seg->direction = left;
			break;
			case 's':
				seg->direction = down;
			break;
			case 'd':
				seg->direction = right;
			break;
		}
	break;

	case false://place the head xy and direction into each queue
	DirectionXY *dXY = new DirectionXY();
	dXY->x = xPos;
	dXY->y = yPos;
		switch(ch){
			case 'w':
				dXY->direction = up;
				seg->segTurns.push(*dXY);
			break;
			case 'a':
				dXY->direction = left;
				seg->segTurns.push(*dXY);

			break;
			case 's':
				dXY->direction = down;
				seg->segTurns.push(*dXY);
			break;
			case 'd':
				dXY->direction = right;
				seg->segTurns.push(*dXY);

			break;


		}
		break;
	delete dXY;

	break;
	}
	if(seg->next != NULL)
		changeDirection(ch,seg->next);
}


void Segment::updateDirection(Segment *seg){
	if(seg->segTurns.size() <= 0)
		return;
	DirectionXY nextDirection = seg->segTurns.front();
	if(seg->xPos == nextDirection.x && seg->yPos == nextDirection.y){
		seg->direction = nextDirection.direction;
		seg->segTurns.pop();
	}
}
void Segment::updatePos(Segment *seg){
	switch(seg->direction){
		case up:
			switch(seg->yPos){
				case 0:
				break;
				default:
					seg->yPos--;
				break;
			}
		break;
		case down:
			switch(seg->yPos){
				case bottomBoundary:
				break;
				default:
					seg->yPos++;
				break;
			}
		break;
		case right:
			switch(seg->xPos){
				case rightBoundary:
				break;
				default:
					seg->xPos++;
				break;
			}
		break;
		case left:
			switch(seg->xPos){
				case 0:
				break;
				default:
					seg->xPos--;
				break;
			}
		break;
	}
	if(seg->next != NULL){
		updateDirection(seg->next);
		updatePos(seg->next);

	}

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

/*Get the x position of all segments */
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
}




void Segment::addNext(){
	int nextXPos = getLastXPos();
	int nextYPos = getLastYPos();
	Direction d = direction;
	if(next == NULL){
		next = new Segment(d,xPos,yPos,segTurns);
		return;
	}else{
		Segment *q = next;
		for(; q->next != NULL; q = q->next){
			d = q->direction;
		}
		q->next = new Segment(d,q->xPos,q->yPos,q->segTurns);
	}

}
