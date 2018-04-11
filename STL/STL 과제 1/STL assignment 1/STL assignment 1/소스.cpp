#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <algorithm>

#define INITPAYERNUM 100000
#define SCHOLLMAXSCORE 37000000
#define ESCAPEMAXSCORE 41000000
#define PLAYPlAYERSNUM 10000

using namespace std;

//플레이어의 정보를 가지고 있는 클레스
class Player
{
private:
	int id = 0;					//아이디	
	int school_score = 0;		//쿠키 훈련소 점수
	int escape_score = 0;		//떼탈출 점수
	int school_rank = 0;		//쿠키 훈련소 랭크
	int escape_rank = 0;		//떼탈출 랭크
	bool played = false;		//플레이 실행 여부					//플레이에서 구분하기 위해서				//추후 알고리즘에 따라 삭제 가능

public:
	//플레이어의 정보를 초기화 하는 함수
	Player() {};
	Player(int id, int school_score, int escape_score) :												//생성자
		id(id), school_score(school_score), escape_score(escape_score) {}
	void setInfo(int id, int school_score, int escape_score) {											//자신의 정보 수정, 생성자와 동일한 인자로.
		this->id = id;	
		this->school_score = school_score;
		this->escape_score = escape_score;	
	}	

	//소멸자
	~Player() {}

	//플레이어의 정보를 가져오는 get , const 함수들
	int getId()const { return id; }
	int getSchoolScore()const { return school_score; }
	int getEscapeScore()const { return escape_score; }
	int getSchoolRank()const { return school_rank; }
	int getEscapeRank()const { return escape_rank; }
	bool getPlayed()const { return played; }

	//플레이어의 정보를 수정하는 set 함수들
	void setSchoolScore(int school_score) { this->school_score = school_score; }
	void setEscapeScore(int escape_score) { this->escape_score = escape_score; }
	void setSchoolRank(int school_rank) { this->school_rank = school_rank; }
	void setEscapeRank(int escape_rank) { this->escape_rank = escape_rank; }
	void setPlayed(bool played) { this->played = played; }

	//플레이어의 정보를 출력 하는 함수
	void showInfo()const {
		cout << "ID : " << id << endl;
		cout << "쿠키 훈련소 랭크 : " << school_rank << "      쿠키 훈련소 점수 : " << school_score << endl;
		cout << "떼탈출 랭크	 : " << escape_rank << "      떼탈출 점수      : " << escape_score << endl;
		cout << "----------------------------------------------------------------------------------------" << endl;
	}
};


//게임을 조작하는 클레스
class Handler
{
private:
	int player_num = 0;									//현제 플레이어의 수
	shared_ptr<Player> player;							//플레이어를 가르키는 포인터
	vector<shared_ptr<Player>> players_vec;				//처음 만들어진 순서 정렬된 플레이어들의 포인터 벡터
	vector<shared_ptr<Player>> players_sorted_school;	//쿠키 훈련소 점수로 정렬된 플레이어들의 포인터 벡터
	vector<shared_ptr<Player>> players_sorted_escape;	//떼 탈출점수로 정렬된 플레이어들의 포인터 벡터

public:

	//Handler를 초기화 하는 함수
	Handler()																											//생성자
	{	//플레이어 백터 메모리 설정
		players_vec.reserve(INITPAYERNUM);
		players_sorted_school.reserve(INITPAYERNUM);
		players_sorted_escape.reserve(INITPAYERNUM);

		ifstream in("과제1.dat", ios::binary); //binary와 txt차이는?

		//파일이 존재할 경우 값을 읽어서 프로그램 실행, 없을시 플레이어들을 만들고 실행
		if (in) {
			//포인터로 바로 받을수 없이니 일단 값을 복사해두고 그것에 포인터를 가르키게함
			vector<Player> v(INITPAYERNUM);
			in.read((char*)v.data(), sizeof(Player) * INITPAYERNUM);
	
			for (int i = 0; i< v.size(); ++i)
				players_vec.push_back(make_shared<Player>(v[i]));

			player_num = INITPAYERNUM;
		}
		else 
		{

			//랜덤을 쓰기 위한 값 설정			//추후에 분포에 대해 더 공부하고 수정해야함
			random_device rd;					// dre.seed 대신 저걸로 초기화해주자.
			default_random_engine dre(rd());
			auto school_distribution = getSchoolDistribution();
			auto escape_distribution = getEscapeDistribution();

			int school_score = 0;
			int escape_score = 0;
			for (player_num; player_num < INITPAYERNUM; ++player_num) {
				school_score = static_cast<int>(round(school_distribution(dre)));
				escape_score = static_cast<int>(round(escape_distribution(dre)));
				players_vec.emplace_back(new Player(player_num + 1, school_score, escape_score));
			}
		}
		//쿠키 훈련소 정렬 벡터에 값 초기화, 정렬 후 랭크를 설정
		players_sorted_school = players_vec;
		setSchoolRank();

		////떼탈출 정렬 벡터에 값 초기화, 정렬 후 랭크를 설정
		players_sorted_escape = players_vec;
		setEscapeRank();

		//플레이어 설정				//디폴트 값으로 첫 플레이어가 플레이어로 설정댐, 추후 설정 변경 가능하도록
		player = players_vec[0];
	
	}

	//프로그램 작동을 위한 함수

	void activate() {
		while (1)
		{
			cout << "-------------------------------------------MENU----------------------------------------------------" << endl;
			cout << "출력 :q -> id 순	w -> 훈련소 랭크순	e -> 때탈출 랭크순	r -> 플레이어 정보 출력" << endl;
			cout << "실행 :a -> 게임 플레이!		s -> 게임 종료" << endl;
			cout << "--------------------------------------------------------------------------------------------------" << endl;
			char key;
			cout << "입력 : "; cin >> key;
			system("cls");

			if (key == 'q' || key == 'Q')
			{
				//id순으로 된 플레이어 출력
				showPlayersInfo(players_vec);
			}

			if (key == 'w' || key == 'W')
			{
				//훈련소 랭크순으로 정렬 된 플레이어 출력
				showPlayersInfo(players_sorted_school);
			}

			if (key == 'e' || key == 'E')
			{
				//때탈출 랭크순으로 정렬 된 플레이어 출력
				showPlayersInfo(players_sorted_escape);
				
			}
			else if (key == 'r' || key == 'R')
			{
				cout << "플레이어 정보 출력 " << endl;
				player->showInfo();
			}

			else if (key == 's' || key == 'S')
			{
				cout << "프로그램을 종료합니다." << endl;
				break;
			}
			else if (key == 'a' || key == 'A')
			{
				cout << endl;
				playCookieRun();
				cout << endl;
			}
		}
	}

	
	//핸들러의 정보를 가져오는 함수
	normal_distribution<> getSchoolDistribution() const {
		return  normal_distribution<>(SCHOLLMAXSCORE / 2, static_cast<int>(SCHOLLMAXSCORE / 20));
	}

	normal_distribution<> getEscapeDistribution() const {
		return  normal_distribution<>(ESCAPEMAXSCORE / 2, static_cast<int>(ESCAPEMAXSCORE / 20));
	}


	//핸들러의 정보를 수정 하는 함수
	void setSchoolRank() {
		sort(players_sorted_school.begin(), players_sorted_school.end(),
			[](const shared_ptr<Player> & p1, const shared_ptr<Player> & p2) {
			return p1->getSchoolScore() > p2->getSchoolScore();
		});
		for (unsigned int i = 0; i < players_sorted_school.size(); i++)
			players_sorted_school[i]->setSchoolRank(i + 1);
	}

	void setEscapeRank() {
		sort(players_sorted_escape.begin(), players_sorted_escape.end(),
			[](const shared_ptr<Player> & p1, const shared_ptr<Player> & p2)
		{return p1->getEscapeScore() > p2->getEscapeScore();});

		for (unsigned int i = 0; i < players_sorted_escape.size(); i++)
			players_sorted_escape[i]->setEscapeRank(i + 1);
	}
	
	void playCookieRun()
	{
		
		//플레이 이전의 플레이어의 랭킹 설정
		int prev_school_rank = player->getSchoolRank();
		int prev_escape_rank = player->getEscapeRank();

		//쿠키 훈련소 실행!
		playSchool();
		//떼탈출 실행!
		playEscape();

		//////////////////////////////////////////////////////플레이한 이후 변경된 플레이어의 정보 출력//////////////////////////////////////////////
		int school_rank = player->getSchoolRank();
		cout << "--------------------------------------------------쿠키 훈련소--------------------------------------------" << endl;
		cout << "플레이어의 ID  : " << player->getId() << "	점수 : " << player->getSchoolScore() << "	  순위 : " << school_rank << "	  상위 " << double(school_rank) / double(player_num) * 100 << "%" << "	  등수 변동 : " <<  prev_school_rank - school_rank << endl;

		if (1 < school_rank && school_rank < player_num) {
			shared_ptr<Player> prevPlayer = players_sorted_school[school_rank - 2];
			shared_ptr<Player> nextPlayer = players_sorted_school[school_rank];
			cout << "이전 등수 ID  : " << prevPlayer->getId() << "	점수 : " << prevPlayer->getSchoolScore() << "	  순위 : " << prevPlayer->getSchoolRank() << endl;
			cout << "이후 등수 ID  : " << nextPlayer->getId() << "	점수 : " << nextPlayer->getSchoolScore() << "	  순위 : " << nextPlayer->getSchoolRank() << endl;
		}
		else if (school_rank ==  1) {
			shared_ptr<Player> nextPlayer = players_sorted_school[school_rank];
			cout << "이후 등수 ID  : " << nextPlayer->getId() << "	점수 : " << nextPlayer->getSchoolScore() << "	  순위 : " << nextPlayer->getSchoolRank() << endl;
			cout << "당신보다 빠른 쿠키는 없습니다." << endl;
		}
		else if (school_rank == player_num) {
			shared_ptr<Player> prevPlayer = players_sorted_school[school_rank - 2];
			cout << "이전 등수 ID  : " << prevPlayer->getId() << "	점수 : " << prevPlayer->getSchoolScore() << "	  순위 : " << prevPlayer->getSchoolRank() << endl;
			cout << "당신보다 느린 쿠키는 없습니다. " << endl;
		}



		int escape_rank = player->getEscapeRank();
		cout << "----------------------------------------------------떼 탈 출---------------------------------------------" << endl;
		cout << "플레이어의 ID  : " << player->getId() << "	점수 : " << player->getEscapeScore() << "	  순위 : " << escape_rank << "	  상위 " << double(escape_rank) / double(player_num) * 100 << "%" << "	  등수 변동 : " << prev_escape_rank - escape_rank << endl;

		if (1 < escape_rank && escape_rank < player_num) {
			shared_ptr<Player> prevPlayer = players_sorted_escape[escape_rank - 2];
			shared_ptr<Player> nextPlayer = players_sorted_escape[escape_rank];
			cout << "이전 등수 ID  : " << prevPlayer->getId() << "	점수 : " << prevPlayer->getEscapeScore() << "	  순위 : " << prevPlayer->getEscapeRank() << endl;
			cout << "이후 등수 ID  : " << nextPlayer->getId() << "	점수 : " << nextPlayer->getEscapeScore() << "	  순위 : " << nextPlayer->getEscapeRank() << endl;
		}
		else if (school_rank == 1) {
			shared_ptr<Player> nextPlayer = players_sorted_escape[escape_rank];
			cout << "이후 등수 ID  : " << nextPlayer->getId() << "	점수 : " << nextPlayer->getEscapeScore() << "	  순위 : " << nextPlayer->getEscapeRank() << endl;
			cout << "당신보다 빠른 쿠키는 없습니다." << endl;
		}
		else if (school_rank == player_num) {
			shared_ptr<Player> prevPlayer = players_sorted_escape[escape_rank - 2];
			cout << "이전 등수 ID  : " << prevPlayer->getId() << "	점수 : " << prevPlayer->getEscapeScore() << "	  순위 : " << prevPlayer->getEscapeRank() << endl;
			cout << "당신보다 느린 쿠키는 없습니다. " << endl;
		}
	

	}


	void playSchool()
	{
		//게임 실행을 위한 변수
		int play_num = PLAYPlAYERSNUM;																				//한번에 플레이 되는 인원
		uniform_int_distribution<int> player_index_distribution(0, player_num - 1);								//랜덤한 학교 플레이어를 뽑기 위한 분포	//-1은 한 이유는 인덱스 값으로 플레이어를 찾기 때문

																												//플레이 이전의 플레이어의 랭킹 설정
		int prev_school_rank = player->getSchoolRank();
		int prev_escape_rank = player->getEscapeRank();

		//////////////////////////////////////////////////////////쿠키 훈련소 탈출 플레이/////////////////////////////////////////////////////

		//쿠키 훈련소 탈출 점수 분포 설정
		random_device rd;
		default_random_engine dre(rd());
		auto schoolDistribution = getSchoolDistribution();

		//나부터 실행
		int temp_score = static_cast<int>(schoolDistribution(dre));										//랜덤적으로 값을 추출

		if (player->getSchoolScore() < temp_score)										//플레이어의 훈련소 탈출 점수가 랜덤 추출 값보다 작을 경우
			player->setSchoolScore(temp_score);											//랜덤 추출 값으로 값을 갱신

																						//나머지 플레이어 실행
		vector<int>played_indexs;				//플레이한 플레이어들의 인덱스들 저장
		played_indexs.reserve(player_num);
		int played_cnt = 1;						//실행된 플레이어 수 저장				//'나'를 실행 했으므로 1부터 
		int player_index = 0;					//플레이할 플레이어 인덱스

												//설정한 플레이 수 만큼의 플레이어 실행 (중복 x)
		while (played_cnt < play_num) {													//설정한 플레이 수 만큼 반복
			player_index = player_index_distribution(dre);								//설정할 인덱스 랜덤값으로 추출
			if (players_vec[player_index]->getPlayed() == false) {							//추출한 값이 플레이어가 실행을 안했었을시 
				temp_score = static_cast<int>(schoolDistribution(dre));									//랜덤 스코어값 추출
				if (players_vec[player_index]->getSchoolScore() < temp_score)			//추출한 값이 이전 훈련소 탈출 점수보다 높으면
					players_vec[player_index]->setSchoolScore(temp_score);				//추출한 값으로 훈련소 탈출 점수 갱신
				++played_cnt;															//플레이했다를 1번 증가		
			}
		}

		setSchoolRank();
	}

	void playEscape() {
		//게임 실행을 위한 변수
		int play_num = PLAYPlAYERSNUM;																				//한번에 플레이 되는 인원
		uniform_int_distribution<int> player_index_distribution(0, player_num - 1);								//랜덤한 학교 플레이어를 뽑기 위한 분포	//-1은 한 이유는 인덱스 값으로 플레이어를 찾기 때문

																												//플레이 이전의 플레이어의 랭킹 설정
		int prev_school_rank = player->getSchoolRank();
		int prev_escape_rank = player->getEscapeRank();


		//떼탈출 분포 설정
		random_device rd;
		default_random_engine dre(rd());
		auto escapeDistribution = getEscapeDistribution();

		//나부터 실행
		int temp_score = static_cast<int>(escapeDistribution(dre));										//랜덤적으로 값을 추출

		if (player->getEscapeScore() < temp_score)										//플레이어의 훈련소 탈출 점수가 랜덤 추출 값보다 작을 경우
			player->setEscapeScore(temp_score);											//랜덤 추출 값으로 값을 갱신

																		
		//나머지 플레이어 실행
		vector<int>played_indexs;				//플레이한 플레이어들의 인덱스들 저장
		played_indexs.reserve(player_num);
		int played_cnt = 1;						//실행된 플레이어 수 저장				//'나'를 실행 했으므로 1부터 
		int player_index = 0;					//플레이할 플레이어 인덱스

											//설정한 플레이 수 만큼의 플레이어 실행 (중복 x)
		while (played_cnt < play_num) {													//설정한 플레이 수 만큼 반복
			player_index = player_index_distribution(dre);								//설정할 인덱스 랜덤값으로 추출
			if (players_vec[player_index]->getPlayed() == false) {							//추출한 값이 플레이어가 실행을 안했었을시 
				temp_score = static_cast<int>(escapeDistribution(dre));									//랜덤 스코어값 추출
				if (players_vec[player_index]->getEscapeScore() < temp_score)			//추출한 값이 이전 훈련소 탈출 점수보다 높으면
					players_vec[player_index]->setEscapeScore(temp_score);				//추출한 값으로 훈련소 탈출 점수 갱신
				++played_cnt;															//플레이했다를 1번 증가		
			}
		}

		setEscapeRank();
	}
	//게임 프레임 워크의 정보를 출력하는 함수

	void showPlayersInfo(const vector<shared_ptr<Player>> & players)const 
	{
		if (players.size() > 1000) {
			int increase_num = players.size() / 100;
			for (int i = 0; i < player_num; i += increase_num)
				players[i]->showInfo();}

		else {
			for (const shared_ptr<Player> & p : players)
				p->showInfo();}

		cout << "플레이어가 너무 많을 경우 일부분의 플레이어만 출력합니다." << endl;
	}

	~Handler()
	{
		//임시 백터를 만들어서 거기에 값을 복사한후 파일에 저장
		vector<Player> v;
		v.reserve(player_num);
		for (const shared_ptr<Player> & p : players_vec) {
			v.emplace_back(*p);
		}
		
		ofstream out("과제1.dat", ios::binary); //binary와 txt차이는?
		out.write((const char*)v.data(), sizeof(Player) * player_num);

		//벡터를 소멸시킴
		v.~vector();
		players_vec.~vector();
		players_sorted_school.~vector();
		players_sorted_escape.~vector();
	}
};


int main()
{
	Handler gfw;
	gfw.activate();

}