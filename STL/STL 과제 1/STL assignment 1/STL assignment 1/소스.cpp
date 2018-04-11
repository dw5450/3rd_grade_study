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

//�÷��̾��� ������ ������ �ִ� Ŭ����
class Player
{
private:
	int id = 0;					//���̵�	
	int school_score = 0;		//��Ű �Ʒü� ����
	int escape_score = 0;		//��Ż�� ����
	int school_rank = 0;		//��Ű �Ʒü� ��ũ
	int escape_rank = 0;		//��Ż�� ��ũ
	bool played = false;		//�÷��� ���� ����					//�÷��̿��� �����ϱ� ���ؼ�				//���� �˰��� ���� ���� ����

public:
	//�÷��̾��� ������ �ʱ�ȭ �ϴ� �Լ�
	Player() {};
	Player(int id, int school_score, int escape_score) :												//������
		id(id), school_score(school_score), escape_score(escape_score) {}
	void setInfo(int id, int school_score, int escape_score) {											//�ڽ��� ���� ����, �����ڿ� ������ ���ڷ�.
		this->id = id;	
		this->school_score = school_score;
		this->escape_score = escape_score;	
	}	

	//�Ҹ���
	~Player() {}

	//�÷��̾��� ������ �������� get , const �Լ���
	int getId()const { return id; }
	int getSchoolScore()const { return school_score; }
	int getEscapeScore()const { return escape_score; }
	int getSchoolRank()const { return school_rank; }
	int getEscapeRank()const { return escape_rank; }
	bool getPlayed()const { return played; }

	//�÷��̾��� ������ �����ϴ� set �Լ���
	void setSchoolScore(int school_score) { this->school_score = school_score; }
	void setEscapeScore(int escape_score) { this->escape_score = escape_score; }
	void setSchoolRank(int school_rank) { this->school_rank = school_rank; }
	void setEscapeRank(int escape_rank) { this->escape_rank = escape_rank; }
	void setPlayed(bool played) { this->played = played; }

	//�÷��̾��� ������ ��� �ϴ� �Լ�
	void showInfo()const {
		cout << "ID : " << id << endl;
		cout << "��Ű �Ʒü� ��ũ : " << school_rank << "      ��Ű �Ʒü� ���� : " << school_score << endl;
		cout << "��Ż�� ��ũ	 : " << escape_rank << "      ��Ż�� ����      : " << escape_score << endl;
		cout << "----------------------------------------------------------------------------------------" << endl;
	}
};


//������ �����ϴ� Ŭ����
class Handler
{
private:
	int player_num = 0;									//���� �÷��̾��� ��
	shared_ptr<Player> player;							//�÷��̾ ����Ű�� ������
	vector<shared_ptr<Player>> players_vec;				//ó�� ������� ���� ���ĵ� �÷��̾���� ������ ����
	vector<shared_ptr<Player>> players_sorted_school;	//��Ű �Ʒü� ������ ���ĵ� �÷��̾���� ������ ����
	vector<shared_ptr<Player>> players_sorted_escape;	//�� Ż�������� ���ĵ� �÷��̾���� ������ ����

public:

	//Handler�� �ʱ�ȭ �ϴ� �Լ�
	Handler()																											//������
	{	//�÷��̾� ���� �޸� ����
		players_vec.reserve(INITPAYERNUM);
		players_sorted_school.reserve(INITPAYERNUM);
		players_sorted_escape.reserve(INITPAYERNUM);

		ifstream in("����1.dat", ios::binary); //binary�� txt���̴�?

		//������ ������ ��� ���� �о ���α׷� ����, ������ �÷��̾���� ����� ����
		if (in) {
			//�����ͷ� �ٷ� ������ ���̴� �ϴ� ���� �����صΰ� �װͿ� �����͸� ����Ű����
			vector<Player> v(INITPAYERNUM);
			in.read((char*)v.data(), sizeof(Player) * INITPAYERNUM);
	
			for (int i = 0; i< v.size(); ++i)
				players_vec.push_back(make_shared<Player>(v[i]));

			player_num = INITPAYERNUM;
		}
		else 
		{

			//������ ���� ���� �� ����			//���Ŀ� ������ ���� �� �����ϰ� �����ؾ���
			random_device rd;					// dre.seed ��� ���ɷ� �ʱ�ȭ������.
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
		//��Ű �Ʒü� ���� ���Ϳ� �� �ʱ�ȭ, ���� �� ��ũ�� ����
		players_sorted_school = players_vec;
		setSchoolRank();

		////��Ż�� ���� ���Ϳ� �� �ʱ�ȭ, ���� �� ��ũ�� ����
		players_sorted_escape = players_vec;
		setEscapeRank();

		//�÷��̾� ����				//����Ʈ ������ ù �÷��̾ �÷��̾�� ������, ���� ���� ���� �����ϵ���
		player = players_vec[0];
	
	}

	//���α׷� �۵��� ���� �Լ�

	void activate() {
		while (1)
		{
			cout << "-------------------------------------------MENU----------------------------------------------------" << endl;
			cout << "��� :q -> id ��	w -> �Ʒü� ��ũ��	e -> ��Ż�� ��ũ��	r -> �÷��̾� ���� ���" << endl;
			cout << "���� :a -> ���� �÷���!		s -> ���� ����" << endl;
			cout << "--------------------------------------------------------------------------------------------------" << endl;
			char key;
			cout << "�Է� : "; cin >> key;
			system("cls");

			if (key == 'q' || key == 'Q')
			{
				//id������ �� �÷��̾� ���
				showPlayersInfo(players_vec);
			}

			if (key == 'w' || key == 'W')
			{
				//�Ʒü� ��ũ������ ���� �� �÷��̾� ���
				showPlayersInfo(players_sorted_school);
			}

			if (key == 'e' || key == 'E')
			{
				//��Ż�� ��ũ������ ���� �� �÷��̾� ���
				showPlayersInfo(players_sorted_escape);
				
			}
			else if (key == 'r' || key == 'R')
			{
				cout << "�÷��̾� ���� ��� " << endl;
				player->showInfo();
			}

			else if (key == 's' || key == 'S')
			{
				cout << "���α׷��� �����մϴ�." << endl;
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

	
	//�ڵ鷯�� ������ �������� �Լ�
	normal_distribution<> getSchoolDistribution() const {
		return  normal_distribution<>(SCHOLLMAXSCORE / 2, static_cast<int>(SCHOLLMAXSCORE / 20));
	}

	normal_distribution<> getEscapeDistribution() const {
		return  normal_distribution<>(ESCAPEMAXSCORE / 2, static_cast<int>(ESCAPEMAXSCORE / 20));
	}


	//�ڵ鷯�� ������ ���� �ϴ� �Լ�
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
		
		//�÷��� ������ �÷��̾��� ��ŷ ����
		int prev_school_rank = player->getSchoolRank();
		int prev_escape_rank = player->getEscapeRank();

		//��Ű �Ʒü� ����!
		playSchool();
		//��Ż�� ����!
		playEscape();

		//////////////////////////////////////////////////////�÷����� ���� ����� �÷��̾��� ���� ���//////////////////////////////////////////////
		int school_rank = player->getSchoolRank();
		cout << "--------------------------------------------------��Ű �Ʒü�--------------------------------------------" << endl;
		cout << "�÷��̾��� ID  : " << player->getId() << "	���� : " << player->getSchoolScore() << "	  ���� : " << school_rank << "	  ���� " << double(school_rank) / double(player_num) * 100 << "%" << "	  ��� ���� : " <<  prev_school_rank - school_rank << endl;

		if (1 < school_rank && school_rank < player_num) {
			shared_ptr<Player> prevPlayer = players_sorted_school[school_rank - 2];
			shared_ptr<Player> nextPlayer = players_sorted_school[school_rank];
			cout << "���� ��� ID  : " << prevPlayer->getId() << "	���� : " << prevPlayer->getSchoolScore() << "	  ���� : " << prevPlayer->getSchoolRank() << endl;
			cout << "���� ��� ID  : " << nextPlayer->getId() << "	���� : " << nextPlayer->getSchoolScore() << "	  ���� : " << nextPlayer->getSchoolRank() << endl;
		}
		else if (school_rank ==  1) {
			shared_ptr<Player> nextPlayer = players_sorted_school[school_rank];
			cout << "���� ��� ID  : " << nextPlayer->getId() << "	���� : " << nextPlayer->getSchoolScore() << "	  ���� : " << nextPlayer->getSchoolRank() << endl;
			cout << "��ź��� ���� ��Ű�� �����ϴ�." << endl;
		}
		else if (school_rank == player_num) {
			shared_ptr<Player> prevPlayer = players_sorted_school[school_rank - 2];
			cout << "���� ��� ID  : " << prevPlayer->getId() << "	���� : " << prevPlayer->getSchoolScore() << "	  ���� : " << prevPlayer->getSchoolRank() << endl;
			cout << "��ź��� ���� ��Ű�� �����ϴ�. " << endl;
		}



		int escape_rank = player->getEscapeRank();
		cout << "----------------------------------------------------�� Ż ��---------------------------------------------" << endl;
		cout << "�÷��̾��� ID  : " << player->getId() << "	���� : " << player->getEscapeScore() << "	  ���� : " << escape_rank << "	  ���� " << double(escape_rank) / double(player_num) * 100 << "%" << "	  ��� ���� : " << prev_escape_rank - escape_rank << endl;

		if (1 < escape_rank && escape_rank < player_num) {
			shared_ptr<Player> prevPlayer = players_sorted_escape[escape_rank - 2];
			shared_ptr<Player> nextPlayer = players_sorted_escape[escape_rank];
			cout << "���� ��� ID  : " << prevPlayer->getId() << "	���� : " << prevPlayer->getEscapeScore() << "	  ���� : " << prevPlayer->getEscapeRank() << endl;
			cout << "���� ��� ID  : " << nextPlayer->getId() << "	���� : " << nextPlayer->getEscapeScore() << "	  ���� : " << nextPlayer->getEscapeRank() << endl;
		}
		else if (school_rank == 1) {
			shared_ptr<Player> nextPlayer = players_sorted_escape[escape_rank];
			cout << "���� ��� ID  : " << nextPlayer->getId() << "	���� : " << nextPlayer->getEscapeScore() << "	  ���� : " << nextPlayer->getEscapeRank() << endl;
			cout << "��ź��� ���� ��Ű�� �����ϴ�." << endl;
		}
		else if (school_rank == player_num) {
			shared_ptr<Player> prevPlayer = players_sorted_escape[escape_rank - 2];
			cout << "���� ��� ID  : " << prevPlayer->getId() << "	���� : " << prevPlayer->getEscapeScore() << "	  ���� : " << prevPlayer->getEscapeRank() << endl;
			cout << "��ź��� ���� ��Ű�� �����ϴ�. " << endl;
		}
	

	}


	void playSchool()
	{
		//���� ������ ���� ����
		int play_num = PLAYPlAYERSNUM;																				//�ѹ��� �÷��� �Ǵ� �ο�
		uniform_int_distribution<int> player_index_distribution(0, player_num - 1);								//������ �б� �÷��̾ �̱� ���� ����	//-1�� �� ������ �ε��� ������ �÷��̾ ã�� ����

																												//�÷��� ������ �÷��̾��� ��ŷ ����
		int prev_school_rank = player->getSchoolRank();
		int prev_escape_rank = player->getEscapeRank();

		//////////////////////////////////////////////////////////��Ű �Ʒü� Ż�� �÷���/////////////////////////////////////////////////////

		//��Ű �Ʒü� Ż�� ���� ���� ����
		random_device rd;
		default_random_engine dre(rd());
		auto schoolDistribution = getSchoolDistribution();

		//������ ����
		int temp_score = static_cast<int>(schoolDistribution(dre));										//���������� ���� ����

		if (player->getSchoolScore() < temp_score)										//�÷��̾��� �Ʒü� Ż�� ������ ���� ���� ������ ���� ���
			player->setSchoolScore(temp_score);											//���� ���� ������ ���� ����

																						//������ �÷��̾� ����
		vector<int>played_indexs;				//�÷����� �÷��̾���� �ε����� ����
		played_indexs.reserve(player_num);
		int played_cnt = 1;						//����� �÷��̾� �� ����				//'��'�� ���� �����Ƿ� 1���� 
		int player_index = 0;					//�÷����� �÷��̾� �ε���

												//������ �÷��� �� ��ŭ�� �÷��̾� ���� (�ߺ� x)
		while (played_cnt < play_num) {													//������ �÷��� �� ��ŭ �ݺ�
			player_index = player_index_distribution(dre);								//������ �ε��� ���������� ����
			if (players_vec[player_index]->getPlayed() == false) {							//������ ���� �÷��̾ ������ ���߾����� 
				temp_score = static_cast<int>(schoolDistribution(dre));									//���� ���ھ ����
				if (players_vec[player_index]->getSchoolScore() < temp_score)			//������ ���� ���� �Ʒü� Ż�� �������� ������
					players_vec[player_index]->setSchoolScore(temp_score);				//������ ������ �Ʒü� Ż�� ���� ����
				++played_cnt;															//�÷����ߴٸ� 1�� ����		
			}
		}

		setSchoolRank();
	}

	void playEscape() {
		//���� ������ ���� ����
		int play_num = PLAYPlAYERSNUM;																				//�ѹ��� �÷��� �Ǵ� �ο�
		uniform_int_distribution<int> player_index_distribution(0, player_num - 1);								//������ �б� �÷��̾ �̱� ���� ����	//-1�� �� ������ �ε��� ������ �÷��̾ ã�� ����

																												//�÷��� ������ �÷��̾��� ��ŷ ����
		int prev_school_rank = player->getSchoolRank();
		int prev_escape_rank = player->getEscapeRank();


		//��Ż�� ���� ����
		random_device rd;
		default_random_engine dre(rd());
		auto escapeDistribution = getEscapeDistribution();

		//������ ����
		int temp_score = static_cast<int>(escapeDistribution(dre));										//���������� ���� ����

		if (player->getEscapeScore() < temp_score)										//�÷��̾��� �Ʒü� Ż�� ������ ���� ���� ������ ���� ���
			player->setEscapeScore(temp_score);											//���� ���� ������ ���� ����

																		
		//������ �÷��̾� ����
		vector<int>played_indexs;				//�÷����� �÷��̾���� �ε����� ����
		played_indexs.reserve(player_num);
		int played_cnt = 1;						//����� �÷��̾� �� ����				//'��'�� ���� �����Ƿ� 1���� 
		int player_index = 0;					//�÷����� �÷��̾� �ε���

											//������ �÷��� �� ��ŭ�� �÷��̾� ���� (�ߺ� x)
		while (played_cnt < play_num) {													//������ �÷��� �� ��ŭ �ݺ�
			player_index = player_index_distribution(dre);								//������ �ε��� ���������� ����
			if (players_vec[player_index]->getPlayed() == false) {							//������ ���� �÷��̾ ������ ���߾����� 
				temp_score = static_cast<int>(escapeDistribution(dre));									//���� ���ھ ����
				if (players_vec[player_index]->getEscapeScore() < temp_score)			//������ ���� ���� �Ʒü� Ż�� �������� ������
					players_vec[player_index]->setEscapeScore(temp_score);				//������ ������ �Ʒü� Ż�� ���� ����
				++played_cnt;															//�÷����ߴٸ� 1�� ����		
			}
		}

		setEscapeRank();
	}
	//���� ������ ��ũ�� ������ ����ϴ� �Լ�

	void showPlayersInfo(const vector<shared_ptr<Player>> & players)const 
	{
		if (players.size() > 1000) {
			int increase_num = players.size() / 100;
			for (int i = 0; i < player_num; i += increase_num)
				players[i]->showInfo();}

		else {
			for (const shared_ptr<Player> & p : players)
				p->showInfo();}

		cout << "�÷��̾ �ʹ� ���� ��� �Ϻκ��� �÷��̾ ����մϴ�." << endl;
	}

	~Handler()
	{
		//�ӽ� ���͸� ���� �ű⿡ ���� �������� ���Ͽ� ����
		vector<Player> v;
		v.reserve(player_num);
		for (const shared_ptr<Player> & p : players_vec) {
			v.emplace_back(*p);
		}
		
		ofstream out("����1.dat", ios::binary); //binary�� txt���̴�?
		out.write((const char*)v.data(), sizeof(Player) * player_num);

		//���͸� �Ҹ��Ŵ
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