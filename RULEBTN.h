#pragma once
#include<graphics.h>

bool MAIN_RULE = false, RACE_RULE = false, LIMIT_RULE = false, SURVIVAL_RULE = false, HELL_RULE = false, PROP_RULE = false;
bool* NOW_RULE = NULL;


//状态
enum StatusRule {
	rWait,rHold,rPushed,rShow
};

//绘制有透明的图片
#pragma comment(lib, "MSIMG32.LIB")
inline void RPutimage(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

class RULEBTN {
private:
	IMAGE wait;
	IMAGE hold;
	IMAGE pushed;
	IMAGE show;
	IMAGE rule;		//h8*75=500,w1280-200-100-150=830
	int x, y;
	int showx, showy;
	int rulex, ruley;
	int width, height;	//非rShow状态的长宽
	RECT rect;			//非rShow状态的区域
	StatusRule status;
	bool* thisrule;

public:
	//构造函数
	RULEBTN(LPCTSTR& wai, LPCTSTR& hol, LPCTSTR& pus, LPCTSTR& sho, LPCTSTR& rul, RECT& rect, int& x_, int& y_, int& shx, bool* th) {
		loadimage(&wait, wai);
		loadimage(&hold, hol);
		loadimage(&pushed, pus);
		loadimage(&show, sho);
		loadimage(&rule, rul);
		showx = shx;
		showy = y_;
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
		x = x_;
		y = y_;
		status = rWait;
		thisrule = th;
		rulex = 100+150, ruley = 75+30;
	}

	//手动设置刚打开规则介绍界面时放置主规则
	void setmain() {
		*thisrule = true;
		NOW_RULE = thisrule;
		status = rShow;
	}

	//放置图片
	void put() {
		if (*thisrule == false && status == rShow)status = rWait;
		switch (status) {
		case StatusRule::rWait:
			RPutimage(x, y, &wait);
			break;
		case StatusRule::rHold:
			RPutimage(x, y, &hold);
			break;
		case StatusRule::rPushed:
			RPutimage(x, y, &pushed);
			break;
		case StatusRule::rShow:
			RPutimage(rulex, ruley, &rule);
			RPutimage(showx, showy, &show);
			break;
		defalut:
			break;
		}
	}

	//检测是否在按钮范围内
	bool inbutton(int cx, int cy) {
		if (cx >= x && cx <= x + width && cy >= y && cy <= y + height)return true;
		return false;
	}

	//按下按键后放置对应的规则
	void onclick() {
		RPutimage(rulex, ruley, &rule);
	}

	//改变按钮状态
	void checkstatus(const ExMessage& msg) {

		if (status != rShow) {
			switch (msg.message) {
			case WM_MOUSEMOVE:	//若鼠标在移动
				if (status == rWait && inbutton(msg.x, msg.y))status = rHold;			//移到按钮内部
				else if (status == rHold && !inbutton(msg.x, msg.y))status = rWait;	//移到按钮外部
				break;
			case WM_LBUTTONDOWN:	//按下左键
				if (inbutton(msg.x, msg.y))		//在按钮内部
					status = rPushed;
				break;
			case WM_LBUTTONUP:		//左键抬起
				if (status == rPushed && inbutton(msg.x, msg.y)) {
					NOW_RULE = thisrule;
					*thisrule = true;
					if (&MAIN_RULE != thisrule)MAIN_RULE = false;
					if (&RACE_RULE != thisrule)RACE_RULE = false;
					if (&LIMIT_RULE != thisrule)LIMIT_RULE = false;
					if (&SURVIVAL_RULE != thisrule)SURVIVAL_RULE = false;
					if (&HELL_RULE != thisrule)HELL_RULE = false;
					if (&PROP_RULE != thisrule)PROP_RULE = false;
					status = rShow;
					onclick();		//进行内部函数处理
				}
				else status = rWait;
				break;
			defalut:
				break;
			}
		}
	}

	//为了你 我变成狼人模样
	
	//为了你 染上了疯狂
	
	//为了你 穿上厚厚的伪装

	//为了你 换了心肠

	//我们还能不能再见面

	//我在佛前苦苦求了几千年

	//愿意用几世换我们一世情缘

	//希望可以感动 上天

	//我们还能不能能不能再见面

	//我在佛前苦苦求了几千年

	//当我在踏过这条奈何桥之前

	//让我再吻一吻你的脸
};