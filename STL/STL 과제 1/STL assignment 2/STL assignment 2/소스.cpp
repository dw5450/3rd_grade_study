#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <chrono>

#define INITPAYERNUM 100000
#define SCHOLLMAXSCORE 37000000
#define ESCAPEMAXSCORE 41000000
#define PLAYPlAYERSNUM 10000

using namespace std;
class CGamePlayer
{
public:
	CGamePlayer(int iId, int iSchool_Score, int iEscape_Score) :
		m_iId(iId), m_iSchool_Score(iSchool_Score), m_iEscape_Score(iEscape_Score){}
	void SetInfo(int iId, int iSchool_Score, int iEscape_Score) {
		m_iId = iId;	//�ڽ��� ���̵�	
		m_iSchool_Score = iSchool_Score;//��Ű �Ʒü� ����
		m_iEscape_Score = iEscape_Score;	//��Ű �Ʒü� ����
	}

	int GetId()const { return m_iId; }
	int GetSchoolScore()const { return m_iSchool_Score; }
	int GetEscapeScore()const { return m_iEscape_Score; }
	int GetSchoolRank()const { return m_iSchool_Rank; }
	int GetEscapeRank()const { return m_iEscape_Rank;  }
	bool GetPlayed()const { return m_bPlayed; }
	void SetSchoolScore(int iSchool_Score) {  m_iSchool_Score = iSchool_Score; }
	void SetEscapeScore(int iEscape_Score) { m_iEscape_Score = iEscape_Score; }
	void SetSchoolRank(int iSchoo_lRank) { m_iSchool_Rank = iSchoo_lRank; }
	void SetEscapeRank(int iEscape_Rank) { m_iEscape_Rank = iEscape_Rank; }
	void SetPlayed(bool bPlayed) { m_bPlayed = bPlayed; }
	void ShowInfo()const {
		cout << "ID : " << m_iId << endl;
		cout << "��Ű �Ʒü� ��ũ	: " << m_iSchool_Rank << "       ��Ű �Ʒü� ����	: " << m_iSchool_Score << endl;
		cout << "��Ż�� ��ũ		: " << m_iEscape_Rank << "       ��Ż�� ����	: " << m_iEscape_Score  <<endl;
		cout << "----------------------------------------------------------------------------------------" << endl;
	}

private:
	int m_iId;					//�ڽ��� ���̵�	
	int m_iSchool_Score = 0;		//��Ű �Ʒü� ����
	int m_iEscape_Score = 0;		//��Ű �Ʒü� ����
	int m_iSchool_Rank = 0;		//��Ű �Ʒü� ����
	int m_iEscape_Rank = 0;		//��Ű �Ʒü� ����
	bool m_bPlayed = false;				//������ �߾���.					//�÷��̿��� �����ϱ� ���ؼ�
};



class CGameFramWork
{
public:
	CGameFramWork()
	{
		auto begin = chrono::high_resolution_clock::now();
		m_iPlayer_Num = 0;
		m_sLoad_Data_Name = "�÷��̾�����";
		m_pvSorted_School_Players.reserve(INITPAYERNUM);//���� �޸� ũ�� �ʱ�ȭ
		m_pvSorted_Escape_Players.reserve(INITPAYERNUM);
		m_uidSchool_Distribuition = uniform_int_distribution<int>(0, SCHOLLMAXSCORE);
		m_uidEacape_Distribuition = uniform_int_distribution<int>(0, ESCAPEMAXSCORE);
		ifstream player_in(m_sLoad_Data_Name, ios::binary);
		m_pvPlayers.reserve(INITPAYERNUM);
		if (player_in) {
			//vector<CGamePlayer> temp_players(INITPAYERNUM);
			//player_in.read(reinterpret_cast<char *> (temp_players.data()), sizeof(shared_ptr<CGamePlayer>) * m_iPlayer_Num);				//������ ���尡 ����� �ȵ� ����
																																			//���� �ϳ��� ��� �ϸ� �� ������ ������?
		}
		else
		{	//��ü �÷��̾� ����,��ũ �ʱ�ȭ
			for (m_iPlayer_Num = 0; m_iPlayer_Num < INITPAYERNUM; ++m_iPlayer_Num) {
				m_pvPlayers.push_back(shared_ptr<CGamePlayer>(new CGamePlayer(m_iPlayer_Num, m_uidSchool_Distribuition(m_dre), m_uidEacape_Distribuition(m_dre))));
			}
		}
		m_pvSorted_School_Players = m_pvPlayers;
		m_pvSorted_Escape_Players = m_pvPlayers;
		SortSchoolRank();
		SortEscapeRank();
		
		//�÷��̾� ����
		m_pPlayer = m_pvPlayers[0];

		auto elapsetime = chrono::high_resolution_clock::now() - begin;
		cout << chrono::duration<double>(elapsetime).count() << endl;
	}
	//�б� Ż�� ���� ����				//���� ������ ���� �ʿ�
	void SortSchoolRank()																//���߿� ����			//�б� ������ ��Ʈ
	{
		sort(m_pvSorted_School_Players.begin(), m_pvSorted_School_Players.end(), [](const shared_ptr<CGamePlayer> & pP1, const shared_ptr<CGamePlayer> & pP2) {
			return pP1->GetSchoolScore() < pP2->GetSchoolScore();
		});

		for (int i = 0; i < m_iPlayer_Num; i++) {
			m_pvSorted_School_Players[i]->SetSchoolRank(i);
		}
	}
	void SortEscapeRank() {
		sort(m_pvSorted_Escape_Players.begin(), m_pvSorted_Escape_Players.end(), [](const shared_ptr<CGamePlayer> & pP1, const shared_ptr<CGamePlayer> & pP2) {
			return pP1->GetEscapeScore() < pP2->GetEscapeScore();
		});
		for (int i = 0; i < m_iPlayer_Num; i++) {
			m_pvSorted_Escape_Players[i]->SetEscapeRank(i);
		}
	};																//���߿� ����			//��Ż�� ������ ��Ʈ

	
	void SetPlayer()
	{
		cout << "'��'�� ������ id�� �Է��� �ּ��� 0 ~ " << INITPAYERNUM << endl;
		int temp_id;
		cin >> temp_id;
		// ���Ŀ� '��'�� ���� �մ� Ȯ���ؾ� �ϴ� �Լ� �߰� 

		if (0 < temp_id && temp_id < INITPAYERNUM) {
			m_pPlayer = m_pvPlayers[temp_id];
			cout << "�÷��̾� ������ �Ϸ� �Ǿ����ϴ�." << endl;
		}
		else
			cout << " �÷��̾ ���� �� �� �����ϴ�. " << endl;
		
	}
	void PlayPlayers()
	{
		PlaySchool();
		PlayEscape();
		cout << "----------------------------------------------------------------" << endl;
	}
	void PlaySchool()
	{
		int iPlay_num = PLAYPlAYERSNUM;																				//�ѹ��� �÷��� �Ǵ� �ο�
		uniform_int_distribution<int> uidRandom_Player_Index(0, m_iPlayer_Num -1);										//�б� Ż�� ���� ����
		
		int play_idex = 0;
		int play_cnt = 0;																									//���� �÷��� �� ��
		int iPrev_Player_Rank = m_pPlayer->GetSchoolRank();
		//'������ �÷���																													//
	
		int temp_i = m_uidSchool_Distribuition(m_dre);
		if (temp_i > m_pPlayer->GetSchoolScore())
			m_pPlayer->SetSchoolScore(temp_i);
		++play_cnt;

		//s������ �÷��̾� �÷���
		vector<int>vPlayed_Index(iPlay_num);
		for (play_cnt; play_cnt < iPlay_num; )
		{
			play_idex = uidRandom_Player_Index(m_dre);
			if (m_pvSorted_School_Players[play_idex]->GetPlayed() == false)
			{
				temp_i = m_uidSchool_Distribuition(m_dre);
				if (temp_i > m_pvSorted_School_Players[play_idex]->GetSchoolScore())
					m_pvSorted_School_Players[play_idex]->SetSchoolScore(temp_i);

				m_pvSorted_School_Players[play_idex]->SetPlayed(true);
				vPlayed_Index.push_back(play_idex);
				++play_cnt;
			}
		}
		//��Ʈ!
		SortSchoolRank();
		for (auto & index : vPlayed_Index) {
			m_pvPlayers[index]->SetPlayed(false);
		}
		//���� ���!
		int iRank = m_pPlayer->GetSchoolRank();
		cout << "--------------------------------------------------��Ű �Ʒü�------------------------------------------------" << endl;
		cout << "�÷��̾��� ID  : " << m_pPlayer->GetId() << "		���� : " << m_pPlayer->GetSchoolScore() << "		���� : " << iRank << "		���� "<< double(m_iPlayer_Num / (iRank))<< "%" << "		��� ���� : " << iRank - iPrev_Player_Rank << endl;
		
		if (iRank > 0) {
			shared_ptr<CGamePlayer> prevPlayer = m_pvSorted_School_Players[iRank - 1];
			cout << "���� ��� ID  : " << prevPlayer->GetId() << "		���� : " << prevPlayer->GetSchoolScore() << "		���� : " << prevPlayer->GetSchoolRank() <<endl;
		}
		else if (iRank < m_iPlayer_Num -1) cout << "�װ� �ְ��.." << endl;
		else cout << "PlayEscape ���� ������ �߻��Ͽ����ϴ�" << endl;

		if (iRank < m_iPlayer_Num - 1) {
			shared_ptr<CGamePlayer> nextPlayer = m_pvSorted_School_Players[iRank + 1];
			cout << "���� ��� ID  : " << nextPlayer->GetId() << "		���� : " << nextPlayer->GetSchoolScore() << "		���� : " << nextPlayer->GetSchoolRank() << endl;
		}
		else if (iRank == 0) cout << " ����ó׿� ���" << endl;
		else cout << "PlayEscape ���� ������ �߻��Ͽ����ϴ�" << endl;

		vPlayed_Index.~vector();
	}
	void PlayEscape()
	{
		int iPlay_num = PLAYPlAYERSNUM;																				//�ѹ��� �÷��� �Ǵ� �ο�
		uniform_int_distribution<int> uidRandom_Player_Index(0, m_iPlayer_Num - 1);										//�б� Ż�� ���� ����
		int play_idex = 0;
		int play_cnt = 0;																									//���� �÷��� �� ��
		int iPrev_Player_Rank = m_pPlayer->GetEscapeRank();								//���� ��ŷ
		//'������ �÷���																													
		int temp_i = m_uidSchool_Distribuition(m_dre);
		if (temp_i > m_pPlayer->GetSchoolScore())
			m_pPlayer->SetSchoolScore(temp_i);
		++play_cnt;

		//������ �÷��̾� �÷���
		vector<int>vPlayed_Index(iPlay_num);
		for (play_cnt; play_cnt < iPlay_num - 1; )
		{
			play_idex = uidRandom_Player_Index(m_dre);
			if (m_pvSorted_Escape_Players[play_idex]->GetPlayed() == false)
			{
				if (temp_i > m_pvSorted_Escape_Players[play_idex]->GetEscapeScore())
					m_pvSorted_Escape_Players[play_idex]->SetEscapeScore(temp_i);
				m_pvSorted_Escape_Players[play_idex]->SetPlayed(true);
				vPlayed_Index.push_back(play_idex);
				++play_cnt;
			}
		}
		//��Ʈ!
		SortEscapeRank();
		for (auto & index : vPlayed_Index) {
			m_pvPlayers[index]->SetPlayed(false);
		}
		//���� ���!
		int iRank = m_pPlayer->GetEscapeRank();
		cout << "-----------------------------------------------------��Ż�� --------------------------------------------------" << endl;
		cout << "�÷��̾��� ID  : " << m_pPlayer->GetId() << "		���� : " << m_pPlayer->GetEscapeScore() << "		���� : " << iRank << "		���� " << double(m_iPlayer_Num / (iRank)) << "%" << "		��� ���� : " << iRank - iPrev_Player_Rank << endl;
		if (iRank > 0) {
			shared_ptr<CGamePlayer> prevPlayer = m_pvSorted_Escape_Players[iRank - 1];
			cout << "���� ��� ID  : " << prevPlayer->GetId() << "		���� : " << prevPlayer->GetEscapeScore() << "		���� : " << prevPlayer->GetEscapeRank() << endl;
		}
		else if (iRank < m_iPlayer_Num  -1) cout << "�װ� �ְ��.." << endl;
		else cout << "PlayEscape ���� ������ �߻��Ͽ����ϴ�" << endl;

		if (iRank < m_iPlayer_Num - 1) {
			shared_ptr<CGamePlayer> nextPlayer = m_pvSorted_Escape_Players[iRank + 1];
			cout << "���� ��� ID  : " << nextPlayer->GetId() << "		���� : " << nextPlayer->GetEscapeScore() << "		���� : " << nextPlayer->GetEscapeRank() << endl;
		}
		else if (iRank == 0) cout << " ����ó׿� ���" << endl;
		else cout << "PlayEscape ���� ������ �߻��Ͽ����ϴ�" << endl;

		vPlayed_Index.~vector();
	}
	void Ative()
	{
		char cKey_Input;
		while (1)
		{
		
			cout << "-------------------------------------------MENU----------------------------------------------------" << endl;
			cout << "��� :q -> id ��		w -> �Ʒü� ��ũ��		e -> ��Ż�� ��ũ��		r -> �÷��̾� ���� ���" << endl;
			cout << "���� :a -> ���� �÷���!			s -> ���� ����" << endl;
			cout << "--------------------------------------------------------------------------------------------------" << endl;
			cout << "�Է� : "; cin >> cKey_Input;
			if (cKey_Input == 'q' || cKey_Input == 'Q')
			{
				cout << "���̵� ������ ��� (10000�� ������)" << endl;
				for (int i = 0; i < m_iPlayer_Num; i += 10000) {
					m_pvPlayers[i]->ShowInfo();
				}
			}

			if (cKey_Input == 'w' || cKey_Input == 'W')
			{
				cout << "�Ʒü� ��ũ ������ ��� (10000�� ������)" << endl;
				for (int i = 0; i < m_iPlayer_Num; i += 10000) {

					m_pvSorted_School_Players[i]->ShowInfo();
					cout << "-----------------------------------------" << endl;
				}
			}

			if (cKey_Input == 'e' || cKey_Input == 'E')
			{
				cout << "��Ż�� ������ ��� (10000�� ������)" << endl;
				for (int i = 0; i < m_iPlayer_Num; i += 10000) {
					m_pvSorted_Escape_Players[i]->ShowInfo();
					cout << "-----------------------------------------" << endl;
				}
			}
			else if (cKey_Input == 'r' || cKey_Input == 'R')
			{
				cout << "�÷��̾� ���� ��� " << endl;
				m_pPlayer->ShowInfo();
			}

			else if (cKey_Input == 's' || cKey_Input == 'S')
			{
				break;
			}
			else if (cKey_Input == 'a' || cKey_Input == 'A')
			{
				auto begin = chrono::high_resolution_clock::now();
				PlayPlayers();
				cout << "��� �÷��̾�� �÷��� �Ϸ�!" << endl;

				auto elapsetime = chrono::high_resolution_clock::now() - begin;
				cout << chrono::duration<double>(elapsetime).count() << endl;
			}
		}
	}
	~CGameFramWork()
	{
		//���̺� �� ���α׷� ����
		//	ofstream player_out(m_sLoad_Data_Name, ios::binary);										
		//player_out.write(reichar *> (pvPlayers.data()), ios::binary);
		m_sLoad_Data_Name.~string();
	}



private:
	default_random_engine m_dre;
	uniform_int_distribution<int> m_uidSchool_Distribuition;											//��Ű �Ʒü� ���� ����
	uniform_int_distribution<int> m_uidEacape_Distribuition;											//��Ż�� ���� ����
	int m_iPlayer_Num;																			// �÷��̾� ��
	string m_sLoad_Data_Name;																	//�ҷ��� ����Ÿ�� �̸�
	shared_ptr<CGamePlayer> m_pPlayer;
	vector<shared_ptr<CGamePlayer>> m_pvPlayers;																//�÷��̾���� ����		
	vector<shared_ptr<CGamePlayer>> m_pvSorted_School_Players;										//��Ű �Ʒüҷ� ������ ���ĵ� �÷��̾� ����
	vector<shared_ptr<CGamePlayer>> m_pvSorted_Escape_Players;										//��Ű �Ʒüҷ� ������ ���ĵ� �÷��̾� ����
};

void test(shared_ptr<CGamePlayer> p1)
{

}
int main()
{

	CGameFramWork gfw;
	gfw.Ative();

}