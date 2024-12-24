#pragma once
#include"RULEBTN.h"

//此为初始化规则界面按钮的命名空间
namespace RuleInit{
	//非show下的宽高
	int WIDTH_RULE = 150, HEIGHT_RULE = 75;
	//show下的宽，高和普通相同
	int WIDTH_SHOW = 200;
	//非show下的x，y
	int X_NORMAL = 100, Y_NORMAL = 150;
	//show下的x，y和普通的y相同
	int X_SHOW = X_NORMAL - (WIDTH_SHOW - WIDTH_RULE);
	//非show下的rect
	RECT RECT_NORMAL = { X_NORMAL,Y_NORMAL,X_NORMAL + WIDTH_RULE,Y_NORMAL + HEIGHT_RULE };

	//主规则
	LPCTSTR main_wait = _T("images/rule/main/wait.png");
	LPCTSTR main_hold = _T("images/rule/main/hold.png");
	LPCTSTR main_pushed = _T("images/rule/main/pushed.png");
	LPCTSTR main_show = _T("images/rule/main/show.png");
	LPCTSTR main_rule = _T("images/rule/main/rule.png");
	int y_main_rule = Y_NORMAL;
	RULEBTN mainrule(main_wait, main_hold, main_pushed, main_show, main_rule, RECT_NORMAL, X_NORMAL, y_main_rule, X_SHOW, &MAIN_RULE);

	//竞速模式
	LPCTSTR race_wait = _T("images/rule/race/wait.png");
	LPCTSTR race_hold = _T("images/rule/race/hold.png");
	LPCTSTR race_pushed = _T("images/rule/race/pushed.png");
	LPCTSTR race_show = _T("images/rule/race/show.png");
	LPCTSTR race_rule = _T("images/rule/race/rule.png");
	int y_race_rule = Y_NORMAL+HEIGHT_RULE;
	RULEBTN racerule(race_wait, race_hold, race_pushed, race_show, race_rule, RECT_NORMAL, X_NORMAL, y_race_rule, X_SHOW, &RACE_RULE);

	//生存模式
	LPCTSTR survival_wait = _T("images/rule/survival/wait.png");
	LPCTSTR survival_hold = _T("images/rule/survival/hold.png");
	LPCTSTR survival_pushed = _T("images/rule/survival/pushed.png");
	LPCTSTR survival_show = _T("images/rule/survival/show.png");
	LPCTSTR survival_rule = _T("images/rule/survival/rule.png");
	int y_survival_rule = Y_NORMAL + HEIGHT_RULE*2;
	RULEBTN survivalrule(survival_wait, survival_hold, survival_pushed, survival_show, survival_rule, RECT_NORMAL, X_NORMAL, y_survival_rule, X_SHOW, &SURVIVAL_RULE);

	//单限模式
	LPCTSTR limit_wait = _T("images/rule/limit/wait.png");
	LPCTSTR limit_hold = _T("images/rule/limit/hold.png");
	LPCTSTR limit_pushed = _T("images/rule/limit/pushed.png");
	LPCTSTR limit_show = _T("images/rule/limit/show.png");
	LPCTSTR limit_rule = _T("images/rule/limit/rule.png");
	int y_limit_rule = Y_NORMAL + HEIGHT_RULE * 3;
	RULEBTN limitrule(limit_wait, limit_hold, limit_pushed, limit_show, limit_rule, RECT_NORMAL, X_NORMAL, y_limit_rule, X_SHOW, &LIMIT_RULE);

	//地狱模式
	LPCTSTR hell_wait = _T("images/rule/hell/wait.png");
	LPCTSTR hell_hold = _T("images/rule/hell/hold.png");
	LPCTSTR hell_pushed = _T("images/rule/hell/pushed.png");
	LPCTSTR hell_show = _T("images/rule/hell/show.png");
	LPCTSTR hell_rule = _T("images/rule/hell/rule.png");
	int y_hell_rule = Y_NORMAL + HEIGHT_RULE * 4;
	RULEBTN hellrule(hell_wait, hell_hold, hell_pushed, hell_show, hell_rule, RECT_NORMAL, X_NORMAL, y_hell_rule, X_SHOW, &HELL_RULE);

	//道具规则
	LPCTSTR prop_wait = _T("images/rule/prop/wait.png");
	LPCTSTR prop_hold = _T("images/rule/prop/hold.png");
	LPCTSTR prop_pushed = _T("images/rule/prop/pushed.png");
	LPCTSTR prop_show = _T("images/rule/prop/show.png");
	LPCTSTR prop_rule = _T("images/rule/prop/rule.png");
	int y_prop_rule = Y_NORMAL + HEIGHT_RULE * 5;
	RULEBTN proprule(prop_wait, prop_hold, prop_pushed, prop_show, prop_rule, RECT_NORMAL, X_NORMAL, y_prop_rule, X_SHOW, &PROP_RULE);
}