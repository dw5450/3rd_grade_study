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
		m_iId = iId;	//자신의 아이디	
		m_iSchool_Score = iSchool_Score;//쿠키 훈련소 점수
		m_iEscape_Score = iEscape_Score;	//쿠키 훈련소 점수
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
		cout << "쿠키 훈련소 랭크	: " << m_iSchool_Rank << "       쿠키 훈련소 점수	: " << m_iSchool_Score << endl;
		cout << "떼탈출 랭크		: " << m_iEscape_Rank << "       떼탈출 점수	: " << m_iEscape_Score  <<endl;
		cout << "----------------------------------------------------------------------------------------" << endl;
	}

private:
	int m_iId;					//자신의 아이디	
	int m_iSchool_Score = 0;		//쿠키 훈련소 점수
	int m_iEscape_Score = 0;		//쿠키 훈련소 점수
	int m_iSchool_Rank = 0;		//쿠키 훈련소 점수
	int m_iEscape_Rank = 0;		//쿠키 훈련소 점수
	bool m_bPlayed = false;				//실행을 했었다.					//플레이에서 구분하기 위해서
};



class CGameFramWork
{
public:
	CGameFramWork()
	{
		auto begin = chrono::high_resolution_clock::now();
		m_iPlayer_Num = 0;
		m_sLoad_Data_Name = "플레이어정보";
		m_pvSorted_School_Players.reserve(INITPAYERNUM);//벡터 메모리 크기 초기화
		m_pvSorted_Escape_Players.reserve(INITPAYERNUM);
		m_uidSchool_Distribuition = uniform_int_distribution<int>(0, SCHOLLMAXSCORE);
		m_uidEacape_Distribuition = uniform_int_distribution<int>(0, ESCAPEMAXSCORE);
		ifstream player_in(m_sLoad_Data_Name, ios::binary);
		m_pvPlayers.reserve(INITPAYERNUM);
		if (player_in) {
			//vector<CGamePlayer> temp_players(INITPAYERNUM);
			//player_in.read(reinterpret_cast<char *> (temp_players.data()), sizeof(shared_ptr<CGamePlayer>) * m_iPlayer_Num);				//느낌이 리드가 제대로 안될 느낌
																																			//파일 하나에 어떻게 하면 다 담을수 있을까?
		}
		else
		{	//전체 플레이어 점수,랭크 초기화
			for (m_iPlayer_Num = 0; m_iPlayer_Num < INITPAYERNUM; ++m_iPlayer_Num) {
				m_pvPlayers.push_back(shared_ptr<CGamePlayer>(new CGamePlayer(m_iPlayer_Num, m_uidSchool_Distribuition(m_dre), m_uidEacape_Distribuition(m_dre))));
			}
		}
		m_pvSorted_School_Players = m_pvPlayers;
		m_pvSorted_Escape_Players = m_pvPlayers;
		SortSchoolRank();
		SortEscapeRank();
		
		//플레이어 설정
		m_pPlayer = m_pvPlayers[0];

		auto elapsetime = chrono::high_resolution_clock::now() - begin;
		cout << chrono::duration<double>(elapsetime).count() << endl;
	}
	//학교 탈출 랜덤 점수				//정규 분포로 변경 필요
	void SortSchoolRank()																//나중에 통합			//학교 점수로 소트
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
	};																//나중에 통합			//떼탈출 점수로 소트

	
	void SetPlayer()
	{
		cout << "'나'로 설정할 id를 입력해 주세요 0 ~ " << INITPAYERNUM << endl;
		int temp_id;
		cin >> temp_id;
		// 추후에 '나'가 현제 잇는 확인해야 하는 함수 추가 

		if (0 < temp_id && temp_id < INITPAYERNUM) {
			m_pPlayer = m_pvPlayers[temp_id];
			cout << "플레이어 설정이 완료 되었습니다." << endl;
		}
		else
			cout << " 플레이어를 설정 할 수 없습니다. " << endl;
		
	}
	void PlayPlayers()
	{
		PlaySchool();
		PlayEscape();
		cout << "----------------------------------------------------------------" << endl;
	}
	void PlaySchool()
	{
		int iPlay_num = PLAYPlAYERSNUM;																				//한번에 플레이 되는 인원
		uniform_int_distribution<int> uidRandom_Player_Index(0, m_iPlayer_Num -1);										//학교 탈출 랜덤 점수
		
		int play_idex = 0;
		int play_cnt = 0;																									//현제 플레이 된 수
		int iPrev_Player_Rank = m_pPlayer->GetSchoolRank();
		//'나부터 플레이																													//
	
		int temp_i = m_uidSchool_Distribuition(m_dre);
		if (temp_i > m_pPlayer->GetSchoolScore())
			m_pPlayer->SetSchoolScore(temp_i);
		++play_cnt;

		//s나머지 플레이어 플레이
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
		//소트!
		SortSchoolRank();
		for (auto & index : vPlayed_Index) {
			m_pvPlayers[index]->SetPlayed(false);
		}
		//정보 출력!
		int iRank = m_pPlayer->GetSchoolRank();
		cout << "--------------------------------------------------쿠키 훈련소------------------------------------------------" << endl;
		cout << "플레이어의 ID  : " << m_pPlayer->GetId() << "		점수 : " << m_pPlayer->GetSchoolScore() << "		순위 : " << iRank << "		상위 "<< double(m_iPlayer_Num / (iRank))<< "%" << "		등수 변동 : " << iRank - iPrev_Player_Rank << endl;
		
		if (iRank > 0) {
			shared_ptr<CGamePlayer> prevPlayer = m_pvSorted_School_Players[iRank - 1];
			cout << "이전 등수 ID  : " << prevPlayer->GetId() << "		점수 : " << prevPlayer->GetSchoolScore() << "		순위 : " << prevPlayer->GetSchoolRank() <<endl;
		}
		else if (iRank < m_iPlayer_Num -1) cout << "네가 최고야.." << endl;
		else cout << "PlayEscape 에서 오류가 발생하였습니다" << endl;

		if (iRank < m_iPlayer_Num - 1) {
			shared_ptr<CGamePlayer> nextPlayer = m_pvSorted_School_Players[iRank + 1];
			cout << "이후 등수 ID  : " << nextPlayer->GetId() << "		점수 : " << nextPlayer->GetSchoolScore() << "		순위 : " << nextPlayer->GetSchoolRank() << endl;
		}
		else if (iRank == 0) cout << " 꼴찌시네요 깔깔" << endl;
		else cout << "PlayEscape 에서 오류가 발생하였습니다" << endl;

		vPlayed_Index.~vector();
	}
	void PlayEscape()
	{
		int iPlay_num = PLAYPlAYERSNUM;																				//한번에 플레이 되는 인원
		uniform_int_distribution<int> uidRandom_Player_Index(0, m_iPlayer_Num - 1);										//학교 탈출 랜덤 점수
		int play_idex = 0;
		int play_cnt = 0;																									//현제 플레이 된 수
		int iPrev_Player_Rank = m_pPlayer->GetEscapeRank();								//이전 랭킹
		//'나부터 플레이																													
		int temp_i = m_uidSchool_Distribuition(m_dre);
		if (temp_i > m_pPlayer->GetSchoolScore())
			m_pPlayer->SetSchoolScore(temp_i);
		++play_cnt;

		//나머지 플레이어 플레이
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
		//소트!
		SortEscapeRank();
		for (auto & index : vPlayed_Index) {
			m_pvPlayers[index]->SetPlayed(false);
		}
		//정보 출력!
		int iRank = m_pPlayer->GetEscapeRank();
		cout << "-----------------------------------------------------떼탈출 --------------------------------------------------" << endl;
		cout << "플레이어의 ID  : " << m_pPlayer->GetId() << "		점수 : " << m_pPlayer->GetEscapeScore() << "		순위 : " << iRank << "		상위 " << double(m_iPlayer_Num / (iRank)) << "%" << "		등수 변동 : " << iRank - iPrev_Player_Rank << endl;
		if (iRank > 0) {
			shared_ptr<CGamePlayer> prevPlayer = m_pvSorted_Escape_Players[iRank - 1];
			cout << "이전 등수 ID  : " << prevPlayer->GetId() << "		점수 : " << prevPlayer->GetEscapeScore() << "		순위 : " << prevPlayer->GetEscapeRank() << endl;
		}
		else if (iRank < m_iPlayer_Num  -1) cout << "네가 최고야.." << endl;
		else cout << "PlayEscape 에서 오류가 발생하였습니다" << endl;

		if (iRank < m_iPlayer_Num - 1) {
			shared_ptr<CGamePlayer> nextPlayer = m_pvSorted_Escape_Players[iRank + 1];
			cout << "이후 등수 ID  : " << nextPlayer->GetId() << "		점수 : " << nextPlayer->GetEscapeScore() << "		순위 : " << nextPlayer->GetEscapeRank() << endl;
		}
		else if (iRank == 0) cout << " 꼴찌시네요 깔깔" << endl;
		else cout << "PlayEscape 에서 오류가 발생하였습니다" << endl;

		vPlayed_Index.~vector();
	}
	void Ative()
	{
		char cKey_Input;
		while (1)
		{
		
			cout << "-------------------------------------------MENU----------------------------------------------------" << endl;
			cout << "출력 :q -> id 순		w -> 훈련소 랭크순		e -> 때탈출 랭크순		r -> 플레이어 정보 출력" << endl;
			cout << "실행 :a -> 게임 플레이!			s -> 게임 종료" << endl;
			cout << "--------------------------------------------------------------------------------------------------" << endl;
			cout << "입력 : "; cin >> cKey_Input;
			if (cKey_Input == 'q' || cKey_Input == 'Q')
			{
				cout << "아이디 순으로 출력 (10000번 단위로)" << endl;
				for (int i = 0; i < m_iPlayer_Num; i += 10000) {
					m_pvPlayers[i]->ShowInfo();
				}
			}

			if (cKey_Input == 'w' || cKey_Input == 'W')
			{
				cout << "훈련소 랭크 순으로 출력 (10000번 단위로)" << endl;
				for (int i = 0; i < m_iPlayer_Num; i += 10000) {

					m_pvSorted_School_Players[i]->ShowInfo();
					cout << "-----------------------------------------" << endl;
				}
			}

			if (cKey_Input == 'e' || cKey_Input == 'E')
			{
				cout << "떼탈출 순으로 출력 (10000번 단위로)" << endl;
				for (int i = 0; i < m_iPlayer_Num; i += 10000) {
					m_pvSorted_Escape_Players[i]->ShowInfo();
					cout << "-----------------------------------------" << endl;
				}
			}
			else if (cKey_Input == 'r' || cKey_Input == 'R')
			{
				cout << "플레이어 정보 출력 " << endl;
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
				cout << "모든 플레이어들 플레이 완료!" << endl;

				auto elapsetime = chrono::high_resolution_clock::now() - begin;
				cout << chrono::duration<double>(elapsetime).count() << endl;
			}
		}
	}
	~CGameFramWork()
	{
		//세이브 후 프로그램 종료
		//	ofstream player_out(m_sLoad_Data_Name, ios::binary);										
		//player_out.write(reichar *> (pvPlayers.data()), ios::binary);
		m_sLoad_Data_Name.~string();
	}



private:
	default_random_engine m_dre;
	uniform_int_distribution<int> m_uidSchool_Distribuition;											//쿠키 훈련소 점수 분포
	uniform_int_distribution<int> m_uidEacape_Distribuition;											//떼탈출 점수 분포
	int m_iPlayer_Num;																			// 플레이어 수
	string m_sLoad_Data_Name;																	//불러올 데이타의 이름
	shared_ptr<CGamePlayer> m_pPlayer;
	vector<shared_ptr<CGamePlayer>> m_pvPlayers;																//플레이어들의 정보		
	vector<shared_ptr<CGamePlayer>> m_pvSorted_School_Players;										//쿠키 훈련소로 점수로 정렬된 플레이어 백터
	vector<shared_ptr<CGamePlayer>> m_pvSorted_Escape_Players;										//쿠키 훈련소로 점수로 정렬된 플레이어 백터
};

void test(shared_ptr<CGamePlayer> p1)
{

}
int main()
{

	CGameFramWork gfw;
	gfw.Ative();

}