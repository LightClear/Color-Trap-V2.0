#pragma once
#include<graphics.h>
#include<cstdio>
#include<string>
using std::wstring;

enum COLOR {
	black, green, yellow, red, brown, blue, purple, cyan, null
};

//绘制包含透明度信息的图片
#pragma comment(lib, "MSIMG32.LIB")
inline void Putimage1(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

//暂时废弃,本来也是用来绘制透明度图片的
//#pragma comment(lib, "MSIMG32.LIB")
//void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg) {
//	HDC dstDC = GetImageHDC(dstimg);
//	HDC srcDC = GetImageHDC(srcimg);
//	int w = srcimg->getwidth();
//	int h = srcimg->getheight();
//	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
//	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
//}

class GameButton {
private:
	RECT rect;
	COLOR color;
	wstring text;
	IMAGE bk;
	int textsize;
	int texttype;

public:
	//初始构造函数
	GameButton(RECT rec, COLOR col, wstring tex, LPCTSTR bkname, int size) {
		rect = rec;
		color = col;
		text = tex;
		loadimage(&bk, bkname);
		textsize = size;
	}

	//用来重新设置内容的构造函数
	void reset(COLOR col, wstring tex) {
		color = col;
		text = tex;
	}

	//设置按钮类型
	void settype(int x) {
		texttype = x;
	}

	//放置背景及文本
	//black,green,yellow,red,brown,blue,purple,cyan
	void putthings() {
		if (texttype == 1)putimage(rect.left, rect.top, &bk);
		else Putimage1(rect.left, rect.top, &bk);
		int wd = 0, he = 0;
		switch (color) {
		case black: {
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("华文琥珀"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		}
		case green: {
			settextcolor(GREEN);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("华文琥珀"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		}
		case yellow: {
			settextcolor(YELLOW);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("华文琥珀"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		}
		case red: {
			settextcolor(RED);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("华文琥珀"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		}
		case brown: {
			settextcolor(BROWN);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("华文琥珀"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		}
		case blue: {
			settextcolor(BLUE);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("华文琥珀"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		}
		case purple: {
			settextcolor(MAGENTA);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("华文琥珀"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		}
		case cyan: {
			settextcolor(CYAN);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("华文琥珀"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			break;
		}
		}
	}

	//检测鼠标点击范围
	bool checkclick(const ExMessage& msg) {
		if (msg.message==WM_LBUTTONDOWN && msg.x >= rect.left && msg.x <= rect.right && msg.y >= rect.top && msg.y <= rect.bottom)return true;
		return false;
	}

	//复制对象的文本
	void gettext(wstring& s) {
		s = text;
	}

	//获得color值
	COLOR getcolor() {
		return color;
	}

};


//玩家按的按钮
class Ken :public GameButton {		//为什么要叫Ken这个名字，因为我高中里的“大幺儿”给我取的
public:
	Ken(RECT rec, COLOR col, wstring tex, LPCTSTR bkname, int size) :GameButton(rec, col, tex, bkname, size) {}
	

};


//题目的按钮
class Title :public GameButton {
public:
	Title(RECT rec, COLOR col, wstring tex, LPCTSTR bkname, int size):GameButton(rec, col, tex, bkname, size){}

	//检测是否得分
	//black,green,yellow,red,brown,blue,purple,cyan
	bool checkscore(Ken& but) {
		wstring s;
		but.gettext(s);
		COLOR check = null;
		int i = 0;
		wstring sc1 = { _T("黑色") };
		wstring sc2 = { _T("绿色") };
		wstring sc3 = { _T("黄色") };
		wstring sc4 = { _T("红色") };
		wstring sc5 = { _T("棕色") };
		wstring sc6 = { _T("蓝色") };
		wstring sc7 = { _T("紫色") };
		wstring sc8 = { _T("青色") };
		COLOR assign[8] = { black,green,yellow,red,brown,blue,purple,cyan };
		if (s == sc1) { check = assign[0]; }
		if (s == sc2) { check = assign[1]; }
		if (s == sc3) { check = assign[2]; }
		if (s == sc4) { check = assign[3]; }
		if (s == sc5) { check = assign[4]; }
		if (s == sc6) { check = assign[5]; }
		if (s == sc7) { check = assign[6]; }
		if (s == sc8) { check = assign[7]; }
		return check == getcolor();
	}
};