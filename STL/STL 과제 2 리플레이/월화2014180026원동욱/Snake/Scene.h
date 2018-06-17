#pragma once
class Scene
{

public:
	Scene();
	virtual ~Scene();

public:
	virtual void Render();
	virtual void ProcessInput();
	virtual void Animate(float ElapsedTime);
	
};

class MenuScene : public Scene
{
public:
	MenuScene();
	virtual ~MenuScene();

public:
	virtual void Render();
	virtual void ProcessInput();
	virtual void Animate(float ElapsedTime);

private:
	size_t next_state = GFWSTATE::MENU;
public:
	size_t getNextState()const ;

};


class GameScene : public Scene
{
private:
	float ElapsedTime;
	std::string map[MAP_SIZE][MAP_SIZE];
	Snake snake;
	POINT FeedObj;
	bool bRecord = false;
	float InitRecordInterval = 0.3f;
	float RecordInterval = 0.0f;
	std::vector<std::vector<POINT>> snakeRecord;
	std::vector<POINT> FeedRecord;

private:
	void clearMap();
	void createFeedObj();
	void inline Redcord();
	void inline saveRecord();


public:
	bool bActive = true;

public:
	GameScene();
	virtual ~GameScene();
	
	//void BuildObject();

public:
	virtual void Render();
	virtual void ProcessInput();
	virtual void Animate(float ElapsedTime);

	bool collsionHeadObstackle();
	bool collsionHeadFeed();


};


class ReplayScene : public Scene
{
private:
	std::string map[MAP_SIZE][MAP_SIZE];
	float before_stop_speed = 1.0f;
	float replay_speed = 1.0f;
	float InitRecordInterval = 0.3f;
	float RecordInterval = 0.0f;
	size_t time_index = 0 ;
	std::vector<std::vector<POINT>> snakeRecord;
	std::vector<POINT> FeedRecord;
	size_t command;
public:
	ReplayScene();
	virtual ~ReplayScene();

	bool bReturnMenu = false;

public:
	virtual void Render();
	virtual void ProcessInput();
	virtual void Animate(float ElapsedTime);
};


