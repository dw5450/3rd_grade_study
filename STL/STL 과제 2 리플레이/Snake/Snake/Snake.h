#pragma once
class Snake
{
public:
	enum MOVEDIRECTION {
		LEFT = 0,
		RIGHT = 1,
		UP = 2,
		DOWN = 3

	};

private:
	std::vector<POINT>body;
	float init_move_cooltime =  0.3f;
	float move_cooltime = 0.3f;
	bool bMove = false;
	size_t MoveDirection = RIGHT;

public:
	Snake();
	~Snake();

public:
	const std::vector<POINT> & GetBody() const { return body; };
	void Animate(float ElapsedTime);
	void Render();

	void SetDirection(size_t inputDirection);
	void AddBody();

private:
	void Move();

};

