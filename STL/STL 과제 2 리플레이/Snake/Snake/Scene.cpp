#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Render()				//화면 초기화 겸용
{
	COORD Pos;
	Pos.X = 0;
	Pos.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	//[출처] 콘솔게임 제작 BAAM(지렁이게임) - 1 | 작성자 박태민
}

void Scene::ProcessInput()
{
}

void Scene::Animate(float ElapsedTime)
{
}

///////////////////////////////////////////////////////////////////////////

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Render()
{
	Scene::Render();
	using namespace std;
	if (next_state == GFWSTATE::REPLAY)
	{
		cout <<  endl;
		cout <<  endl;
	
		cout << "     세이브 파일이 존재하지 않습니다.       " << endl;
		cout << "w를 누르면 메뉴 화면으로 돌아갈 수 있습니다." << endl;
		
	}
	else {
		cout << "-------------------------------------------" << endl;
		cout << endl;
		cout << "                 SNAKE GAME				" << endl;
		cout << "                                           " << endl;
		cout << "                 GameStart  : s			" << endl;
		cout << endl;
		cout << "                 GameReplay : r			" << endl;
		cout << endl;
		cout << "                  E x i t   : e			" << endl;
		cout << endl;
		cout << "-------------------------------------------" << endl;
	}
	
}

void MenuScene::ProcessInput()
{
	if (_kbhit())
	{
		int key = _getch();
		if (key == 'w' || key == 'W') next_state = GFWSTATE::MENU; system("cls");
		if (key == 's' || key == 'S') next_state = GFWSTATE::GAME; system("cls");
		if (key == 'r' || key == 'R') next_state = GFWSTATE::REPLAY; system("cls");
		if (key == 'e' || key == 'E') next_state = GFWSTATE::EXIT;
	}
}

void MenuScene::Animate(float ElapsedTime)
{
}

size_t MenuScene::getNextState() const
{
	return next_state;
}


/////////////////////////////////////////////////////////////////////////////



GameScene::GameScene()
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = "　";
		}
	}

	//좌우 벽 설정
	for (int i = 0; i <MAP_SIZE; i++) {
		map[i][0] = "■";
		map[i][MAP_SIZE - 1] = "■";
	}

	//상하 벽 설정/
	for (int j = 0; j <MAP_SIZE; j++) {
		map[0][j] = "■";
		map[MAP_SIZE - 1][j] = "■";
	}

	snakeRecord.reserve(10000);
	FeedRecord.reserve(10000);
	createFeedObj();

}


GameScene::~GameScene()
{
}

void GameScene::Render()
{
	using namespace std;
	Scene::Render();

	clearMap();

	std::vector<POINT> SnakeBody = snake.GetBody();

	for (const auto & p : SnakeBody) {
		map[p.y][p.x] = "○";
	}

	map[SnakeBody[0].y][SnakeBody[0].x] = "●";

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++)
		{
			cout << map[i][j];
		}

		//if (i == 0) cout << "      현재 경과 시간 : " << ElapsedTime;
		if (i == 2) cout << "      벽이나 자기 자신과 부딪히면 메뉴로 돌아가요 ";
		if (i == 4) cout << "      별을 먹으면 길이가 늘어나요";
		if (i == 6) cout << "      wasd로 조작 가능해요";
		if (i == 8) cout << "      q를 누르면 녹화하고 e를 누르면 녹화를 종료해요";
		if (i == 10) cout << "     1이 뜨면 녹화중입니다 " << bRecord;
			

		cout << endl;
	}
}

void GameScene::ProcessInput()
{

	if (_kbhit())
	{
		int key = _getch();
		if (key == 'w' || key == 'W') snake.SetDirection(Snake::MOVEDIRECTION::UP);
		if (key == 'a' || key == 'A') snake.SetDirection(Snake::MOVEDIRECTION::LEFT);
		if (key == 's' || key == 'S') snake.SetDirection(Snake::MOVEDIRECTION::DOWN);
		if (key == 'd' || key == 'D') snake.SetDirection(Snake::MOVEDIRECTION::RIGHT);
		if (key == 'q' || key == 'Q') bRecord = true;
		if (key == 'e' || key == 'E') saveRecord();
		
	}
}

void GameScene::Animate(float ElapsedTime)
{
	this->ElapsedTime += ElapsedTime;
	RecordInterval -= ElapsedTime;
	snake.Animate(ElapsedTime);
	if (collsionHeadFeed()) {
		snake.AddBody();
		createFeedObj();
	}

	if (collsionHeadObstackle()) {
		if(bRecord) saveRecord();
		bActive = false;
	}

	if (bRecord && RecordInterval < 0) {
		Redcord();
		RecordInterval = InitRecordInterval;
	}
}

bool GameScene::collsionHeadObstackle()
{
	POINT Head = snake.GetBody()[0];
	if (map[Head.y][Head.x] == "■" || map[Head.y][Head.x] == "○")
		return true;
	else
		return false;
}

bool GameScene::collsionHeadFeed()
{
	POINT Head = snake.GetBody()[0];
	if (Head.x == FeedObj.x && Head.y == FeedObj.y)
		return true;
	else
		return false;
}

void GameScene::clearMap()
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = "  ";
		}
	}

	//좌우 벽 설정
	for (int i = 0; i <MAP_SIZE; i++) {
		map[i][0] = "■";
		map[i][MAP_SIZE - 1] = "■";
	}

	//상하 벽 설정/
	for (int j = 0; j <MAP_SIZE; j++) {
		map[0][j] = "■";
		map[MAP_SIZE - 1][j] = "■";
	}

	map[FeedObj.y][FeedObj.x] = "☆";
	
}

void GameScene::createFeedObj()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<> uid(1, MAP_SIZE - 2);

	FeedObj.x = uid(dre);
	FeedObj.y = uid(dre);

}

inline void GameScene::Redcord()
{
	snakeRecord.emplace_back(snake.GetBody());
	FeedRecord.emplace_back(FeedObj);
}

void GameScene::saveRecord()
{
	snakeRecord.shrink_to_fit();
	std::ofstream out("snakeRecordData.txt");
	for (const auto & datas : snakeRecord) {
		out << datas.size()<< std::endl;
		for (const auto & data : datas)
			out << data.x << " " << data.y << " " ;
		out << std::endl;
	}
	out.close();

	FeedRecord.shrink_to_fit();
	out.open("FeedRecordData.txt");
	for (const auto & data: FeedRecord) {
		out << data.x << " " << data.y << std::endl;
	}
	out.close();

	bRecord = false;
}

ReplayScene::ReplayScene()
{
	std::ifstream in("snakeRecordData.txt");
	size_t num;
	std::vector<POINT> vecPoint;
	POINT tempPoint;
	
	while (in >> num) {
		vecPoint.clear();
		vecPoint.reserve(num);
		for (size_t i = 0 ; i<num; i++)
		{
			in >> tempPoint.x;
			in >> tempPoint.y;
			vecPoint.emplace_back(tempPoint);
		}
		snakeRecord.emplace_back(vecPoint);
	}
	in.close();

	in.open("FeedRecordData.txt");

	while (in >> tempPoint.x) {
		in >> tempPoint.y;
		FeedRecord.emplace_back(tempPoint);
	}
	in.close();


	
}

ReplayScene::~ReplayScene()
{
	

}

void ReplayScene::Render()
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = "  ";
		}
	}

	//좌우 벽 설정
	for (int i = 0; i <MAP_SIZE; i++) {
		map[i][0] = "■";
		map[i][MAP_SIZE - 1] = "■";
	}

	//상하 벽 설정/
	for (int j = 0; j <MAP_SIZE; j++) {
		map[0][j] = "■";
		map[MAP_SIZE - 1][j] = "■";
	}

	map[FeedRecord[time_index].y][FeedRecord[time_index].x] = "☆";

	for (const auto & data : snakeRecord[time_index])
	{
		map[data.y][data.x] = "○";
	}

	map[snakeRecord[time_index][0].y][snakeRecord[time_index][0].x] = "●";

	Scene::Render();
	using namespace std;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++)
		{
			cout << map[i][j];
		}
		//if (i == 0) cout << "      현재 경과 시간 : " << ElapsedTime;
		if (i == 2) cout << "      w 메뉴로 돌아가기 ";
		if (i == 4) cout << "      ad 속도 조절하기";
		if (i == 6) cout << "      s 정지하기, 정지 해제하기";
		//if (i == 8) cout << "      q를 누르면 녹화하고 e를 누르면 녹화를 종료해요";
		if (i == 10) {

			if (time_index < FeedRecord.size() - 1)
				cout << "       영상을 재생 중 입니다.";
			else cout << "      영상 재생이 종료 되었습니다.";

		}

		cout << endl;
	}

}

void ReplayScene::ProcessInput()
{

	if (_kbhit())
	{
		int key = _getch();
		if (key == 'w' || key == 'W') bReturnMenu = true;
		if (key == 'a' || key == 'A') 
			if(replay_speed > 0.0f) replay_speed -= 0.4f;
		if (key == 's' || key == 'S') {
			if (replay_speed) {
				before_stop_speed = replay_speed;
				replay_speed = 0.0f;
			}
			else
				replay_speed = before_stop_speed;
		}
		if (key == 'd' || key == 'D') {
			if (replay_speed < 2.0f)
			replay_speed += 0.4f;
		}

	}
}

void ReplayScene::Animate(float ElapsedTime)
{
	if(time_index < FeedRecord.size() -1)
		RecordInterval -= ElapsedTime * replay_speed;

	if (RecordInterval < 0) {
		time_index++;
		RecordInterval = InitRecordInterval;
	}

}
