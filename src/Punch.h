#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Punch
{
public:
	Punch();

	virtual void dCone(double x, double y, double h) = 0;
	virtual void dObstacle(double x, double y, double w) = 0;
	virtual void dStartLine(double x, double y, double w) = 0;
	virtual void dMeasureR(Point2f, double, double, string) = 0;
	virtual void dMeasure(double x, double y, double w, string, int = 2) = 0;
	virtual void dMeasureV(double, double, double, string, int = 2) = 0;

	virtual void dCommentR(double x, double y, double a, int fs, string) = 0;

	virtual void dGoalCage(double x, double y, int = 0) = 0;
	virtual void dKeeperarea(double x, double y, int = 0) = 0;
	virtual void dGoalCageDemo(double x, double y) = 0;

	virtual void dLink(double x, double y, double w, double h) = 0;

	virtual void wrt_field(string) = 0;

protected:
	double pi;
	const int W = 1000;
	const int H = 1000;
	const float WF = 10.0;
	const float HF = 10.0;
	const vector<int> BGR_FLOOR = { 0x66, 0x99, 0x33 };
	const vector<int> BGR_CONE = { 0x00, 0x66, 0xff };
	const vector<int> BGR_MEASURE = { 0x66, 0x66, 0x33 };
	const vector<int> BGR_CAPTION = { 0x66, 0, 0x1A };
	const vector<int> BGR_OBSTACLE = { 0x66, 0x66, 0x33 };
	const vector<int> BGR_START_LINE = { 0xFF, 0xFE, 0xFF };
	const vector<int> BGR_CAGE = { 0x0, 0x0, 0xA0 };
	const vector<int> BGR_CAGE_DEMO = { 0x0, 0x0, 0xA0 };
	const vector<int> BGR_CAGE_DEMO_TAPE = { 0x7A, 0xA0, 0xFF };
	const vector<int> BGR_SCORE = { 0xFF, 00, 0 };
	const vector<int> BGR_LINE = { 0xFF, 0xFE, 0xFF };
	const vector<int> BGR_FACEOFF_DOT = { 0xFF, 0xFE, 0x0 };

	const Scalar COL_FLOOR = Scalar(0x66, 0x99, 0x33);
	const Scalar COL_CONE = Scalar(0x33, 0xFF, 0xFF);
	const Scalar COL_START_LINE = Scalar(0xF0, 0xF0, 0xF0);
	const Scalar COL_OBSTACLE = Scalar(0x33, 0x66, 0xFF);
	const Scalar COL_MEASURE = Scalar(0x66, 0x66, 0x33);
	const Scalar COL_CAPTION = Scalar(0xF6, 0xF6, 0xF3);
	const Scalar COL_CAG = Scalar(0x0, 0x0, 0xF0);

	vector<Point2i> normal_coord(const vector<Point2f>&);

	int nor_width, nor_height;
	float log_width, log_height;
};

class Bitmap : public Punch
{
public:
	Bitmap() : Punch() {}
	Bitmap(int a, int b, float c, float d);

	void dCone(double x, double y, double h);
	void dObstacle(double x, double y, double w);
	void dStartLine(double x, double y, double w);
	void dMeasureR(Point2f, double, double, string);
	void dMeasure(double x, double y, double w, string, int);
	void dMeasureV(double x, double y, double w, string, int);

	void dCommentR(double x, double y, double a, int fs, string);

	void dGoalCage(double x, double y, int);
	void dKeeperarea(double x, double y, int);
	void dGoalCageDemo(double x, double y);

	void dLink(double x, double y, double w, double h);

	void wrt_field(string);
private:
	Mat m;
};

class Scalable : public Punch
{
public:
	Scalable() : Punch() {}
	Scalable(int a, int b, float c, float d);

	void dCone(double x, double y, double h);
	void dObstacle(double x, double y, double w);
	void dStartLine(double x, double y, double w);
	void dMeasureR(Point2f, double, double, string);
	void dMeasure(double x, double y, double w, string, int);
	void dMeasureV(double x, double y, double w, string, int);

	void dCommentR(double x, double y, double a, int fs, string);

	void dGoalCage(double x, double y, int);
	void dKeeperarea(double x, double y, int);
	void dGoalCageDemo(double x, double y);

	void dLink(double x, double y, double w, double h);

	void wrt_field(string);
private:
	stringstream ss;
	const vector<string> SvgFontSize = { "14", "22", "26", "30" };

	void svgPolyline(const vector<Point>&, string, int);
	void svgPolygon(const vector<Point>&, string, bool = true);
	void svgLine(const Point2i, const Point2i, string, int = 0, int = 1);		// point-1 , point-2 , caption , ê¸éÌ(0:continuas,1:dash ---  ---), line-width
	void svgText(const string, const Point2i, string, int = 1, double = 0.0); // caption , point , colour , font-size , angle
	void svgLink(const int, int, int, int, string);

	string rgb6(const vector<int>&, const string = "#");
};

