// Snake.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Snake.h"


Snake::Snake()
{
	POINT p;
	p.x = MAP_SIZE / 2;
	p.y = MAP_SIZE / 2;
	body.emplace_back(p);
}


Snake::~Snake()
{

}

void Snake::Animate(float ElapsedTime)
{
	move_cooltime -= ElapsedTime;

	if (move_cooltime < 0) {
		Move();
		move_cooltime = init_move_cooltime;
	}
}

void Snake::Render()
{
}

void Snake::SetDirection(size_t inputDirection)
{
	POINT tempPoint = body[0];

	if (inputDirection == LEFT) {
		tempPoint.x -= 1;
		if (tempPoint.x != body[1].x)
			MoveDirection = LEFT;
	}

	if (inputDirection == RIGHT) {
		tempPoint.x += 1;
		if (tempPoint.x != body[1].x )
			MoveDirection = RIGHT;
	}

	if (inputDirection == UP) {
		tempPoint.y -= 1;
		if (tempPoint.y != body[1].y)
			MoveDirection = UP;
	}

	if (inputDirection == DOWN) {
		tempPoint.y += 1;
		if (tempPoint.y != body[1].y)
			MoveDirection = DOWN;
	}
}

void Snake::AddBody()
{
	POINT tempPoint;
	size_t BodyEndDirection;

	if (body.size() == 1) {
		BodyEndDirection = MoveDirection;
	}
	else {
		POINT end = body[body.size() - 1];
		POINT before_end = body[body.size() - 2];

		if (before_end.x - end.x < 0) BodyEndDirection = LEFT;
		if (before_end.x - end.x > 0) BodyEndDirection = RIGHT;
		if (before_end.y - end.y < 0) BodyEndDirection = UP;
		if (before_end.y - end.y > 0) BodyEndDirection = DOWN;
	}

	size_t end_index = body.size() - 1;
	if (BodyEndDirection == LEFT) {
		tempPoint.x = body[end_index].x + 1;
		tempPoint.y = body[end_index].y;
	}
	if (BodyEndDirection == RIGHT) {
		tempPoint.x = body[end_index].x - 1;
		tempPoint.y = body[end_index].y;
	}
	if (BodyEndDirection == UP) {
		tempPoint.x = body[end_index].x;
		tempPoint.y = body[end_index].y + 1;
	}
	if (BodyEndDirection == DOWN) {
		tempPoint.x = body[end_index].x;
		tempPoint.y = body[end_index].y - 1;
	}
	
	body.emplace_back(tempPoint);
}

void Snake::Move()
{
	std::vector<POINT>::iterator itor = --body.end();
	for (itor; itor > begin(body); --itor) {
		*itor = *(itor - 1);
	}

	if (MoveDirection == LEFT) {
		body[0].x -= 1;
	}
	if (MoveDirection == RIGHT) {
		body[0].x += 1;
	}
	if (MoveDirection == UP) {
		body[0].y -= 1;
	}
	if (MoveDirection == DOWN) {
		body[0].y += 1;
	}
}


