#include"MBUTTON.h"
#include"RuleInitSpace.h"
#include"initspace.h"
#include<ctime>
#include<cmath>
#include<graphics.h>
#include <sstream> // ������׼���е��ַ�����ͷ�ļ�
#include <iomanip> // �������ø��������ȵ�ͷ�ļ�
using namespace init;
using namespace RuleInit;

//24.12.13���賿12�㣬�����������Button�Ķ���
//24.12.14����22�㣬��Ҫ�����Ϸ�����߼��Ĵ��ͬʱҪ����endgame��clearmenu������߼���ϵ���������е��ظ��ˣ������Ƿ�Ҫ������ͣ��ť
//24.12.21�賿12�㣬�����ui����ĸ��£�������Ҫ���ģʽ��ѡ�񲿷ֵĴ��룬�Լ���Ϸ����������ģʽ�ĸı䣬�Լ�������棬�������߽��棨ɾ�������а񣩣���ʼ��Ϸǰ���뵹��

//�������ð�ť��ֵ
inline void resetbuttons() {
	int n = 0;
	int a[8][2] = {0};
	COLOR ass[8] = { black,green,yellow,red,brown,blue,purple,cyan };
	wstring s[8]= { { _T("��ɫ") } ,{ _T("��ɫ") } ,{ _T("��ɫ") } ,{ _T("��ɫ") } ,
					{ _T("��ɫ") } ,{ _T("��ɫ") } ,{ _T("��ɫ") }, { _T("��ɫ") } };
	wstring tmps;
	srand(time(0));
	int tmp1,tmp2;
	while (n < 8) {
		tmp1 = rand() % 8, tmp2 = rand() % 8;
		if (!a[tmp1][0] && !a[tmp2][1]) {
			tmps = s[tmp2];
			switch (n) {
			case 0:player1.reset(ass[tmp1], tmps); break;
			case 1:player2.reset(ass[tmp1], tmps); break;
			case 2:player3.reset(ass[tmp1], tmps); break;
			case 3:player4.reset(ass[tmp1], tmps); break;
			case 4:player5.reset(ass[tmp1], tmps); break;
			case 5:player6.reset(ass[tmp1], tmps); break;
			case 6:player7.reset(ass[tmp1], tmps); break;
			case 7:player8.reset(ass[tmp1], tmps); break;
			}
			a[tmp1][0] = a[tmp2][1] = 1;
			n++;
		}
	}
	while (1) {
		tmp1 = rand() % 8, tmp2 = rand() % 8;
		if (tmp1 != tmp2) {
			tmps = s[tmp2];
			question.reset(ass[tmp1], tmps);
			break;
		}
	}
}

//����player�ఴť
inline void putplayers() {
	question.putthings();
	player1.putthings();
	player2.putthings();
	player3.putthings();
	player4.putthings();
	player5.putthings();
	player6.putthings();
	player7.putthings();
	player8.putthings();
}

//���õ�ǰģʽ�ı�
IMAGE CHMODEBK, CHMODE_REPLACE;
wstring nowmode = _T("��ǰģʽΪ��");
IMAGE NOWMODE;
inline void putnowmode() {
	RECT nowmode_rect = { 0,0,1280,150 };
	nowmode = _T("��ǰģʽΪ��");

	switch (GAMEMODE) {
	case race: {
		nowmode += _T("����ģʽ");
		if (DIFFICULTY_TIME == 15)nowmode += _T(" - 15��");
		else if (DIFFICULTY_TIME == 30)nowmode += _T(" - 30��");
		else nowmode += _T(" - 60��");
		break;
	}
	case survival: {
		nowmode += _T("����ģʽ");
		if (DIFFICULTY_HP == 5)nowmode += _T(" - 5����ֵ");
		else if (DIFFICULTY_HP == 3)nowmode += _T(" - 3����ֵ");
		else nowmode += _T(" - 1����ֵ");
		break;
	}
	case limit: {
		nowmode += _T("����ģʽ");
		if (DIFFICULTY_TIME == 5)nowmode += _T(" - 5��");
		else if (DIFFICULTY_TIME == 3)nowmode += _T(" - 3��");
		else nowmode += _T(" - 8��");
		break;
	}
	case hell: {
		nowmode += _T("����ģʽ");
		if (DIFFICULTY_TIME == 5)nowmode += _T(" - 5��");
		else if (DIFFICULTY_TIME == 3)nowmode += _T(" - 3��");
		else nowmode += _T(" - 8��");
		if (DIFFICULTY_HP == 5)nowmode += _T(" - 5����ֵ");
		else if (DIFFICULTY_HP == 3)nowmode += _T(" - 3����ֵ");
		else nowmode += _T(" - 1����ֵ");
		break;
	}
	}
	settextcolor(YELLOW);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("��������"));
	//putimage(0, 0, &CHMODE_REPLACE);
	Putimage(210, 35, &NOWMODE);
	drawtext(nowmode.c_str(), &nowmode_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

inline void choosemode_clearmenu();

//�Ժ�����̽����
IMAGE PA;
IMAGE LATER;
inline void putpa();

int main() {
	//��ʼ�����ڡ���ť�Լ�����
	initgraph(1280,720);
	IMAGE INITBACKGROUND;
	loadimage(&INITBACKGROUND, _T("images/INITBACKGROUND.png"));
	putimage(0, 0, &INITBACKGROUND);
	IMAGE OTBACKGROUND;
	loadimage(&OTBACKGROUND, _T("images/OTHERBACKGROUND.png"));
	loadimage(&NOWMODE, _T("images/chmode/nowmodebk.png"));
	IMAGE CLEARMENUBK;
	loadimage(&CLEARMENUBK, _T("images/clearmenu/CLEARMENUBK.png"));
	BeginBatchDraw();

	//������
	loadimage(&PA, _T("images/PA.png"));
	loadimage(&LATER, _T("images/LATER.png"));

	//���������ʽ
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("��������"));

	//��ʼ��ģʽ����ͼƬ
	loadimage(&CHMODEBK, _T("images/chmode/CHMODEBK.png"));
	loadimage(&CHMODE_REPLACE, _T("images/chmode/CHMODEBK_REPLACE.png"));

	//����question�Լ�player���ı�����
	question.settype(1);
	player1.settype(2);
	player2.settype(2);
	player3.settype(2);
	player4.settype(2);
	player5.settype(2);
	player6.settype(2);
	player7.settype(2);
	player8.settype(2);

	//��ʼ������ͼƬ
	IMAGE REPLACE_TIME;
	IMAGE REPLACE_SCORE;
	loadimage(&REPLACE_TIME, _T("images/REPLACE_INF.png"));
	loadimage(&REPLACE_SCORE, _T("images/REPLACE_SCORE.png"));

	//��ʼ������ͼƬ�������������ť�������ʷ�������24.12.23
	/*IMAGE RULE_BK;
	loadimage(&RULE_BK, _T("images/RULE_BK.png"));
	resetbuttons();*/

	//��ʼ�����а�ͼƬ
	IMAGE RANKINGLIST_BK;
	loadimage(&RANKINGLIST_BK, _T("images/RANKINGLIST_BK.png"));

	//��ʼ������ť��ֵ
	race_modebtn.setGamemode(race);
	survival_modebtn.setGamemode(survival);
	limit_modebtn.setGamemode(limit);
	hell_modebtn.setGamemode(hell);

	//��ʼ���ѶȰ�ť���Ѷ�ֵ
	diftime30btn.setdifficulty(30);
	diftime15btn.setdifficulty(15);
	diftime60btn.setdifficulty(60);
	diftime3btn.setdifficulty(3);
	diftime5btn.setdifficulty(5);
	diftime8btn.setdifficulty(8);
	difhp5btn.setdifficulty(5);
	difhp3btn.setdifficulty(3);
	difhp1btn.setdifficulty(1);

	
	ExMessage msg;

	while (PROGRAM_RUNNING) {
		DWORD starttime = GetTickCount();

		//�������˵�ʱ
		putimage(0, 0, &INITBACKGROUND);
		if (INIT_MENU_RUNNING) {
			stbtn.putmenu();
			rlbtn.putmenu();
			exbtn.putmenu();
			chmodebtn.putmenu();
			rkbtn.putmenu();
			achbtn.putmenu();
			bgmbtn.putmenu();
			ababtn.putmenu();
		}
		while (INIT_MENU_RUNNING) {
			DWORD starttime_initmenu = GetTickCount();

			while (peekmessage(&msg)) {

				stbtn.checkstatus(msg);
				rlbtn.checkstatus(msg);
				exbtn.checkstatus(msg);
				chmodebtn.checkstatus(msg);
				rkbtn.checkstatus(msg);
				achbtn.checkstatus(msg);
				bgmbtn.checkstatus(msg);
				ababtn.checkstatus(msg);
				
				cleardevice();
				putimage(0, 0, &INITBACKGROUND);
				stbtn.putmenu();
				rlbtn.putmenu();
				exbtn.putmenu();
				chmodebtn.putmenu();
				rkbtn.putmenu();
				achbtn.putmenu();
				bgmbtn.putmenu();
				ababtn.putmenu();
			}

			FlushBatchDraw();
			DWORD endtime_initmenu = GetTickCount();
			DWORD process_initmenu = endtime_initmenu - starttime_initmenu;
			if (process_initmenu < 1000 / 60) {
				Sleep(1000 / 60 - process_initmenu);
			}
		}
		
		//�������а�
		putimage(0, 0, &OTBACKGROUND);
		if (rank) {
			//putimage(0, 0, &RANKINGLIST_BK);	//�����������а������
			remenubtn.putmenu();
			putpa();
		}
		while (rank) {
			DWORD starttime_rank = GetTickCount();

			while (peekmessage(&msg)) {
				remenubtn.checkstatus(msg);

				remenubtn.putmenu();
			}

			FlushBatchDraw();
			DWORD endtime_rank = GetTickCount();
			DWORD process_rank = endtime_rank - starttime_rank;
			if (process_rank < 1000 / 60) {
				Sleep(1000 / 60 - process_rank);
			}
		}

		//���ڳɾͽ���
		if (ACHIEVEMENT) {
			putimage(0, 0, &OTBACKGROUND);
			putpa();
			remenubtn.putmenu();

			while (ACHIEVEMENT) {
				DWORD starttime_ach = GetTickCount();

				while (peekmessage(&msg)) {
					remenubtn.checkstatus(msg);

					remenubtn.putmenu();
				}
				
				FlushBatchDraw();
				DWORD endtime_ach = GetTickCount();
				DWORD process_ach = endtime_ach - starttime_ach;
				if (process_ach < 1000 / 60) {
					Sleep(1000 / 60 - process_ach);
				}
			}

			cleardevice();
		}

		//�������ֽ���
		if (BGM) {
			putimage(0, 0, &OTBACKGROUND);
			putpa();
			remenubtn.putmenu();

			while (BGM) {
				DWORD starttime_bgm = GetTickCount();

				while (peekmessage(&msg)) {
					remenubtn.checkstatus(msg);

					remenubtn.putmenu();
				}

				FlushBatchDraw();
				DWORD endtime_bgm = GetTickCount();
				DWORD process_bgm = endtime_bgm - starttime_bgm;
				if (process_bgm < 1000 / 60) {
					Sleep(1000 / 60 - process_bgm);
				}
			}

			cleardevice();
		}

		//���ڹ������߽���
		if (ABOUTAUTHOR) {
			putimage(0, 0, &OTBACKGROUND);
			putpa();
			remenubtn.putmenu();

			while (ABOUTAUTHOR) {
				DWORD starttime_aba = GetTickCount();

				while (peekmessage(&msg)) {
					remenubtn.checkstatus(msg);

					remenubtn.putmenu();
				}

				FlushBatchDraw();
				DWORD endtime_aba = GetTickCount();
				DWORD process_aba = endtime_aba - starttime_aba;
				if (process_aba < 1000 / 60){
					Sleep(1000 / 60 - process_aba);
				}
			}

			cleardevice();
		}

		//������Ϸ����
		putimage(0, 0, &OTBACKGROUND);
		if (rule) {
			//���ð�ť
			mainrule.setmain();
			mainrule.put();
			racerule.put();
			survivalrule.put();
			limitrule.put();
			hellrule.put();
			proprule.put();
			remenubtn.putmenu();
		}
		while (rule) {
			DWORD starttime_rule = GetTickCount();

			while (peekmessage(&msg)) {
				mainrule.checkstatus(msg);
				racerule.checkstatus(msg);
				survivalrule.checkstatus(msg);
				limitrule.checkstatus(msg);
				hellrule.checkstatus(msg);
				proprule.checkstatus(msg);
				remenubtn.checkstatus(msg);

				cleardevice();
				putimage(0, 0, &OTBACKGROUND);
				mainrule.put();
				racerule.put();
				survivalrule.put();
				limitrule.put();
				hellrule.put();
				proprule.put();
				remenubtn.putmenu();
			}

			FlushBatchDraw();
			DWORD endtime_rule = GetTickCount();
			DWORD process_rule = endtime_rule - starttime_rule;
			if (process_rule < 1000 / 60) {
				Sleep(1000 / 60 - process_rule);
			}
		}
		if (NOW_RULE != NULL && *NOW_RULE)*NOW_RULE = false;

		//������Ϸģʽѡ��
		while (CHOOSE_GAMEMODE) {
			cleardevice();
			putimage(0, 0, &CHMODEBK);
			DWORD starttime_chmode = GetTickCount();
			//wstring pre_nowmode = nowmode;
			GameMode pre_gmmode = GAMEMODE;
			int pre_difficulty_time = DIFFICULTY_TIME;
			int pre_difficulty_hp = DIFFICULTY_HP;

			putnowmode();
			//peekmessage(&msg);
			remenubtn.checkstatus(msg);
			remenubtn.putmenu();
			race_modebtn.putmenu();
			survival_modebtn.putmenu();
			limit_modebtn.putmenu();
			hell_modebtn.putmenu();

			//��ʼģʽѡ�����
			while (CHOOSE_GAMEMODE_INIT) {
				DWORD starttime_chmode_init = GetTickCount();

				remenubtn.putmenu();
				race_modebtn.putmenu();
				survival_modebtn.putmenu();
				limit_modebtn.putmenu();
				hell_modebtn.putmenu();

				while (peekmessage(&msg)) {

					remenubtn.checkstatus(msg);
					race_modebtn.checkstatus(msg);
					survival_modebtn.checkstatus(msg);
					limit_modebtn.checkstatus(msg);
					hell_modebtn.checkstatus(msg);

					if (GAMEMODE != pre_gmmode) {
						putnowmode();
						pre_gmmode =GAMEMODE;
					}
					remenubtn.putmenu();
					race_modebtn.putmenu();
					survival_modebtn.putmenu();
					limit_modebtn.putmenu();
					hell_modebtn.putmenu();

				}

				FlushBatchDraw();
				DWORD endtime_chmode_init = GetTickCount();
				DWORD process_chmode_init = endtime_chmode_init - starttime_chmode_init;
				if (process_chmode_init < 1000 / 60) {
					Sleep(1000 / 60 - process_chmode_init);
				}
			}


			//��Ϸģʽ��race���涨ʱ���ڱ�ƴ��ȷ���� survival��������������һ���������� limit�����Ƶ�����Ŀ��ʱ�䣻 hell���������������Ƶ�����Ŀʱ��
			//���ѡ�����race
			if (GAMEMODE == race) {
				putimage(0, 0, &CHMODEBK);
				if (DIFFICULTY_TIME < 15)DIFFICULTY_TIME = 60;
				//GameMode pre_gmmode_inrace = GAMEMODE;

				//�ı�����λ��
				diftime30btn.setxy(490, 370);
				diftime60btn.setxy(490, 200);
				diftime15btn.setxy(490, 540);

				//���ð�ť���ı�����
				putnowmode();
				diftime30btn.putmenu();
				diftime60btn.putmenu();
				diftime15btn.putmenu();
				rechmodebtn.putmenu();

				while (CHOOSE_GAMEMODE_NEXT) {
					DWORD starttime_chmode_race = GetTickCount();

					while (peekmessage(&msg)) {
						rechmodebtn.checkstatus(msg);
						diftime30btn.checkstatus(msg);
						diftime60btn.checkstatus(msg);
						diftime15btn.checkstatus(msg);

						if (DIFFICULTY_TIME != pre_difficulty_time || DIFFICULTY_HP != pre_difficulty_hp) {
							putnowmode();
							pre_difficulty_time = DIFFICULTY_TIME;
							pre_difficulty_hp = DIFFICULTY_HP;
						}
						rechmodebtn.putmenu();
						diftime30btn.putmenu();
						diftime60btn.putmenu();
						diftime15btn.putmenu();
					}

					FlushBatchDraw();
					DWORD endtime_chmode_race = GetTickCount();
					DWORD process_chmode_race = endtime_chmode_race - starttime_chmode_race;
					if (process_chmode_race < 1000 / 60) {
						Sleep(1000 / 60 - process_chmode_race);
					}
				}
			}

			//���ѡ������ģʽ
			else if (GAMEMODE == survival) {
				//if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
				putimage(0, 0, &CHMODEBK);
				//GameMode pre_gmmode_inrace = GAMEMODE;

				//�ı�����λ��
				difhp5btn.setxy(490, 200);
				difhp3btn.setxy(490, 370);
				difhp1btn.setxy(490, 540);

				//���ð�ť���ı�����
				putnowmode();
				difhp5btn.putmenu();
				difhp3btn.putmenu();
				difhp1btn.putmenu();
				rechmodebtn.putmenu();

				while (CHOOSE_GAMEMODE_NEXT) {
					DWORD starttime_chmode_next = GetTickCount();

					while (peekmessage(&msg)) {
						rechmodebtn.checkstatus(msg);
						difhp5btn.checkstatus(msg);
						difhp3btn.checkstatus(msg);
						difhp1btn.checkstatus(msg);

						if (DIFFICULTY_TIME != pre_difficulty_time || DIFFICULTY_HP != pre_difficulty_hp) {
							putnowmode();
							pre_difficulty_time = DIFFICULTY_TIME;
							pre_difficulty_hp = DIFFICULTY_HP;
						}
						rechmodebtn.putmenu();
						difhp5btn.putmenu();
						difhp3btn.putmenu();
						difhp1btn.putmenu();
					}

					FlushBatchDraw();
					DWORD endtime_chmode_next = GetTickCount();
					DWORD process_chmode_next = endtime_chmode_next - starttime_chmode_next;
					if (process_chmode_next < 1000 / 60) {
						Sleep(1000 / 60 - process_chmode_next);
					}
				}
			}

			//ѡ����ģʽ��
			else if (GAMEMODE == limit) {
				if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
				putimage(0, 0, &CHMODEBK);
				//GameMode pre_gmmode_inrace = GAMEMODE;

				//�ı�����λ��
				diftime8btn.setxy(490, 200);
				diftime5btn.setxy(490, 370);
				diftime3btn.setxy(490, 540);

				//���ð�ť���ı�����
				putnowmode();
				diftime3btn.putmenu();
				diftime5btn.putmenu();
				diftime8btn.putmenu();
				rechmodebtn.putmenu();

				while (CHOOSE_GAMEMODE_NEXT) {
					DWORD starttime_chmode_next = GetTickCount();

					while (peekmessage(&msg)) {
						rechmodebtn.checkstatus(msg);
						diftime3btn.checkstatus(msg);
						diftime5btn.checkstatus(msg);
						diftime8btn.checkstatus(msg);

						if (DIFFICULTY_TIME != pre_difficulty_time || DIFFICULTY_HP != pre_difficulty_hp) {
							putnowmode();
							pre_difficulty_time = DIFFICULTY_TIME;
							pre_difficulty_hp = DIFFICULTY_HP;
						}
						rechmodebtn.putmenu();
						diftime3btn.putmenu();
						diftime5btn.putmenu();
						diftime8btn.putmenu();
					}

					FlushBatchDraw();
					DWORD endtime_chmode_next = GetTickCount();
					DWORD process_chmode_next = endtime_chmode_next - starttime_chmode_next;
					if (process_chmode_next < 1000 / 60) {
						Sleep(1000 / 60 - process_chmode_next);
					}
				}
			}

			//ѡ�����ģʽ��
			else if (GAMEMODE == hell) {
				if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
				putimage(0, 0, &CHMODEBK);
				//GameMode pre_gmmode_inrace = GAMEMODE;

				//�ı�����λ��
				difhp5btn.setxy(665, 200);
				difhp3btn.setxy(665, 370);
				difhp1btn.setxy(665, 540);
				diftime8btn.setxy(315, 200);
				diftime5btn.setxy(315, 370);
				diftime3btn.setxy(315, 540);

				//���ð�ť���ı�����
				putnowmode();
				difhp5btn.putmenu();
				difhp3btn.putmenu();
				difhp1btn.putmenu();
				diftime3btn.putmenu();
				diftime5btn.putmenu();
				diftime8btn.putmenu();
				rechmodebtn.putmenu();

				while (CHOOSE_GAMEMODE_NEXT) {
					DWORD starttime_chmode_next = GetTickCount();

					while (peekmessage(&msg)) {
						rechmodebtn.checkstatus(msg);
						difhp5btn.checkstatus(msg);
						difhp3btn.checkstatus(msg);
						diftime3btn.checkstatus(msg);
						diftime5btn.checkstatus(msg);
						diftime8btn.checkstatus(msg);
						difhp1btn.checkstatus(msg);

						if (DIFFICULTY_TIME != pre_difficulty_time || DIFFICULTY_HP != pre_difficulty_hp) {
							putnowmode();
							pre_difficulty_time = DIFFICULTY_TIME;
							pre_difficulty_hp = DIFFICULTY_HP;
						}
						rechmodebtn.putmenu();
						diftime3btn.putmenu();
						diftime5btn.putmenu();
						diftime8btn.putmenu();
						difhp5btn.putmenu();
						difhp3btn.putmenu();
						difhp1btn.putmenu();
					}
					FlushBatchDraw();
					DWORD endtime_chmode_next = GetTickCount();
					DWORD process_chmode_next = endtime_chmode_next - starttime_chmode_next;
					if (process_chmode_next < 1000 / 60) {
						Sleep(1000 / 60 - process_chmode_next);
					}
				}
			}

			FlushBatchDraw();
			DWORD endtime_chmode = GetTickCount();
			DWORD process_chmode = endtime_chmode - starttime_chmode;
			if (process_chmode < 1000 / 60) {
				Sleep(1000 / 60 - process_chmode);
			}
		}

		//��Ϸ��ʼ
		while (gamestart) {
			DWORD starttime_game = GetTickCount();

			cleardevice();
			putimage(0, 0, &OTBACKGROUND);
			int score = 0, pre_score = 1;							//��ҵ÷�
			bool have_clicked = false;				//����Ƿ������е�ĳ����ť
			
			wstring game_time_now;					//ʣ��ʱ���ı�
			wstring score_now;						//��ǰ�÷�
			RECT game_time_now_rect = { 950,125,1000,175 };						//ʣ��ʱ��������������
			RECT replace_time_rect = { 900,45+12,1250,45 + 212 };				//��Ϣ�����ı�λ��		����Ҫ
			RECT replace_score_now_rect = { 220,100,220 + 206,100 + 140 };		//��ǰ���������ı�����
			RECT score_now_rect = { 300,125,350,175 };							//��ǰ����������������
			RECT INF_FIRSTHALF = { 900,57+10,1250,157 };						//��Ϣ���ϰ벿��
			RECT INF_SECONDHALF = { 900,157,1250,257-10 };						//��Ϣ���°벿��
			RECT INF_TOP = { 900,57 + 10,1250,67 + 60 };						//��Ϣ��������������������Ϊ�����Լ�����ģʽ����
			RECT INF_MIDDLE = { 900,67 + 60,1250,67 + 120 };					//��Ϣ���в�
			RECT INF_BOTTOM = { 900,67 + 120,1250,67 + 180 };					//��Ϣ���ײ�
			remenubtn.putmenu();

			//���ֵ���ʱ
			//лл������
			IMAGE countdown[3];
			loadimage(&countdown[0], _T("images/countdown/countdown1.png"));
			loadimage(&countdown[1], _T("images/countdown/countdown2.png"));
			loadimage(&countdown[2], _T("images/countdown/countdown3.png"));
			DWORD count_start_time = GetTickCount();
			while (COUNTDOWN) {
				DWORD starttime_count = GetTickCount();

				//���á���ⷵ�ز˵���ť
				while (peekmessage(&msg)) {
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();
				}
				
				//���õ���ʱ
				DWORD count_now_time = GetTickCount();
				if (count_now_time - count_start_time > 3000)COUNTDOWN = false;
				int nowcount = 3 - (count_now_time - count_start_time)/1000.0;
				Putimage(490, 210, &countdown[nowcount]);

				FlushBatchDraw();
				DWORD endtime_count = GetTickCount();
				DWORD process_count = endtime_count - starttime_count;
				if (process_count < 1000 / 60) {
					Sleep(1000 / 60 - process_count);
				}
			}
			cleardevice();
			putimage(0, 0, &OTBACKGROUND);
			resetbuttons();
			putplayers();

			//����ģʽ
			if (GAMEMODE == race) {
				DWORD this_game_start = GetTickCount();	//�˾���Ϸ�Ŀ�ʼʱ��
				while (this_game) {
					DWORD starttime_thisgame = GetTickCount();

					//����Ƿ����ص����˵���ť
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();
					while (peekmessage(&msg)) {

						//����Ƿ����ص����˵���ť
						remenubtn.checkstatus(msg);
						remenubtn.putmenu();

						//����Ƿ�����ĳ����Ұ�ť�����Ƿ�÷�
						if (!have_clicked && player1.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player1))pre_score = score, score++;
						}
						else if (!have_clicked && player2.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player2))pre_score = score, score++;
						}
						else if (!have_clicked && player3.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player3))pre_score = score, score++;
						}
						else if (!have_clicked && player4.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player4))pre_score = score, score++;
						}
						else if (!have_clicked && player5.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player5))pre_score = score, score++;
						}
						else if (!have_clicked && player6.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player6))pre_score = score, score++;
						}
						else if (!have_clicked && player7.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player7))pre_score = score, score++;
						}
						else if (!have_clicked && player8.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player8))pre_score = score, score++;
						}
					}

					//����Ƿ��Ѿ���������ĳ����ť
					if (have_clicked) {
						resetbuttons();
						putplayers();
						have_clicked = false;
					}

					//���ʱ���Ƿ��ޣ�������˾���Ϸ����
					DWORD this_game_now = GetTickCount();
					if (this_game_now - this_game_start > DIFFICULTY_TIME*1000) this_game = false, CLEAR_MENU_RUNNING = true;

					//����ʣ��ʱ���ı�
					std::wstringstream wss; // ����һ�����ַ���������
					int elapsedTime = ceil(DIFFICULTY_TIME - (this_game_now - this_game_start) / 1000.0); // ���㾭����ʱ��
					// ���þ��Ȳ������ʽ�����ַ���
					if (elapsedTime >= 10)wss << L"ʣ��ʱ��Ϊ��" << std::fixed << std::setprecision(2) << elapsedTime;
					else wss << L"ʣ��ʱ��Ϊ�� " << std::fixed << std::setprecision(2) << elapsedTime;
					// ���ַ������л�ȡ��ʽ������ַ���������ֵ�� wstring ����
					game_time_now = wss.str();

					//����÷�
					std::wstringstream wss2; // ����һ�����ַ���������
					// ���þ��Ȳ������ʽ�����ַ���
					wss2 << L"��ǰ�÷֣�" << std::fixed << score;
					// ���ַ������л�ȡ��ʽ������ַ���������ֵ�� wstring ����
					score_now = wss2.str();

					//����ʣ��ʱ���ı�
					if (this_game_now - this_game_start <= ceil(DIFFICULTY_TIME/4.0*3000))settextcolor(YELLOW);
					else settextcolor(RED);
					//setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("��������"));
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					drawtext(game_time_now.c_str(), &INF_FIRSTHALF, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//���õ÷�
					if (score < 15)settextcolor(GREEN);
					else if (score < 25)settextcolor(BLUE);
					else settextcolor(YELLOW);
					//setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("��������"));
					drawtext(score_now.c_str(), &INF_SECONDHALF, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					FlushBatchDraw();
					DWORD endtime_thisgame = GetTickCount();
					DWORD process_thisgame = endtime_thisgame - starttime_thisgame;
					if (process_thisgame < 1000 / 60) {
						Sleep(1000 / 60 - process_thisgame);
					}
				}
			}

			//����ģʽ
			else if (GAMEMODE == limit) {
				DWORD this_game_start = GetTickCount();	//�˾���Ϸ�Ŀ�ʼʱ��

				DWORD nowlimit_time = GetTickCount();
				wstring limit_time_now_text;

				double nowpenalty = 0;
				pre_score = score;

				while (this_game) {
					DWORD starttime_thisgame = GetTickCount();

					//����Ƿ����ص����˵���ť
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();

					while (peekmessage(&msg)) {

						//����Ƿ����ص����˵���ť
						remenubtn.checkstatus(msg);
						remenubtn.putmenu();

						//����Ƿ�����ĳ����Ұ�ť�����Ƿ�÷�
						if (!have_clicked && player1.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player1))pre_score = score, score++;
							else nowpenalty += PENALTY;
						}
						if (!have_clicked && player2.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player2))pre_score = score, score++;
							else nowpenalty += PENALTY;
						}
						if (!have_clicked && player3.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player3))pre_score = score, score++;
							else nowpenalty += PENALTY;
						}
						if (!have_clicked && player4.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player4))pre_score = score, score++;
							else nowpenalty += PENALTY;
						}
						if (!have_clicked && player5.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player5))pre_score = score, score++;
							else nowpenalty += PENALTY;
						}
						if (!have_clicked && player6.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player6))pre_score = score, score++;
							else nowpenalty += PENALTY;
						}
						if (!have_clicked && player7.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player7))pre_score = score, score++;
							else nowpenalty += PENALTY;
						}
						if (!have_clicked && player8.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player8))pre_score = score, score++;
							else nowpenalty += PENALTY;
						}
					}

					//���ʱ���Ƿ��ޣ�������˾���Ϸ����
					DWORD this_game_now = GetTickCount();
					if (this_game_now - this_game_start > (DIFFICULTY_TIME_ALL - nowpenalty) * 1000) this_game = false, CLEAR_MENU_RUNNING = true;
					if (!have_clicked && this_game_now - nowlimit_time > DIFFICULTY_TIME * 1000)this_game = false, CLEAR_MENU_RUNNING = true;

					//�����ܹ�ʣ��ʱ���ı�
					std::wstringstream wss; // ����һ�����ַ���������
					int elapsedTime = ceil(DIFFICULTY_TIME_ALL - nowpenalty - (this_game_now - this_game_start) / 1000.0); // ���㾭����ʱ��
					if (elapsedTime >= 10)wss << L"��ʣ��ʱ��Ϊ��" << std::fixed << std::setprecision(2) << elapsedTime;// ���þ��Ȳ������ʽ�����ַ���
					else wss << L"��ʣ��ʱ��Ϊ�� " << std::fixed << std::setprecision(2) << elapsedTime;
					game_time_now = wss.str();// ���ַ������л�ȡ��ʽ������ַ���������ֵ�� wstring ����

					//��������ʣ��ʱ���ı�
					std::wstringstream wss1;
					int elapsedTime1 = ceil(DIFFICULTY_TIME - (this_game_now - nowlimit_time) / 1000.0);
					wss1 << L"����ʣ��ʱ��Ϊ��" << std::fixed << std::setprecision(2) << elapsedTime1;
					limit_time_now_text = wss1.str();

					//����÷�
					std::wstringstream wss2;
					wss2 << L"��ǰ�÷֣�" << std::fixed << score;
					score_now = wss2.str();

					//����ʣ��ʱ���ı�
					if (this_game_now - this_game_start < ceil(DIFFICULTY_TIME_ALL / 4.0 * 3000))settextcolor(YELLOW);
					else settextcolor(RED);
					//setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("��������"));
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					drawtext(game_time_now.c_str(), &INF_TOP, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//���õ���ʣ��ʱ���ı�
					settextcolor(RED);
					drawtext(limit_time_now_text.c_str(), &INF_MIDDLE, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//���õ÷�
					if (score < 15)settextcolor(GREEN);
					else if (score < 25)settextcolor(BLUE);
					else settextcolor(YELLOW);
					drawtext(score_now.c_str(), &INF_BOTTOM, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					//����Ƿ��Ѿ���������ĳ����ť
					if (have_clicked) {
						resetbuttons();
						putplayers();
						nowlimit_time = GetTickCount();
						have_clicked = false;
					}

					FlushBatchDraw();
					DWORD endtime_thisgame = GetTickCount();
					DWORD process_thisgame = endtime_thisgame - starttime_thisgame;
					if (process_thisgame < 1000 / 60) {
						Sleep(1000 / 60 - process_thisgame);
					}
				}
			}

			//����ģʽ��������Ҫ��Ҫ������ʱ�������������˱�ʳ�Ȼ���24.12.24
			else if (GAMEMODE == survival) {
				DWORD this_game_start = GetTickCount();	//�˾���Ϸ�Ŀ�ʼʱ��
				int nowhp = DIFFICULTY_HP;

				DWORD start_fullness = GetTickCount();	//�������㱥ʳ��
				int awardfullness = 0;	//���ӵı�ʳ��
				wstring drawfullness;	//����õı�ʳ��

				//���ú���
				IMAGE HP;
				loadimage(&HP, _T("images/HP.png"));

				//������������ͷλ��		RECT INF_FIRSTHALF = { 900,57+10,1250,157 };x350 y90   54*50
				// RECT INF_TOP = { 900,57 + 10,1250,67 + 60 };
				int hplocx,hplocy=10+67;
				int tmphp = nowhp;
				if (DIFFICULTY_HP == 1)hplocx = 148+900;
				else if (DIFFICULTY_HP == 3)hplocx = 900+(350 - 54 * 3 - 5 * 2) / 2;
				else hplocx = 900+(350 - 54 * 5 - 5 * 4) / 2;

				while (this_game) {
					DWORD starttime_thisgame = GetTickCount();

					//����Ƿ����ص����˵���ť
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();
					while (peekmessage(&msg)) {

						//����Ƿ����ص����˵���ť
						remenubtn.checkstatus(msg);
						remenubtn.putmenu();

						//����Ƿ�����ĳ����Ұ�ť�����Ƿ�÷�
						if (!have_clicked && player1.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player1))score++, awardfullness += 3;
							else nowhp--;
						}
						if (!have_clicked && player2.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player2))score++, awardfullness += 3;
							else nowhp--;
						}
						if (!have_clicked && player3.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player3))score++, awardfullness += 3;
							else nowhp--;
						}
						if (!have_clicked && player4.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player4))score++, awardfullness += 3;
							else nowhp--;
						}
						if (!have_clicked && player5.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player5))score++, awardfullness += 3;
							else nowhp--;
						}
						if (!have_clicked && player6.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player6))score++, awardfullness += 3;
							else nowhp--;
						}
						if (!have_clicked && player7.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player7))score++, awardfullness += 3;
							else nowhp--;
						}
						if (!have_clicked && player8.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player8))score++, awardfullness += 3;
							else nowhp--;
						}
					}

					//����Ƿ��Ѿ���������ĳ����ť
					if (have_clicked) {
						resetbuttons();
						putplayers();
						have_clicked = false;
					}

					//��ʳ�Ȳ��㣬��һ����
					DWORD nowfullness = GetTickCount();
					if ((FULLNESS + awardfullness) * 1000.0 - nowfullness + start_fullness > 60 * 1000.0)awardfullness = floor((60 * 1000.0 - start_fullness + nowfullness)) / 1000.0 - FULLNESS;
					if (nowfullness - start_fullness >= (FULLNESS + awardfullness) * 1000.0) {
						awardfullness += FULLNESS;
						nowhp--;
					}

					//���ʣ������������Ϊ0��˾���Ϸ����
					//DWORD this_game_now = GetTickCount();
					if (nowhp <= 0) this_game = false, CLEAR_MENU_RUNNING = true;

					//���㱥ʳ��
					std::wstringstream wss; // ����һ�����ַ���������
					int elapsedTime = ceil(FULLNESS + awardfullness - (nowfullness - start_fullness) / 1000.0); // ���㾭����ʱ��
					// ���þ��Ȳ������ʽ�����ַ���
					if (elapsedTime >= 10)wss << L"ʣ�౥ʳ�ȣ�" << std::fixed << std::setprecision(2) << elapsedTime;
					else wss << L"ʣ�౥ʳ�ȣ� " << std::fixed << std::setprecision(2) << elapsedTime;
					// ���ַ������л�ȡ��ʽ������ַ���������ֵ�� wstring ����
					drawfullness = wss.str();

					//����÷�
					std::wstringstream wss2; // ����һ�����ַ���������
					// ���þ��Ȳ������ʽ�����ַ���
					wss2 << L"��ǰ�÷֣�" << std::fixed << score;
					// ���ַ������л�ȡ��ʽ������ַ���������ֵ�� wstring ����
					score_now = wss2.str();

					//���ñ�ʳ��
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					if ((FULLNESS + awardfullness) * 1000.0 - nowfullness + start_fullness > 5*1000.0)settextcolor(YELLOW);
					else settextcolor(RED);
					setbkmode(TRANSPARENT);
					settextstyle(35, 0, _T("��������"));
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					drawtext(drawfullness.c_str(), &INF_MIDDLE, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					//����ʣ������
					int tmploc = hplocx;
					for (int i = 1; i <= nowhp; i++) {
						Putimage(tmploc, hplocy, &HP);
						tmploc += 54 + 5;
					}

					//���õ÷�
					if (score < 25)settextcolor(GREEN);
					else if (score < 35)settextcolor(BLUE);
					else settextcolor(YELLOW);
					//setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("��������"));
					drawtext(score_now.c_str(), &INF_BOTTOM, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					FlushBatchDraw();
					DWORD endtime_thisgame = GetTickCount();
					DWORD process_thisgame = endtime_thisgame - starttime_thisgame;
					if (process_thisgame < 1000 / 60) {
						Sleep(1000 / 60 - process_thisgame);
					}
				}
			}

			//����ģʽ
			else if (GAMEMODE == hell) {
				DWORD this_game_start = GetTickCount();	//�˾���Ϸ�Ŀ�ʼʱ��

				DWORD nowlimit_time = GetTickCount();
				wstring limit_time_now_text;

				pre_score = score;

				int nowhp = DIFFICULTY_HP;

				//���ú���
				IMAGE HP;
				loadimage(&HP, _T("images/HP.png"));

				//������������ͷλ��		RECT INF_FIRSTHALF = { 900,57+10,1250,157 };x350 y90   54*50
				int hplocx, hplocy = 67;
				int tmphp = nowhp;
				if (DIFFICULTY_HP == 1)hplocx = 148 + 900;
				else if (DIFFICULTY_HP == 3)hplocx = 900 + (350 - 54 * 3 - 5 * 2) / 2;
				else hplocx = 900 + (350 - 54 * 5 - 5 * 4) / 2;

				while (this_game) {
					DWORD starttime_thisgame = GetTickCount();

					//����Ƿ����ص����˵���ť
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();

					while (peekmessage(&msg)) {

						//����Ƿ����ص����˵���ť
						remenubtn.checkstatus(msg);
						remenubtn.putmenu();

						//����Ƿ�����ĳ����Ұ�ť�����Ƿ�÷�
						if (!have_clicked && player1.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player1))score++;
							else nowhp--;
						}
						if (!have_clicked && player2.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player2))score++;
							else nowhp--;
						}
						if (!have_clicked && player3.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player3))score++;
							else nowhp--;
						}
						if (!have_clicked && player4.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player4))score++;
							else nowhp--;
						}
						if (!have_clicked && player5.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player5))score++;
							else nowhp--;
						}
						if (!have_clicked && player6.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player6))score++;
							else nowhp--;
						}
						if (!have_clicked && player7.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player7))score++;
							else nowhp--;
						}
						if (!have_clicked && player8.checkclick(msg)) {
							have_clicked = true;
							if (question.checkscore(player8))score++;
							else nowhp--;
						}
					}

					//���ʱ���Ƿ��ޣ�������˾���Ϸ����
					DWORD this_game_now = GetTickCount();
					if (!have_clicked && this_game_now - nowlimit_time > DIFFICULTY_TIME * 1000)this_game = false, CLEAR_MENU_RUNNING = true;

					//���ʣ������������Ϊ0��˾���Ϸ����
					if (nowhp == 0) this_game = false, CLEAR_MENU_RUNNING = true;

					//��������ʣ��ʱ���ı�
					std::wstringstream wss1;
					int elapsedTime1 = ceil(DIFFICULTY_TIME - (this_game_now - nowlimit_time) / 1000.0);
					wss1 << L"����ʣ��ʱ��Ϊ��" << std::fixed << std::setprecision(2) << elapsedTime1;
					limit_time_now_text = wss1.str();

					//����÷�
					std::wstringstream wss2;
					wss2 << L"��ǰ�÷֣�" << std::fixed << score;
					score_now = wss2.str();

					//���õ���ʣ��ʱ���ı�
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					settextstyle(40, 0, _T("��������"));
					//setbkmode(TRANSPARENT);
					settextcolor(RED);
					drawtext(limit_time_now_text.c_str(), &INF_MIDDLE, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//���õ÷�
					if (score < 15)settextcolor(GREEN);
					else if (score < 25)settextcolor(BLUE);
					else settextcolor(YELLOW);
					drawtext(score_now.c_str(), &INF_BOTTOM, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//����ʣ������
					int tmploc = hplocx;
					for (int i = 1; i <= nowhp; i++) {
						Putimage(tmploc, hplocy, &HP);
						tmploc += 54 + 5;
					}

					//����Ƿ��Ѿ���������ĳ����ť
					if (have_clicked) {
						resetbuttons();
						putplayers();
						nowlimit_time = GetTickCount();
						have_clicked = false;
					}

					FlushBatchDraw();
					DWORD endtime_thisgame = GetTickCount();
					DWORD process_thisgame = endtime_thisgame - starttime_thisgame;
					if (process_thisgame < 1000 / 60) {
						Sleep(1000 / 60 - process_thisgame);
					}
				}
			}

			//�������
			int setclearmenu = true;
			GameMode clearmenumode = GAMEMODE;
			while (CLEAR_MENU_RUNNING) {
				DWORD starttime_clearmenu = GetTickCount();

				//���ý���ҳ��
				if (setclearmenu) {
					//����˵�
					cleardevice();
					putimage(0, 0, &OTBACKGROUND);
					Putimage(398, 75, &CLEARMENUBK);
					wstring gameover = _T("��Ϸ����"), score_final;	//��Ϸ�����ı������յ÷��ı�
					RECT gameover_rect = { 590,100,690,150 };
					RECT gamemode_final_rect = { 590,150+10,690,200+10 };
					RECT score_final_rect = { 590,200+20,690,250+20 };
					std::wstringstream wss; // ����һ�����ַ���������
					// ���þ��Ȳ������ʽ�����ַ���
					wss << L"���յ÷֣�" << std::fixed << score;
					// ���ַ������л�ȡ��ʽ������ַ���������ֵ�� wstring ����
					score_final = wss.str();
					settextcolor(MAGENTA);
					//setbkmode(TRANSPARENT);
					settextstyle(50, 0, _T("��������"));
					drawtext(gameover.c_str(), &gameover_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					drawtext(score_final.c_str(), &score_final_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					wstring clearmenumode_text=_T("");

					switch (clearmenumode) {
					case race: {
						clearmenumode_text += _T("����ģʽ");
						if (DIFFICULTY_TIME == 15)clearmenumode_text += _T(" - 15��");
						else if (DIFFICULTY_TIME == 30)clearmenumode_text += _T(" - 30��");
						else clearmenumode_text += _T(" - 60��");
						break;
					}
					case survival: {
						clearmenumode_text += _T("����ģʽ");
						if (DIFFICULTY_HP == 5)clearmenumode_text += _T(" - 5����ֵ");
						else if (DIFFICULTY_HP == 3)clearmenumode_text += _T(" - 3����ֵ");
						else clearmenumode_text += _T(" - 1����ֵ");
						break;
					}
					case limit: {
						clearmenumode_text += _T("����ģʽ");
						if (DIFFICULTY_TIME == 5)clearmenumode_text += _T(" - 5��");
						else if (DIFFICULTY_TIME == 3)clearmenumode_text += _T(" - 3��");
						else clearmenumode_text += _T(" - 8��");
						break;
					}
					case hell: {
						clearmenumode_text += _T("����ģʽ");
						if (DIFFICULTY_TIME == 5)clearmenumode_text += _T(" - 5��");
						else if (DIFFICULTY_TIME == 3)clearmenumode_text += _T(" - 3��");
						else clearmenumode_text += _T(" - 8��");
						if (DIFFICULTY_HP == 5)clearmenumode_text += _T(" - 5����ֵ");
						else if (DIFFICULTY_HP == 3)clearmenumode_text += _T(" - 3����ֵ");
						else clearmenumode_text += _T(" - 1����ֵ");
						break;
					}
					}
					settextcolor(YELLOW);
					setbkmode(TRANSPARENT);
					if (clearmenumode != hell)settextstyle(50, 0, _T("��������"));
					else settextstyle(40, 0, _T("��������"));
					drawtext(clearmenumode_text.c_str(), &gamemode_final_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					remenubtn_clear.putmenu();
					restartbtn.putmenu();
					chmodebtn_clearmenu.putmenu();
					setclearmenu = false;
				}
				

				while (peekmessage(&msg)) {
					//����ؿ���ť�ͷ������˵���ť
					restartbtn.checkstatus(msg);
					chmodebtn_clearmenu.checkstatus(msg);
					remenubtn_clear.checkstatus(msg);

					chmodebtn_clearmenu.putmenu();
					remenubtn_clear.putmenu();
					restartbtn.putmenu();
				}
				
				if (CHOOSE_GAMEMODE) {
					choosemode_clearmenu();
					setclearmenu = true;
				}

				FlushBatchDraw();
				DWORD endtime_clearmenu = GetTickCount();
				DWORD process_clearmenu = endtime_clearmenu - starttime_clearmenu;
				if (process_clearmenu < 1000 / 60) {
					Sleep(1000 / 60 - process_clearmenu);
				}
			}
		}

		
		DWORD endtime = GetTickCount();
		DWORD process = endtime - starttime;
		if (process < 1000 / 60) {
			Sleep(1000 / 60 - process);
		}
	}

	EndBatchDraw();
	return 0;
}

//��������ѡ��ģʽ
inline void choosemode_clearmenu() {
	ExMessage msg;
	bool chmode_clear = true;

	ReturnUplevButton reupbtn(remenu_bkwait, remenu_bkhold, remenu_bkpushed, remenu_bkrect, x_remenu_bkrect, y_remenu_bkrect);
	reupbtn.setlevel(&CLEAR_MENU_RUNNING, &chmode_clear, &CHOOSE_GAMEMODE_INIT, &CHOOSE_GAMEMODE);
	
	while (chmode_clear) {
		cleardevice();
		putimage(0, 0, &CHMODEBK);
		DWORD starttime_chmode = GetTickCount();
		//wstring pre_nowmode = nowmode;
		GameMode pre_gmmode = GAMEMODE;
		int pre_difficulty_time = DIFFICULTY_TIME;
		int pre_difficulty_hp = DIFFICULTY_HP;

		putnowmode();
		reupbtn.putmenu();
		race_modebtn.putmenu();
		survival_modebtn.putmenu();
		limit_modebtn.putmenu();
		hell_modebtn.putmenu();

		//��ʼģʽѡ�����
		while (CHOOSE_GAMEMODE_INIT) {
			DWORD starttime_chmode_init = GetTickCount();

			reupbtn.putmenu();
			race_modebtn.putmenu();
			survival_modebtn.putmenu();
			limit_modebtn.putmenu();
			hell_modebtn.putmenu();

			while (peekmessage(&msg)) {

				reupbtn.checkstatus(msg);
				race_modebtn.checkstatus(msg);
				survival_modebtn.checkstatus(msg);
				limit_modebtn.checkstatus(msg);
				hell_modebtn.checkstatus(msg);

				if (GAMEMODE != pre_gmmode) {
					putnowmode();
					pre_gmmode = GAMEMODE;
				}
				reupbtn.putmenu();
				race_modebtn.putmenu();
				survival_modebtn.putmenu();
				limit_modebtn.putmenu();
				hell_modebtn.putmenu();

			}

			FlushBatchDraw();
			DWORD endtime_chmode_init = GetTickCount();
			DWORD process_chmode_init = endtime_chmode_init - starttime_chmode_init;
			if (process_chmode_init < 1000 / 60) {
				Sleep(1000 / 60 - process_chmode_init);
			}
		}

		//������ҳ��
		if (chmode_clear==false)return;

		//��Ϸģʽ��race���涨ʱ���ڱ�ƴ��ȷ���� survival��������������һ���������� limit�����Ƶ�����Ŀ��ʱ�䣻 hell���������������Ƶ�����Ŀʱ��
			//���ѡ�����race
		if (GAMEMODE == race) {
			cleardevice();
			putimage(0, 0, &CHMODEBK);
			if (DIFFICULTY_TIME < 15)DIFFICULTY_TIME = 60;
			//GameMode pre_gmmode_inrace = GAMEMODE;

			//�ı�����λ��
			diftime30btn.setxy(490, 370);
			diftime60btn.setxy(490, 200);
			diftime15btn.setxy(490, 540);

			//���ð�ť���ı�����
			putnowmode();
			diftime30btn.putmenu();
			diftime60btn.putmenu();
			diftime15btn.putmenu();
			rechmodebtn.putmenu();

			while (CHOOSE_GAMEMODE_NEXT) {
				DWORD starttime_chmode_race = GetTickCount();

				while (peekmessage(&msg)) {
					rechmodebtn.checkstatus(msg);
					diftime30btn.checkstatus(msg);
					diftime60btn.checkstatus(msg);
					diftime15btn.checkstatus(msg);

					if (DIFFICULTY_TIME != pre_difficulty_time || DIFFICULTY_HP != pre_difficulty_hp) {
						putnowmode();
						pre_difficulty_time = DIFFICULTY_TIME;
						pre_difficulty_hp = DIFFICULTY_HP;
					}
					rechmodebtn.putmenu();
					diftime30btn.putmenu();
					diftime60btn.putmenu();
					diftime15btn.putmenu();
				}

				FlushBatchDraw();
				DWORD endtime_chmode_race = GetTickCount();
				DWORD process_chmode_race = endtime_chmode_race - starttime_chmode_race;
				if (process_chmode_race < 1000 / 60) {
					Sleep(1000 / 60 - process_chmode_race);
				}
			}
		}

		//���ѡ������ģʽ
		else if (GAMEMODE == survival) {
			cleardevice();
			//if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
			putimage(0, 0, &CHMODEBK);
			//GameMode pre_gmmode_inrace = GAMEMODE;

			//�ı�����λ��
			difhp5btn.setxy(490, 200);
			difhp3btn.setxy(490, 370);
			difhp1btn.setxy(490, 540);

			//���ð�ť���ı�����
			putnowmode();
			difhp5btn.putmenu();
			difhp3btn.putmenu();
			difhp1btn.putmenu();
			rechmodebtn.putmenu();

			while (CHOOSE_GAMEMODE_NEXT) {
				DWORD starttime_chmode_next = GetTickCount();

				while (peekmessage(&msg)) {
					rechmodebtn.checkstatus(msg);
					difhp5btn.checkstatus(msg);
					difhp3btn.checkstatus(msg);
					difhp1btn.checkstatus(msg);

					if (DIFFICULTY_TIME != pre_difficulty_time || DIFFICULTY_HP != pre_difficulty_hp) {
						putnowmode();
						pre_difficulty_time = DIFFICULTY_TIME;
						pre_difficulty_hp = DIFFICULTY_HP;
					}
					rechmodebtn.putmenu();
					difhp5btn.putmenu();
					difhp3btn.putmenu();
					difhp1btn.putmenu();
				}

				FlushBatchDraw();
				DWORD endtime_chmode_next = GetTickCount();
				DWORD process_chmode_next = endtime_chmode_next - starttime_chmode_next;
				if (process_chmode_next < 1000 / 60) {
					Sleep(1000 / 60 - process_chmode_next);
				}
			}
		}

		//ѡ����ģʽ��
		else if (GAMEMODE == limit) {
			cleardevice();
			if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
			putimage(0, 0, &CHMODEBK);
			//GameMode pre_gmmode_inrace = GAMEMODE;

			//�ı�����λ��
			diftime8btn.setxy(490, 200);
			diftime5btn.setxy(490, 370);
			diftime3btn.setxy(490, 540);

			//���ð�ť���ı�����
			putnowmode();
			diftime3btn.putmenu();
			diftime5btn.putmenu();
			diftime8btn.putmenu();
			rechmodebtn.putmenu();

			while (CHOOSE_GAMEMODE_NEXT) {
				DWORD starttime_chmode_next = GetTickCount();

				while (peekmessage(&msg)) {
					rechmodebtn.checkstatus(msg);
					diftime3btn.checkstatus(msg);
					diftime5btn.checkstatus(msg);
					diftime8btn.checkstatus(msg);

					if (DIFFICULTY_TIME != pre_difficulty_time || DIFFICULTY_HP != pre_difficulty_hp) {
						putnowmode();
						pre_difficulty_time = DIFFICULTY_TIME;
						pre_difficulty_hp = DIFFICULTY_HP;
					}
					rechmodebtn.putmenu();
					diftime3btn.putmenu();
					diftime5btn.putmenu();
					diftime8btn.putmenu();
				}

				FlushBatchDraw();
				DWORD endtime_chmode_next = GetTickCount();
				DWORD process_chmode_next = endtime_chmode_next - starttime_chmode_next;
				if (process_chmode_next < 1000 / 60) {
					Sleep(1000 / 60 - process_chmode_next);
				}
			}
		}

		//ѡ�����ģʽ��
		else if (GAMEMODE == hell) {
			cleardevice();
			if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
			putimage(0, 0, &CHMODEBK);
			//GameMode pre_gmmode_inrace = GAMEMODE;

			//�ı�����λ��
			difhp5btn.setxy(665, 200);
			difhp3btn.setxy(665, 370);
			difhp1btn.setxy(665, 540);
			diftime8btn.setxy(315, 200);
			diftime5btn.setxy(315, 370);
			diftime3btn.setxy(315, 540);

			//���ð�ť���ı�����
			putnowmode();
			difhp5btn.putmenu();
			difhp3btn.putmenu();
			difhp1btn.putmenu();
			diftime3btn.putmenu();
			diftime5btn.putmenu();
			diftime8btn.putmenu();
			rechmodebtn.putmenu();

			while (CHOOSE_GAMEMODE_NEXT) {
				DWORD starttime_chmode_next = GetTickCount();

				while (peekmessage(&msg)) {
					rechmodebtn.checkstatus(msg);
					difhp5btn.checkstatus(msg);
					difhp3btn.checkstatus(msg);
					diftime3btn.checkstatus(msg);
					diftime5btn.checkstatus(msg);
					diftime8btn.checkstatus(msg);
					difhp1btn.checkstatus(msg);

					if (DIFFICULTY_TIME != pre_difficulty_time || DIFFICULTY_HP != pre_difficulty_hp) {
						putnowmode();
						pre_difficulty_time = DIFFICULTY_TIME;
						pre_difficulty_hp = DIFFICULTY_HP;
					}
					rechmodebtn.putmenu();
					diftime3btn.putmenu();
					diftime5btn.putmenu();
					diftime8btn.putmenu();
					difhp5btn.putmenu();
					difhp3btn.putmenu();
					difhp1btn.putmenu();
				}
				FlushBatchDraw();
				DWORD endtime_chmode_next = GetTickCount();
				DWORD process_chmode_next = endtime_chmode_next - starttime_chmode_next;
				if (process_chmode_next < 1000 / 60) {
					Sleep(1000 / 60 - process_chmode_next);
				}
			}
		}

		FlushBatchDraw();
		DWORD endtime_chmode = GetTickCount();
		DWORD process_chmode = endtime_chmode - starttime_chmode;
		if (process_chmode < 1000 / 60) {
			Sleep(1000 / 60 - process_chmode);
		}
	}

	return;
}

//�Ժ�����̽����
inline void putpa() {
	putimage(440, 90, &PA);
	putimage(335, 90 + 400 + 5, &LATER);
}