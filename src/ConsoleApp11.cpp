// ConsoleApp11.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "Punch.h"

using namespace cv;
using namespace std;

void draw1ShootAroundTheGoal(string);
void draw2ReceiveAndPass(string);
void draw3StickHandling(string);
void draw4ShootForAccuracy(string);
void draw5FlipPassOverAnObstacle(string);
void draw11Rink_4x4(string);
void draw12Rink_6x6(string);
void draw13Rink_5x5unified(string);
void draw21Ball(string);

int main(int argc, char**argv)
{
	string wpath1 = "1_ShootAroundTheGoal.svg";
	string wpath2 = "2_ReceiveAndPass.svg";
	string wpath3 = "3_Stickhandling.svg";
	string wpath4 = "4_ShootForAccuracy.svg";
	string wpath5 = "5_FlipPassOverAnObstacle.svg";
	string wpath11 = "11_Rink_4x4.svg";
	string wpath12 = "12_Rink_6x6.svg";
	string wpath13 = "13_Rink_5x5unified.svg";
	string wpath21 = "21_Ball.svg";
	if (argc == 1) {
		string n = *argv;

		cout << std::filesystem::path(n).stem().string() << " n" << endl;
		cout << " " << wpath1 << endl;
		cout << " " << wpath2 << endl;
		cout << " " << wpath3 << endl;
		cout << " " << wpath4 << endl;
		cout << " " << wpath5 << endl;
		cout << " 0: all" << endl;
		return 1;
	}
	int n = stoi(*(argv + 1));
 	switch (n)
	{
	case 0:
		draw1ShootAroundTheGoal(wpath1);
		draw2ReceiveAndPass(wpath2);
		draw3StickHandling(wpath3);
		draw4ShootForAccuracy(wpath4);
		draw5FlipPassOverAnObstacle(wpath5);
		draw11Rink_4x4(wpath11);
		draw12Rink_6x6(wpath12);
		draw13Rink_5x5unified(wpath13);
		draw21Ball(wpath21);
		break;
	case 1:
		draw1ShootAroundTheGoal(wpath1);
		break;
	case 2:
		draw2ReceiveAndPass(wpath2);
		break;
	case 3:
		draw3StickHandling(wpath3);
		break;
	case 4:
		draw4ShootForAccuracy(wpath4);
		break;
	case 5:
		draw5FlipPassOverAnObstacle(wpath5);
		break;

	case 11:
		draw11Rink_4x4(wpath11);
		break;
	case 12:
		draw12Rink_6x6(wpath12);
		break;
	case 13:
		draw13Rink_5x5unified(wpath13);
		break;

	case 21:
		draw21Ball(wpath21);
		break;
	default:
		break;
	}

}


void draw1ShootAroundTheGoal(string path)
{
	Punch* draw;
	if (1 == 2) {
		draw = new Bitmap(900, 900, 10.0, 10.0);
	}
	else {
		draw = new Scalable(900, 900, 10.0, 10.0);
	}

	draw->dGoalCage(0.0, 3.0);
	draw->dKeeperarea(0.0, 3.0);
	draw->dCone(0.0, -2.0, 0.1);
	double pi = acos(-1);
	double r30 = 30.0 / (180.0 / pi);
	double a = 5.0 * sin(r30);
	double b = a / tan(r30);
	draw->dCone(a, -2.0 + (5.0 - b), 0.1);
	double r60 = 60.0 / (180.0 / pi);
	double a1 = 5.0 * sin(r60);
	double b1 = a1 / tan(r60);
	draw->dCone(a1, -2.0 + (5.0 - b1), 0.1);
	draw->dCone(-a1, -2.0 + (5.0 - b1), 0.1);
	draw->dCone(-a, -2.0 + (5.0 - b), 0.1);
	draw->dCone(-a1, -2.0 + (5.0 - b1), 0.1);

	draw->dMeasureR(Point2f(0.0, 3.0), 30.0, 5.0, "5m");
	draw->dMeasureR(Point2f(0.0, 3.0), 60.0, 5.0, "5m");
	draw->dMeasureR(Point2f(0.0, 3.0), 0.0, 5.0, "5m");
	draw->dMeasureR(Point2f(0.0, 3.0), -30.0, 5.0, "5m");
	draw->dMeasureR(Point2f(0.0, 3.0), -60.0, 5.0, "5m");

	double r8 = 8.0 / (180.0 / pi);
	double r38 = 38.0 / (180.0 / pi);
	double r68 = 68.0 / (180.0 / pi);
	double rm24 = -24.0 / (180.0 / pi);
	double rm54 = -54.0 / (180.0 / pi);
	double rm84 = -84.0 / (180.0 / pi);
	double l = 1.1;
	double a2 = l * sin(r8);
	double b2 = a2 / tan(r8);
	draw->dCommentR(0.0 + a2, 3.0 - b2, 15.0, 0, u8"30度");
	a2 = l * sin(r38);
	b2 = a2 / tan(r38);
	draw->dCommentR(0.0 + a2, 3.0 - b2, 45.0, 0, u8"30度");
	a2 = l * sin(r68);
	b2 = a2 / tan(r68);
	draw->dCommentR(0.0 + a2, 3.0 - b2, 75.0, 0, u8"30度");

	a2 = l * sin(rm24);
	b2 = a2 / tan(rm24);
	draw->dCommentR(0.0 + a2, 3.0 - b2, -15.0, 0, u8"30度");
	a2 = l * sin(rm54);
	b2 = a2 / tan(rm54);
	draw->dCommentR(0.0 + a2, 3.0 - b2, -45.0, 0, u8"30度");
	a2 = l * sin(rm84);
	b2 = a2 / tan(rm84);
	draw->dCommentR(0.0 + a2, 3.0 - b2, -75.0, 0, u8"30度");

	draw->wrt_field(path);
}
void draw2ReceiveAndPass(string path)
{
	Punch* draw;
	if (1 == 2) {
		draw = new Bitmap(900, 900, 10.0, 10.0);
	}
	else {
		draw = new Scalable(900, 900, 10.0, 10.0);
	}

	draw->dCone(-1.5, 4.0, -0.4);
	draw->dCone(-0.5, 4.0, -0.4);
	draw->dCone(0.5, 4.0, -0.4);
	draw->dCone(1.5, 4.0, -0.4);
	draw->dMeasure(-1.0, 4.25, 1.0, "1m");
	draw->dMeasure(0.0, 4.25, 1.0, "1m");
	draw->dMeasure(1.0, 4.25, 1.0, "1m");

	draw->dMeasureV(-3.0, 0.0, 8.0, "8m");

	draw->dStartLine(0.0, -4.0, 1.5);
	draw->dCone(0.0, -4.0, 0.1);
	draw->dMeasureR(Point2f(0.0, -4.0), 135.0, 4.0, "4m");
	draw->dMeasureR(Point2f(0.0, -4.0), -135.0, 4.0, "4m");

	double pi = acos(-1);
	double r45 = 45.0 / (180.0 / pi);
	double a = cos(r45) * 4.0;
	draw->dCommentR(0.0 + a, -4.0 + a, 0.0, 0, u8"👧🏻");
	draw->dCommentR(0.0 - a, -4.0 + a, 0.0, 0, u8"🧑🏻‍🦱");
	draw->dCommentR(-0.5, -4.5, 0.0, 0, u8"👲🏻");

	draw->wrt_field(path);
}
void draw3StickHandling(string path)
{
	Punch* draw;
	if (1 == 2) {
		draw = new Bitmap(900, 900, 10.0, 10.0);
	}
	else {
		draw = new Scalable(900, 900, 26.0, 26.0);
	}
	draw->dGoalCage(0.0, 10.0);

	draw->dCone(0, 7.0, -0.6);
	draw->dCone(0, 4.0, -0.6);
	draw->dCone(0, 1.0, -0.6);
	draw->dCone(0, -2.0, -0.6);
	draw->dCone(0, -5.0, -0.6);
	draw->dCone(0, -8.0, -0.6);

	draw->dMeasureV(8.0, -0.5, 21.0, "21m");
	draw->dMeasureV(-8.0, 8.5, 3.0, "3m");
	draw->dMeasureV(-8.0, 5.5, 3.0, "3m");
	draw->dMeasureV(-8.0, 2.5, 3.0, "3m");
	draw->dMeasureV(-8.0, -0.5, 3.0, "3m");
	draw->dMeasureV(-8.0, -3.5, 3.0, "3m");
	draw->dMeasureV(-8.0, -6.5, 3.0, "3m");
	draw->dMeasureV(-8.0, -9.5, 3.0, "3m");

	draw->dStartLine(0.0, -11.0, 2.0);

	draw->wrt_field(path);
}
void draw4ShootForAccuracy(string path)
{
	Punch* draw;
	if (1 == 2) {
		draw = new Bitmap(900, 900, 10.0, 10.0);
	}
	else {
		draw = new Scalable(900, 900, 10.0, 10.0);
	}
	draw->dGoalCage(0.0, 3.0);
	draw->dKeeperarea(0.0, 3.0);
	draw->dMeasureV(-3.0, 0.5, 5.0, "5m");
	draw->dStartLine(0.0, -2.0, 1.5);

	draw->dGoalCageDemo(3.0, -1.0);

	draw->wrt_field(path);
}

void draw5FlipPassOverAnObstacle(string path)
{
	Punch* draw;
	if (1 == 2) {
		draw = new Bitmap(900, 900, 10.0, 10.0);
	}
	else {
		draw = new Scalable(900, 900, 10.0, 10.0);
	}

	draw->dCone(-1.5, 4.0, -0.4);
	draw->dCone(-0.5, 4.0, -0.4);
	draw->dCone(0.5, 4.0, -0.4);
	draw->dCone(1.5, 4.0, -0.4);
	draw->dMeasure(-1.0, 4.25, 1.0, "1m");
	draw->dMeasure(0.0, 4.25, 1.0, "1m");
	draw->dMeasure(1.0, 4.25, 1.0, "1m");

	draw->dMeasureV(-3.0, 2.0, 4.0, "4m");
	draw->dMeasureV(-3.0, -2.0, 4.0, "4m");

	draw->dObstacle(0.0, 0.0, 1.5);
	draw->dMeasure(0.0, 0.2, 3.0, u8"障害物 幅 3m以上, 高さ 25～30 cm");

	draw->dStartLine(0.0, -4.0, 1.5);

	draw->wrt_field(path);
}

void draw11Rink_4x4(string wpath)
{
	Punch* draw;
	if (1 == 2) {
		draw = new Bitmap(900, 540, 30.0, 18.0);
	}
	else {
		draw = new Scalable(900, 540, 30.0, 18.0);
	}
	draw->dRink4x4(0.0, 0.0, 20.0, 12.0);

	draw->wrt_field(wpath);
}

void draw12Rink_6x6(string wpath)
{
	Punch* draw;
	if (1 == 2) {
		draw = new Bitmap(900, 540, 30.0, 18.0);
	}
	else {
		draw = new Scalable(900, 450, 54.0, 27.0);
	}
	draw->dRink6x6(-7.0, 0.0, 36.0, 18.0);
	draw->wrt_field(wpath);
}

void draw13Rink_5x5unified(string wpath)
{
	Punch* draw;
	if (1 == 2) {
		draw = new Bitmap(900, 540, 36.0, 21.0);
	}
	else {
		draw = new Scalable(900, 540, 36.0, 21.0);
	}
	draw->dRink5x5unified(0.0, 0.0, 24.0, 14.0);
	draw->wrt_field(wpath);
}

void draw21Ball(string wpath)
{
	Punch* draw;
	if (1 == 2) {
		draw = new Bitmap(900, 900, 10.0, 10.0);
	}
	else {
		draw = new Scalable(600, 600, 100.0, 100.0);
	}
	draw->dBall(0.0, 0.0, 72.0, 11.0);

	draw->wrt_field(wpath);
}
