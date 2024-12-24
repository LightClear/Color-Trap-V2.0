#include"MBUTTON.h"
#include"RuleInitSpace.h"
#include"initspace.h"
#include<ctime>
#include<cmath>
#include<graphics.h>
#include <sstream> // 包含标准库中的字符串流头文件
#include <iomanip> // 包含设置浮点数精度的头文件
using namespace init;
using namespace RuleInit;

//24.12.13日凌晨12点，基本上完成了Button的对象搭建
//24.12.14晚上22点，还要完成游戏主体逻辑的搭建，同时要完善endgame与clearmenu那里的逻辑关系，这两个有点重复了，考虑是否要加入暂停按钮
//24.12.21凌晨12点，完成了ui界面的更新，后续需要完成模式的选择部分的代码，以及游戏主体界面根据模式的改变，以及结算界面，关于作者界面（删除了排行榜），开始游戏前三秒倒数

//重新设置按钮的值
inline void resetbuttons() {
	int n = 0;
	int a[8][2] = {0};
	COLOR ass[8] = { black,green,yellow,red,brown,blue,purple,cyan };
	wstring s[8]= { { _T("黑色") } ,{ _T("绿色") } ,{ _T("黄色") } ,{ _T("红色") } ,
					{ _T("棕色") } ,{ _T("蓝色") } ,{ _T("紫色") }, { _T("青色") } };
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

//放置player类按钮
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

//放置当前模式文本
IMAGE CHMODEBK, CHMODE_REPLACE;
wstring nowmode = _T("当前模式为：");
IMAGE NOWMODE;
inline void putnowmode() {
	RECT nowmode_rect = { 0,0,1280,150 };
	nowmode = _T("当前模式为：");

	switch (GAMEMODE) {
	case race: {
		nowmode += _T("竞速模式");
		if (DIFFICULTY_TIME == 15)nowmode += _T(" - 15秒");
		else if (DIFFICULTY_TIME == 30)nowmode += _T(" - 30秒");
		else nowmode += _T(" - 60秒");
		break;
	}
	case survival: {
		nowmode += _T("生存模式");
		if (DIFFICULTY_HP == 5)nowmode += _T(" - 5生命值");
		else if (DIFFICULTY_HP == 3)nowmode += _T(" - 3生命值");
		else nowmode += _T(" - 1生命值");
		break;
	}
	case limit: {
		nowmode += _T("单限模式");
		if (DIFFICULTY_TIME == 5)nowmode += _T(" - 5秒");
		else if (DIFFICULTY_TIME == 3)nowmode += _T(" - 3秒");
		else nowmode += _T(" - 8秒");
		break;
	}
	case hell: {
		nowmode += _T("地狱模式");
		if (DIFFICULTY_TIME == 5)nowmode += _T(" - 5秒");
		else if (DIFFICULTY_TIME == 3)nowmode += _T(" - 3秒");
		else nowmode += _T(" - 8秒");
		if (DIFFICULTY_HP == 5)nowmode += _T(" - 5生命值");
		else if (DIFFICULTY_HP == 3)nowmode += _T(" - 3生命值");
		else nowmode += _T(" - 1生命值");
		break;
	}
	}
	settextcolor(YELLOW);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("华文琥珀"));
	//putimage(0, 0, &CHMODE_REPLACE);
	Putimage(210, 35, &NOWMODE);
	drawtext(nowmode.c_str(), &nowmode_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

inline void choosemode_clearmenu();

//以后再来探索吧
IMAGE PA;
IMAGE LATER;
inline void putpa();

int main() {
	//初始化窗口、按钮以及背景
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

	//派蒙爬
	loadimage(&PA, _T("images/PA.png"));
	loadimage(&LATER, _T("images/LATER.png"));

	//设置字体格式
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("华文琥珀"));

	//初始化模式界面图片
	loadimage(&CHMODEBK, _T("images/chmode/CHMODEBK.png"));
	loadimage(&CHMODE_REPLACE, _T("images/chmode/CHMODEBK_REPLACE.png"));

	//设置question以及player的文本类型
	question.settype(1);
	player1.settype(2);
	player2.settype(2);
	player3.settype(2);
	player4.settype(2);
	player5.settype(2);
	player6.settype(2);
	player7.settype(2);
	player8.settype(2);

	//初始化覆盖图片
	IMAGE REPLACE_TIME;
	IMAGE REPLACE_SCORE;
	loadimage(&REPLACE_TIME, _T("images/REPLACE_INF.png"));
	loadimage(&REPLACE_SCORE, _T("images/REPLACE_SCORE.png"));

	//初始化规则图片————因规则按钮的制作故废弃这里24.12.23
	/*IMAGE RULE_BK;
	loadimage(&RULE_BK, _T("images/RULE_BK.png"));
	resetbuttons();*/

	//初始化排行榜图片
	IMAGE RANKINGLIST_BK;
	loadimage(&RANKINGLIST_BK, _T("images/RANKINGLIST_BK.png"));

	//初始化规则按钮的值
	race_modebtn.setGamemode(race);
	survival_modebtn.setGamemode(survival);
	limit_modebtn.setGamemode(limit);
	hell_modebtn.setGamemode(hell);

	//初始化难度按钮的难度值
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

		//处于主菜单时
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
		
		//处于排行榜
		putimage(0, 0, &OTBACKGROUND);
		if (rank) {
			//putimage(0, 0, &RANKINGLIST_BK);	//用来放置排行榜的内容
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

		//处于成就界面
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

		//处于音乐界面
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

		//处于关于作者界面
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

		//处于游戏介绍
		putimage(0, 0, &OTBACKGROUND);
		if (rule) {
			//放置按钮
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

		//处于游戏模式选择
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

			//初始模式选择界面
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


			//游戏模式，race：规定时间内比拼正确数； survival：有生命数，错一个扣生命； limit：限制单次题目的时间； hell：有生命数，限制单次题目时间
			//如果选择的是race
			if (GAMEMODE == race) {
				putimage(0, 0, &CHMODEBK);
				if (DIFFICULTY_TIME < 15)DIFFICULTY_TIME = 60;
				//GameMode pre_gmmode_inrace = GAMEMODE;

				//改变坐标位置
				diftime30btn.setxy(490, 370);
				diftime60btn.setxy(490, 200);
				diftime15btn.setxy(490, 540);

				//放置按钮及文本内容
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

			//如果选择生存模式
			else if (GAMEMODE == survival) {
				//if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
				putimage(0, 0, &CHMODEBK);
				//GameMode pre_gmmode_inrace = GAMEMODE;

				//改变坐标位置
				difhp5btn.setxy(490, 200);
				difhp3btn.setxy(490, 370);
				difhp1btn.setxy(490, 540);

				//放置按钮及文本内容
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

			//选择单限模式后
			else if (GAMEMODE == limit) {
				if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
				putimage(0, 0, &CHMODEBK);
				//GameMode pre_gmmode_inrace = GAMEMODE;

				//改变坐标位置
				diftime8btn.setxy(490, 200);
				diftime5btn.setxy(490, 370);
				diftime3btn.setxy(490, 540);

				//放置按钮及文本内容
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

			//选择地狱模式后
			else if (GAMEMODE == hell) {
				if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
				putimage(0, 0, &CHMODEBK);
				//GameMode pre_gmmode_inrace = GAMEMODE;

				//改变坐标位置
				difhp5btn.setxy(665, 200);
				difhp3btn.setxy(665, 370);
				difhp1btn.setxy(665, 540);
				diftime8btn.setxy(315, 200);
				diftime5btn.setxy(315, 370);
				diftime3btn.setxy(315, 540);

				//放置按钮及文本内容
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

		//游戏开始
		while (gamestart) {
			DWORD starttime_game = GetTickCount();

			cleardevice();
			putimage(0, 0, &OTBACKGROUND);
			int score = 0, pre_score = 1;							//玩家得分
			bool have_clicked = false;				//检测是否按了其中的某个按钮
			
			wstring game_time_now;					//剩余时间文本
			wstring score_now;						//当前得分
			RECT game_time_now_rect = { 950,125,1000,175 };						//剩余时间文字所在区域
			RECT replace_time_rect = { 900,45+12,1250,45 + 212 };				//信息覆盖文本位置		最重要
			RECT replace_score_now_rect = { 220,100,220 + 206,100 + 140 };		//当前分数覆盖文本区域
			RECT score_now_rect = { 300,125,350,175 };							//当前分数文字所在区域
			RECT INF_FIRSTHALF = { 900,57+10,1250,157 };						//信息栏上半部分
			RECT INF_SECONDHALF = { 900,157,1250,257-10 };						//信息栏下半部分
			RECT INF_TOP = { 900,57 + 10,1250,67 + 60 };						//信息栏顶部————及以下为单限以及地狱模式中用
			RECT INF_MIDDLE = { 900,67 + 60,1250,67 + 120 };					//信息栏中部
			RECT INF_BOTTOM = { 900,67 + 120,1250,67 + 180 };					//信息栏底部
			remenubtn.putmenu();

			//开局倒计时
			//谢谢点赞喵
			IMAGE countdown[3];
			loadimage(&countdown[0], _T("images/countdown/countdown1.png"));
			loadimage(&countdown[1], _T("images/countdown/countdown2.png"));
			loadimage(&countdown[2], _T("images/countdown/countdown3.png"));
			DWORD count_start_time = GetTickCount();
			while (COUNTDOWN) {
				DWORD starttime_count = GetTickCount();

				//放置、检测返回菜单按钮
				while (peekmessage(&msg)) {
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();
				}
				
				//放置倒计时
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

			//竞速模式
			if (GAMEMODE == race) {
				DWORD this_game_start = GetTickCount();	//此局游戏的开始时间
				while (this_game) {
					DWORD starttime_thisgame = GetTickCount();

					//检测是否点击回到主菜单按钮
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();
					while (peekmessage(&msg)) {

						//检测是否点击回到主菜单按钮
						remenubtn.checkstatus(msg);
						remenubtn.putmenu();

						//检测是否点击了某个玩家按钮，且是否得分
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

					//检测是否已经按了其中某个按钮
					if (have_clicked) {
						resetbuttons();
						putplayers();
						have_clicked = false;
					}

					//检测时间是否超限，超限则此局游戏结束
					DWORD this_game_now = GetTickCount();
					if (this_game_now - this_game_start > DIFFICULTY_TIME*1000) this_game = false, CLEAR_MENU_RUNNING = true;

					//计算剩余时间文本
					std::wstringstream wss; // 创建一个宽字符串流对象
					int elapsedTime = ceil(DIFFICULTY_TIME - (this_game_now - this_game_start) / 1000.0); // 计算经过的时间
					// 设置精度并插入格式化的字符串
					if (elapsedTime >= 10)wss << L"剩余时间为：" << std::fixed << std::setprecision(2) << elapsedTime;
					else wss << L"剩余时间为： " << std::fixed << std::setprecision(2) << elapsedTime;
					// 从字符串流中获取格式化后的字符串，并赋值给 wstring 变量
					game_time_now = wss.str();

					//计算得分
					std::wstringstream wss2; // 创建一个宽字符串流对象
					// 设置精度并插入格式化的字符串
					wss2 << L"当前得分：" << std::fixed << score;
					// 从字符串流中获取格式化后的字符串，并赋值给 wstring 变量
					score_now = wss2.str();

					//放置剩余时间文本
					if (this_game_now - this_game_start <= ceil(DIFFICULTY_TIME/4.0*3000))settextcolor(YELLOW);
					else settextcolor(RED);
					//setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("华文琥珀"));
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					drawtext(game_time_now.c_str(), &INF_FIRSTHALF, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//放置得分
					if (score < 15)settextcolor(GREEN);
					else if (score < 25)settextcolor(BLUE);
					else settextcolor(YELLOW);
					//setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("华文琥珀"));
					drawtext(score_now.c_str(), &INF_SECONDHALF, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					FlushBatchDraw();
					DWORD endtime_thisgame = GetTickCount();
					DWORD process_thisgame = endtime_thisgame - starttime_thisgame;
					if (process_thisgame < 1000 / 60) {
						Sleep(1000 / 60 - process_thisgame);
					}
				}
			}

			//单限模式
			else if (GAMEMODE == limit) {
				DWORD this_game_start = GetTickCount();	//此局游戏的开始时间

				DWORD nowlimit_time = GetTickCount();
				wstring limit_time_now_text;

				double nowpenalty = 0;
				pre_score = score;

				while (this_game) {
					DWORD starttime_thisgame = GetTickCount();

					//检测是否点击回到主菜单按钮
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();

					while (peekmessage(&msg)) {

						//检测是否点击回到主菜单按钮
						remenubtn.checkstatus(msg);
						remenubtn.putmenu();

						//检测是否点击了某个玩家按钮，且是否得分
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

					//检测时间是否超限，超限则此局游戏结束
					DWORD this_game_now = GetTickCount();
					if (this_game_now - this_game_start > (DIFFICULTY_TIME_ALL - nowpenalty) * 1000) this_game = false, CLEAR_MENU_RUNNING = true;
					if (!have_clicked && this_game_now - nowlimit_time > DIFFICULTY_TIME * 1000)this_game = false, CLEAR_MENU_RUNNING = true;

					//计算总共剩余时间文本
					std::wstringstream wss; // 创建一个宽字符串流对象
					int elapsedTime = ceil(DIFFICULTY_TIME_ALL - nowpenalty - (this_game_now - this_game_start) / 1000.0); // 计算经过的时间
					if (elapsedTime >= 10)wss << L"总剩余时间为：" << std::fixed << std::setprecision(2) << elapsedTime;// 设置精度并插入格式化的字符串
					else wss << L"总剩余时间为： " << std::fixed << std::setprecision(2) << elapsedTime;
					game_time_now = wss.str();// 从字符串流中获取格式化后的字符串，并赋值给 wstring 变量

					//计算限制剩余时间文本
					std::wstringstream wss1;
					int elapsedTime1 = ceil(DIFFICULTY_TIME - (this_game_now - nowlimit_time) / 1000.0);
					wss1 << L"单次剩余时间为：" << std::fixed << std::setprecision(2) << elapsedTime1;
					limit_time_now_text = wss1.str();

					//计算得分
					std::wstringstream wss2;
					wss2 << L"当前得分：" << std::fixed << score;
					score_now = wss2.str();

					//放置剩余时间文本
					if (this_game_now - this_game_start < ceil(DIFFICULTY_TIME_ALL / 4.0 * 3000))settextcolor(YELLOW);
					else settextcolor(RED);
					//setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("华文琥珀"));
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					drawtext(game_time_now.c_str(), &INF_TOP, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//放置单限剩余时间文本
					settextcolor(RED);
					drawtext(limit_time_now_text.c_str(), &INF_MIDDLE, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//放置得分
					if (score < 15)settextcolor(GREEN);
					else if (score < 25)settextcolor(BLUE);
					else settextcolor(YELLOW);
					drawtext(score_now.c_str(), &INF_BOTTOM, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					//检测是否已经按了其中某个按钮
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

			//生存模式————要不要加上限时————加上了饱食度机制24.12.24
			else if (GAMEMODE == survival) {
				DWORD this_game_start = GetTickCount();	//此局游戏的开始时间
				int nowhp = DIFFICULTY_HP;

				DWORD start_fullness = GetTickCount();	//用来计算饱食度
				int awardfullness = 0;	//增加的饱食度
				wstring drawfullness;	//输出用的饱食度

				//设置红心
				IMAGE HP;
				loadimage(&HP, _T("images/HP.png"));

				//设置生命放置头位置		RECT INF_FIRSTHALF = { 900,57+10,1250,157 };x350 y90   54*50
				// RECT INF_TOP = { 900,57 + 10,1250,67 + 60 };
				int hplocx,hplocy=10+67;
				int tmphp = nowhp;
				if (DIFFICULTY_HP == 1)hplocx = 148+900;
				else if (DIFFICULTY_HP == 3)hplocx = 900+(350 - 54 * 3 - 5 * 2) / 2;
				else hplocx = 900+(350 - 54 * 5 - 5 * 4) / 2;

				while (this_game) {
					DWORD starttime_thisgame = GetTickCount();

					//检测是否点击回到主菜单按钮
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();
					while (peekmessage(&msg)) {

						//检测是否点击回到主菜单按钮
						remenubtn.checkstatus(msg);
						remenubtn.putmenu();

						//检测是否点击了某个玩家按钮，且是否得分
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

					//检测是否已经按了其中某个按钮
					if (have_clicked) {
						resetbuttons();
						putplayers();
						have_clicked = false;
					}

					//饱食度不足，扣一条命
					DWORD nowfullness = GetTickCount();
					if ((FULLNESS + awardfullness) * 1000.0 - nowfullness + start_fullness > 60 * 1000.0)awardfullness = floor((60 * 1000.0 - start_fullness + nowfullness)) / 1000.0 - FULLNESS;
					if (nowfullness - start_fullness >= (FULLNESS + awardfullness) * 1000.0) {
						awardfullness += FULLNESS;
						nowhp--;
					}

					//检测剩余生命，生命为0则此局游戏结束
					//DWORD this_game_now = GetTickCount();
					if (nowhp <= 0) this_game = false, CLEAR_MENU_RUNNING = true;

					//计算饱食度
					std::wstringstream wss; // 创建一个宽字符串流对象
					int elapsedTime = ceil(FULLNESS + awardfullness - (nowfullness - start_fullness) / 1000.0); // 计算经过的时间
					// 设置精度并插入格式化的字符串
					if (elapsedTime >= 10)wss << L"剩余饱食度：" << std::fixed << std::setprecision(2) << elapsedTime;
					else wss << L"剩余饱食度： " << std::fixed << std::setprecision(2) << elapsedTime;
					// 从字符串流中获取格式化后的字符串，并赋值给 wstring 变量
					drawfullness = wss.str();

					//计算得分
					std::wstringstream wss2; // 创建一个宽字符串流对象
					// 设置精度并插入格式化的字符串
					wss2 << L"当前得分：" << std::fixed << score;
					// 从字符串流中获取格式化后的字符串，并赋值给 wstring 变量
					score_now = wss2.str();

					//放置饱食度
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					if ((FULLNESS + awardfullness) * 1000.0 - nowfullness + start_fullness > 5*1000.0)settextcolor(YELLOW);
					else settextcolor(RED);
					setbkmode(TRANSPARENT);
					settextstyle(35, 0, _T("华文琥珀"));
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					drawtext(drawfullness.c_str(), &INF_MIDDLE, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					//放置剩余生命
					int tmploc = hplocx;
					for (int i = 1; i <= nowhp; i++) {
						Putimage(tmploc, hplocy, &HP);
						tmploc += 54 + 5;
					}

					//放置得分
					if (score < 25)settextcolor(GREEN);
					else if (score < 35)settextcolor(BLUE);
					else settextcolor(YELLOW);
					//setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("华文琥珀"));
					drawtext(score_now.c_str(), &INF_BOTTOM, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					FlushBatchDraw();
					DWORD endtime_thisgame = GetTickCount();
					DWORD process_thisgame = endtime_thisgame - starttime_thisgame;
					if (process_thisgame < 1000 / 60) {
						Sleep(1000 / 60 - process_thisgame);
					}
				}
			}

			//地狱模式
			else if (GAMEMODE == hell) {
				DWORD this_game_start = GetTickCount();	//此局游戏的开始时间

				DWORD nowlimit_time = GetTickCount();
				wstring limit_time_now_text;

				pre_score = score;

				int nowhp = DIFFICULTY_HP;

				//设置红心
				IMAGE HP;
				loadimage(&HP, _T("images/HP.png"));

				//设置生命放置头位置		RECT INF_FIRSTHALF = { 900,57+10,1250,157 };x350 y90   54*50
				int hplocx, hplocy = 67;
				int tmphp = nowhp;
				if (DIFFICULTY_HP == 1)hplocx = 148 + 900;
				else if (DIFFICULTY_HP == 3)hplocx = 900 + (350 - 54 * 3 - 5 * 2) / 2;
				else hplocx = 900 + (350 - 54 * 5 - 5 * 4) / 2;

				while (this_game) {
					DWORD starttime_thisgame = GetTickCount();

					//检测是否点击回到主菜单按钮
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();

					while (peekmessage(&msg)) {

						//检测是否点击回到主菜单按钮
						remenubtn.checkstatus(msg);
						remenubtn.putmenu();

						//检测是否点击了某个玩家按钮，且是否得分
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

					//检测时间是否超限，超限则此局游戏结束
					DWORD this_game_now = GetTickCount();
					if (!have_clicked && this_game_now - nowlimit_time > DIFFICULTY_TIME * 1000)this_game = false, CLEAR_MENU_RUNNING = true;

					//检测剩余生命，生命为0则此局游戏结束
					if (nowhp == 0) this_game = false, CLEAR_MENU_RUNNING = true;

					//计算限制剩余时间文本
					std::wstringstream wss1;
					int elapsedTime1 = ceil(DIFFICULTY_TIME - (this_game_now - nowlimit_time) / 1000.0);
					wss1 << L"单次剩余时间为：" << std::fixed << std::setprecision(2) << elapsedTime1;
					limit_time_now_text = wss1.str();

					//计算得分
					std::wstringstream wss2;
					wss2 << L"当前得分：" << std::fixed << score;
					score_now = wss2.str();

					//放置单限剩余时间文本
					Putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
					settextstyle(40, 0, _T("华文琥珀"));
					//setbkmode(TRANSPARENT);
					settextcolor(RED);
					drawtext(limit_time_now_text.c_str(), &INF_MIDDLE, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//放置得分
					if (score < 15)settextcolor(GREEN);
					else if (score < 25)settextcolor(BLUE);
					else settextcolor(YELLOW);
					drawtext(score_now.c_str(), &INF_BOTTOM, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					//放置剩余生命
					int tmploc = hplocx;
					for (int i = 1; i <= nowhp; i++) {
						Putimage(tmploc, hplocy, &HP);
						tmploc += 54 + 5;
					}

					//检测是否已经按了其中某个按钮
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

			//结算界面
			int setclearmenu = true;
			GameMode clearmenumode = GAMEMODE;
			while (CLEAR_MENU_RUNNING) {
				DWORD starttime_clearmenu = GetTickCount();

				//放置结算页面
				if (setclearmenu) {
					//结算菜单
					cleardevice();
					putimage(0, 0, &OTBACKGROUND);
					Putimage(398, 75, &CLEARMENUBK);
					wstring gameover = _T("游戏结束"), score_final;	//游戏结束文本，最终得分文本
					RECT gameover_rect = { 590,100,690,150 };
					RECT gamemode_final_rect = { 590,150+10,690,200+10 };
					RECT score_final_rect = { 590,200+20,690,250+20 };
					std::wstringstream wss; // 创建一个宽字符串流对象
					// 设置精度并插入格式化的字符串
					wss << L"最终得分：" << std::fixed << score;
					// 从字符串流中获取格式化后的字符串，并赋值给 wstring 变量
					score_final = wss.str();
					settextcolor(MAGENTA);
					//setbkmode(TRANSPARENT);
					settextstyle(50, 0, _T("华文琥珀"));
					drawtext(gameover.c_str(), &gameover_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					drawtext(score_final.c_str(), &score_final_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					wstring clearmenumode_text=_T("");

					switch (clearmenumode) {
					case race: {
						clearmenumode_text += _T("竞速模式");
						if (DIFFICULTY_TIME == 15)clearmenumode_text += _T(" - 15秒");
						else if (DIFFICULTY_TIME == 30)clearmenumode_text += _T(" - 30秒");
						else clearmenumode_text += _T(" - 60秒");
						break;
					}
					case survival: {
						clearmenumode_text += _T("生存模式");
						if (DIFFICULTY_HP == 5)clearmenumode_text += _T(" - 5生命值");
						else if (DIFFICULTY_HP == 3)clearmenumode_text += _T(" - 3生命值");
						else clearmenumode_text += _T(" - 1生命值");
						break;
					}
					case limit: {
						clearmenumode_text += _T("单限模式");
						if (DIFFICULTY_TIME == 5)clearmenumode_text += _T(" - 5秒");
						else if (DIFFICULTY_TIME == 3)clearmenumode_text += _T(" - 3秒");
						else clearmenumode_text += _T(" - 8秒");
						break;
					}
					case hell: {
						clearmenumode_text += _T("地狱模式");
						if (DIFFICULTY_TIME == 5)clearmenumode_text += _T(" - 5秒");
						else if (DIFFICULTY_TIME == 3)clearmenumode_text += _T(" - 3秒");
						else clearmenumode_text += _T(" - 8秒");
						if (DIFFICULTY_HP == 5)clearmenumode_text += _T(" - 5生命值");
						else if (DIFFICULTY_HP == 3)clearmenumode_text += _T(" - 3生命值");
						else clearmenumode_text += _T(" - 1生命值");
						break;
					}
					}
					settextcolor(YELLOW);
					setbkmode(TRANSPARENT);
					if (clearmenumode != hell)settextstyle(50, 0, _T("华文琥珀"));
					else settextstyle(40, 0, _T("华文琥珀"));
					drawtext(clearmenumode_text.c_str(), &gamemode_final_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					remenubtn_clear.putmenu();
					restartbtn.putmenu();
					chmodebtn_clearmenu.putmenu();
					setclearmenu = false;
				}
				

				while (peekmessage(&msg)) {
					//检测重开按钮和返回主菜单按钮
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

//结算界面的选择模式
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

		//初始模式选择界面
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

		//结束该页面
		if (chmode_clear==false)return;

		//游戏模式，race：规定时间内比拼正确数； survival：有生命数，错一个扣生命； limit：限制单次题目的时间； hell：有生命数，限制单次题目时间
			//如果选择的是race
		if (GAMEMODE == race) {
			cleardevice();
			putimage(0, 0, &CHMODEBK);
			if (DIFFICULTY_TIME < 15)DIFFICULTY_TIME = 60;
			//GameMode pre_gmmode_inrace = GAMEMODE;

			//改变坐标位置
			diftime30btn.setxy(490, 370);
			diftime60btn.setxy(490, 200);
			diftime15btn.setxy(490, 540);

			//放置按钮及文本内容
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

		//如果选择生存模式
		else if (GAMEMODE == survival) {
			cleardevice();
			//if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
			putimage(0, 0, &CHMODEBK);
			//GameMode pre_gmmode_inrace = GAMEMODE;

			//改变坐标位置
			difhp5btn.setxy(490, 200);
			difhp3btn.setxy(490, 370);
			difhp1btn.setxy(490, 540);

			//放置按钮及文本内容
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

		//选择单限模式后
		else if (GAMEMODE == limit) {
			cleardevice();
			if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
			putimage(0, 0, &CHMODEBK);
			//GameMode pre_gmmode_inrace = GAMEMODE;

			//改变坐标位置
			diftime8btn.setxy(490, 200);
			diftime5btn.setxy(490, 370);
			diftime3btn.setxy(490, 540);

			//放置按钮及文本内容
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

		//选择地狱模式后
		else if (GAMEMODE == hell) {
			cleardevice();
			if (DIFFICULTY_TIME > 8)DIFFICULTY_TIME = 8;
			putimage(0, 0, &CHMODEBK);
			//GameMode pre_gmmode_inrace = GAMEMODE;

			//改变坐标位置
			difhp5btn.setxy(665, 200);
			difhp3btn.setxy(665, 370);
			difhp1btn.setxy(665, 540);
			diftime8btn.setxy(315, 200);
			diftime5btn.setxy(315, 370);
			diftime3btn.setxy(315, 540);

			//放置按钮及文本内容
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

//以后再来探索吧
inline void putpa() {
	putimage(440, 90, &PA);
	putimage(335, 90 + 400 + 5, &LATER);
}