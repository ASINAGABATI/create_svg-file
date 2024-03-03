#include <vector>
//#include <format>
#include <iostream>
#include <fstream>
#include "Punch.h"

using namespace cv;
using namespace std;

Punch::Punch()
{
	nor_width = 0;
	nor_height = 0;
	log_width = 0;
	log_height = 0;
	pi = acos(-1);
}

vector<Point2i> Punch::normal_coord(const vector<Point2f>& pts)
{
	vector<Point2i>vers;
	for (Point2f p0 : pts) {
		float x0 = p0.x + log_width / 2.0;
		float y0 = log_height - (p0.y + log_height / 2.0);
 		Point2i p1 = Point2i((int)(x0 * (float)nor_width / log_width), (int)(y0 * (float)nor_height / log_height));
 		vers.push_back(p1);
	}
	return vers;
}
int Punch::normal_height(const float l)
{
	return (int)(l * nor_height /log_height);

}

Bitmap::Bitmap(int w, int h, float lw, float lh)
{
	nor_width = w;
	nor_height = h;
	log_width = lw;
	log_height = lh;
	pi = acos(-1);

 	m = Mat(w, h, CV_8UC3, COL_FLOOR);
}
void Bitmap::dCone(double x, double y, double h)
{
	double r = 60 / (180 / pi);
	double a = h / tan(r);
	double b = sqrt(a * a + h * h);
	Point2f p1 = Point2f((float)x, (float)(y + (h - a)));
	Point2f p2 = Point2f((float)(x + a), (float)(y - (h - a)));
	Point2f p3 = Point2f((float)(x - a), (float)(y - (h - a)));
	vector<Point2f> tri{ p1, p2, p3 };
	vector<Point2i>coord = normal_coord(tri);

	fillConvexPoly(m, coord, COL_CONE, LINE_AA);
}
void Bitmap::dObstacle(double x, double y, double w)
{
	double a = w / 20.0;
	vector<Point2f>rect{ Point2f((float)(x - w, y - a)), Point2f((float)(x + w, y - a)), Point2f((float)(x + w, y + a)), Point2f((float)(x - w), (float)(y + a)) };
	vector<Point2i>coord = normal_coord(rect);
	fillConvexPoly(m, coord, COL_OBSTACLE, LINE_AA);
}
void Bitmap::dStartLine(double x, double y, double w)
{
	double a = w / 100.0;
	vector<Point2f>rect{ Point2f((float)(x - w), (float)(y - a)), Point2f((float)(x + w), (float)(y - a)), 
			Point2f((float)(x + w), (float)(y + a)), Point2f((float)(x - w), (float)(y + a)) };
	vector<Point2i>coord = normal_coord(rect);
	fillConvexPoly(m, coord, COL_START_LINE, LINE_AA);
}
void Bitmap::dMeasureR(Point2f p, double r, double len, string cap)
{

}
void Bitmap::dMeasure(double x, double y, double w, string cap, int sz)
{
	double a = w / 30.0;
	vector<Point2f>measure{ Point2f((float)(x - w / 2), (float)y), Point2f((float)(x + w / 2), (float)y) };
	vector<Point2i>coord = normal_coord(measure);
	cv::line(m, coord[0], coord[1], COL_MEASURE, 1, LINE_AA);

	vector<Point2f>measure1{ Point2f((float)(x - w / 2), (float)(y - a)), Point2f((float)(x - w / 2), (float)(y + a)) };
	vector<Point2i>coord1 = normal_coord(measure1);
	cv::line(m, coord1[0], coord1[1], COL_MEASURE, 1, LINE_AA);

	vector<Point2f>measure2{ Point2f((float)(x + w / 2), (float)(y - a)), Point2f((float)(x + w / 2), (float)(y + a)) };
	vector<Point2i>coord2 = normal_coord(measure2);
	cv::line(m, coord2[0], coord2[1], COL_MEASURE, 1, LINE_AA);

	vector<Point2f>measure3{ Point2f((float)(x - w / 4), (float)(y + 5 * a)) };
	vector<Point2i>coord3 = normal_coord(measure3);
	putText(m, cap, coord3[0], FONT_HERSHEY_SIMPLEX, 1.0, COL_CAPTION);
}
void Bitmap::dMeasureV(double x, double y, double w, string cap, int sz)
{
	double a = w / 30.0;
	vector<Point2f>measure{ Point2f((float)x, (float)(y + w / 2)), Point2f((float)x, (float)(y - w / 2)) };
	vector<Point2i>coord = normal_coord(measure);
	cv::line(m, coord[0], coord[1], COL_MEASURE, 1, LINE_AA);

	vector<Point2f>measure1{ Point2f((float)(x - a), (float)(y + w / 2)), Point2f((float)(x + a), (float)(y + w / 2)) };
	vector<Point2i>coord1 = normal_coord(measure1);
	cv::line(m, coord1[0], coord1[1], COL_MEASURE, 1, LINE_AA);

	vector<Point2f>measure2{ Point2f((float)(x - a), (float)(y - w / 2)), Point2f((float)(x + a), (float)(y - w / 2)) };
	vector<Point2i>coord2 = normal_coord(measure2);
	cv::line(m, coord2[0], coord2[1], COL_MEASURE, 1, LINE_AA);

	vector<Point2f>measure3{ Point2f((float)(x - w / 8), (float)y) };
	vector<Point2i>coord3 = normal_coord(measure3);
	putText(m, cap, coord3[0], FONT_HERSHEY_SIMPLEX, 1.0, COL_CAPTION);
}
void Bitmap::dCommentR(double x, double y, double a, int fs, string cap)
{

}
void Bitmap::dRink4x4(double x, double y, double w, double h)
{

}
void Bitmap::dRink6x6(double x, double y, double w, double h)
{

}
void Bitmap::dRink5x5unified(double x, double y, double w, double h)
{

}
void Bitmap::dBall(double x, double y, double d, double dh)
{

}

void Bitmap::wrt_field(string path)
{
	imwrite(path, m);
	cout << "write " << path << endl;
}
void Bitmap::dGoalCage(float x, float y, int a)
{
}
void Bitmap::dGoalPost(float x, float y, int a)
{
}
void Bitmap::dKeeperarea(double x, double y, int a)
{
}
void Bitmap::dGoalCrease(double x, double y, int a, float wide, float depth)
{
}
void Bitmap::dGoalCageDemo(double x, double y)
{
}

Scalable::Scalable(int w, int h, float lw, float lh)
{
	nor_width = w;
	nor_height = h;
	log_width = lw;
	log_height = lh;
	pi = acos(-1);

	ss << "<svg" << endl;
	ss << " xmlns = \"http://www.w3.org/2000/svg\"" << endl;
    ss << " width = \"" << to_string(nor_width) << "\"" << endl;
	ss << " height= \"" << to_string(nor_height) << "\"" << endl;
	ss << " viewBox = \"" << "0 0 " << to_string(nor_width) << " " << to_string(nor_height) << "\"" << " >" << endl << endl;

	ss << "  <rect x=\"0\" y=\"0\" width=\"" << to_string(nor_width) << "\" height=\"" << to_string(nor_height) << "\" fill=\"" << rgb6(BGR_FLOOR) << "\" fill-opacity=\"0.4\" />" << endl;
}
void Scalable::dCone(double x, double y, double h)
{
	double r60 = 60 / (180 / pi);
	double r30 = (h / abs(h)) * 30 / (180 / pi);
	double a = abs(h / tan(r60));
	double b = a * tan(r30);
	Point2f p1 = Point2f((float)x, (float)(y + h - b) );
	Point2f p2 = Point2f((float)(x + a), (float)(y - b));
	Point2f p3 = Point2f((float)(x - a), (float)(y - b));

	vector<Point2f> tri{ p1, p2, p3 };
	vector<Point2i>coord = normal_coord(tri);

	string col = rgb6(BGR_CONE);
	svgPolygon(coord, col);
}
void Scalable::dMeasureR(Point2f sp, double ang, double len, string cap)
{
	double r = ang / (180 / pi);
	double a = len * sin(r);
	double b = a == 0.0 ? len : a / tan(r);
	Point2f p2 = Point2f((float)(sp.x + a), (float)(sp.y - b));

	ang += 2;
	r = ang / (180 / pi);
	a = len * sin(r);
	b = a == 0.0 ? len : a / tan(r);
	Point2f p2_3 = Point2f((float)(sp.x + a), (float)(sp.y - b));

	float f = abs(ang) < 90 ? -1 : 1;
	Point2f p3 = Point2f((float)(sp.x + (p2_3.x - sp.x) / 2), (float)(sp.y + f * abs(p2_3.y - sp.y) / 2));

	vector<Point2f>measure{ sp, p2, p3 };
	vector<Point2i>coord = normal_coord(measure);
	string col = rgb6(BGR_MEASURE);
	svgLine(coord[0], coord[1], col, 1);

	col = rgb6(BGR_CAPTION);
 	svgText(cap, coord[2], col, 2, -1.0 * ang);
}
void Scalable::dMeasure(double x, double y, double w, string cap, int sz)
{
	double a = w / 30.0;
	vector<Point2f>measure{ Point2f((float)(x - w / 2), (float)y), Point2f((float)(x + w / 2), (float)y) };
	vector<Point2i>coord = normal_coord(measure);
	string col = rgb6(BGR_MEASURE);
	svgLine(coord[0], coord[1], col, 1);

	vector<Point2f>measure1{ Point2f((float)(x - w / 2), (float)(y - a)), Point2f((float)(x - w / 2), (float)(y + a)) };
	vector<Point2i>coord1 = normal_coord(measure1);
	svgLine(coord1[0], coord1[1], col);

	vector<Point2f>measure2{ Point2f((float)(x + w / 2), (float)(y - a)), Point2f((float)(x + w / 2), (float)(y + a)) };
	vector<Point2i>coord2 = normal_coord(measure2);
	svgLine(coord2[0], coord2[1], col);

	vector<Point2f>measure3{ Point2f((float)(x - w / 8), (float)y) };
	vector<Point2i>coord3 = normal_coord(measure3);
	coord3[0].y -= 6;
	col = rgb6(BGR_CAPTION);
	svgText(cap, Point2i(coord3[0].x, coord3[0].y - 5), col, sz);

}
void Scalable::dMeasureV(double x, double y, double w, string cap, int sz)
{
	double a = w / 30.0;
	vector<Point2f>measure{ Point2f((float)x, (float)(y + w / 2)), Point2f((float)x, (float)(y - w / 2)) };
	vector<Point2i>coord = normal_coord(measure);
	string col = rgb6(BGR_MEASURE);
	svgLine(coord[0], coord[1], col, 1);

	vector<Point2f>measure1{ Point2f((float)(x - a), (float)(y + w / 2)), Point2f((float)(x + a), (float)(y + w / 2)) };
	vector<Point2i>coord1 = normal_coord(measure1);
	svgLine(coord1[0], coord1[1], col);

	vector<Point2f>measure2{ Point2f((float)(x - a), (float)(y - w / 2)), Point2f((float)(x + a), (float)(y - w / 2)) };
	vector<Point2i>coord2 = normal_coord(measure2);
	svgLine(coord2[0], coord2[1], col);

	vector<Point2f>measure3{ Point2f((float)(x - w / 9), (float)y) };
	vector<Point2i>coord3 = normal_coord(measure3);
	col = rgb6(BGR_CAPTION);
	svgText(cap, coord3[0], col, sz);
}
void Scalable::dCommentR(double x, double y, double ang, int fs, string cap)
{
	vector<Point2f>measure{ Point2f((float)x, (float)y) };
	vector<Point2i>coord = normal_coord(measure);
	string col = rgb6(BGR_CAPTION);
	svgText(cap, coord[0], col, fs, -1.0 * ang);
}
void Scalable::dObstacle(double x, double y, double w)
{
	double a = w / 20.0;
	vector<Point2f>rect{ Point2f((float)(x - w), (float)(y - a)), Point2f((float)(x + w), (float)(y - a)), Point2f((float)(x + w), (float)(y + a)), Point2f((float)(x - w), (float)(y + a)) };
	vector<Point2i>coord = normal_coord(rect);
	string col = rgb6(BGR_OBSTACLE);
	svgPolygon(coord, col);
}
void Scalable::dStartLine(double x, double y, double w)
{
	double a = w / 50.0;
	vector<Point2f>rect{ Point2f((float)(x - w), (float)y), Point2f((float)(x + w), (float)y),
			Point2f((float)(x + w), (float)(y + a)), Point2f((float)(x - w), (float)(y + a)) };
	vector<Point2i>coord = normal_coord(rect);
	string col = rgb6(BGR_START_LINE);
	svgPolygon(coord, col);
}
void Scalable::dGoalCage(float x, float y, int a)
{
	int lwpx = 2; //4;
	float dx1, dx3, dy1, dy3;
	int offx, offy;
	if (a == 0) {
		dx1 = (float)(-0.8);
		dy1 = (float)0.6;
		dx3 = (float)0.8;  dy3 = (float)0.0;
		offx = 0; offy = -lwpx;
	}
	else {
		dx1 = (float)0.0;	dy1 = a == (float)90 ? (float)0.8 : (float)(-0.8)	;
		dx3 = a == 90 ? (float)0.6 : (float)(-0.6);  dy3 = a == 90 ? (float)(-0.8) : (float)0.8;
		offy = 0;
		offx = a == 90 ? lwpx : -lwpx;
	}
	vector<Point2f>frm{ Point2f(x + dx1, y + dy1), Point2f(x + dx3, y + dy3) };
	vector<Point2i>coord = normal_coord(frm);
	for (auto& p : coord) {
		p.x += offx;
		p.y += offy;	//lineïù
	}
	string col = rgb6(BGR_CAGE);

	int x0, y0, w, h;
	if (a == 0) {
		x0 = coord[0].x;
		y0 = coord[0].y;
		w = coord[1].x - coord[0].x;
		h = coord[1].y - coord[0].y;
	} else {
		x0 = a == 90 ? coord[0].x : coord[1].x;
		y0 = a == 90 ? coord[0].y : coord[1].y;
		w = abs(coord[1].x - coord[0].x);
		h = abs(coord[1].y - coord[0].y);
	}
	ss << "  <rect x=\"" << x0 << "\" y=\"" << y0 << "\" rx=\"5\" ry=\"5\" width=\"" << w << "\" height=\"" << h  << "\" stroke=\"" << col << "\"";
		ss << " fill=\"transparent\" fill-opacity=\"0.0\" stroke-width=\"" << lwpx << "\" />" << endl;
}
void Scalable::dGoalPost(float x, float y, int a)
{
	float f = 1.0;
	if (a == -91) {
		a = -91;
		f = 1.5;
	}
	int lwpx = 2;
	float dx1, dx3, dy1, dy3;
	Point2f plu, pld, pru, prd;
	int offx, offy;
	if (a == 0) {
		plu.x = x - 0.8*f;
		plu.y = y;
		pld.x = x - 0.8 * f;
		pld.y = y - 0.5 * f;

		pru.x = x + 0.8 * f;
		pru.y = y;
		prd.x = x + 0.8 * f;
		prd.y = y - 0.5 * f;
	}
	else {
		plu.x = x;
		plu.y = a == 90 ? y + 0.8*f : y - 0.8 * f;
		pld.x = a == 90 ? x - 0.5 * f : x + 0.5 * f;
		pld.y = a == 90 ? y + 0.8 * f : y - 0.8 * f;

		pru.x = x;
		pru.y = a == 90 ? y - 0.8*f : y + 0.8*f;
		prd.x = a == 90 ? x - 0.5*f : x + 0.5*f;
		prd.y = a == 90 ? y - 0.8*f : y + 0.8*f;
	}
	vector<Point2f>post{ plu, pld, pru, prd };
	vector<Point2i>coord = normal_coord(post);

	string col = rgb6(BGR_CAGE);

	string linetype = " stroke-width=\"" + to_string(lwpx) + "\"";
	ss << "  <line x1 = \"" << to_string(coord[0].x) << "\" y1=\"" << to_string(coord[0].y) << "\"";
	ss << " x2 = \"" << to_string(coord[1].x) << "\" y2=\"" << to_string(coord[1].y) << "\" stroke=\"" << col << "\" " << linetype << " />" << endl;
	linetype = " stroke-width=\"" + to_string(lwpx) + "\"";
	ss << "  <line x1 = \"" << to_string(coord[2].x) << "\" y1=\"" << to_string(coord[2].y) << "\"";
	ss << " x2 = \"" << to_string(coord[3].x) << "\" y2=\"" << to_string(coord[3].y) << "\" stroke=\"" << col << "\" " << linetype << " />" << endl;
}
void Scalable::dKeeperarea(double x, double y, int a)
{
	float f = 1.0;
	if (a == 91) {
		a = 90;
		f = 1.5;
	}
	dGoalCrease(x, y, a, 2.5*f, 1.0*f);
}
void Scalable::dGoalCrease(double x, double y, int a, float wide, float depth)
{

	int lwp = 2;
	double dx1, dx2, dx3, dx4, dy1, dy2, dy3, dy4;
	vector<int>offx;
	vector<int>offy;
	if (a == 0) {
		dx1 = -wide / 2; dy1 = 0.0;
		dx2 = wide / 2;  dy2 = 0.0;
		dx3 = wide / 2;  dy3 = -depth;
		dx4 = -wide / 2; dy4 = -depth;
		offx = vector<int>{ lwp / 2, -lwp / 2, -lwp / 2, lwp / 2 };
		offy = vector<int>{ -lwp, -lwp, lwp, lwp };
	}
	else {
		dx1 = 0.0;
		dy1 = a == 90 ? wide / 2 : -wide / 2;
		dx2 = a == 90 ? 0.0 : depth;
		dy2 = -wide / 2;
		dx3 = a == 90 ? -depth : depth;
		dy3 = a == 90 ? -wide / 2 : wide / 2;
		dx4 = a == 90 ? -depth : 0.0;
		dy4 = wide / 2;

		offx = vector<int>{ a == 90 ? -lwp / 2 : lwp / 2, -lwp / 2, a == 90 ? lwp / 2 : -lwp / 2, lwp / 2 };
		offy = vector<int>{ a == 90 ? -lwp / 2 : lwp / 2, lwp / 2, a == 90 ? lwp / 2 : -lwp / 2, -lwp / 2 };
	}

	vector<Point2f>frm{ Point2f(x + dx1, y + dy1), Point2f(x + dx2, y + dy2), Point2f(x + dx3, y + dy3) , Point2f(x + dx4, y + dy4) };
	vector<Point2i>coord = normal_coord(frm);
	int ix = 0;
	for (auto& p : coord) {
		p.x += offx[ix];
		p.y += offy[ix];	//lineïù
		ix++;
	}
	string col = rgb6(BGR_START_LINE);
	svgPolygonlw(coord, col, lwp);
}
void Scalable::dGoalCageDemo(double x, double y)
{
	float f = 1.2;
	vector<Point2f>frm{ Point2f(x - f*0.8, y), Point2f(x - f*0.8, y + f*1.05), Point2f(x - f*0.8 + f*0.1, y + f*1.15), 
		Point2f(x + f*0.8 - f*0.1, y + f*1.15), Point2f(x + f * 0.8, y + f*1.05), Point2f(x + f*0.8, y) };
	vector<Point2i>coord = normal_coord(frm);
	for (auto& p : coord) {
		p.y -= f*5;	//lineïù
	}
	string col = rgb6(BGR_CAGE_DEMO);
	svgPolyline(coord, col, 5);

	vector<Point2f>tape1{ Point2f(x - f*0.8, y + f*0.35), Point2f(x + f * 0.8, y + f*0.35) };
	vector<Point2i>tcoord1 = normal_coord(tape1);
	col = rgb6(BGR_CAGE_DEMO_TAPE);
	svgLine(tcoord1[0], tcoord1[1], col, 1, 3);
	tape1 = vector<Point2f>{ Point2f(x - f * 0.35, y + f*1.15), Point2f(x - f * 0.35, y ) };
	tcoord1 = normal_coord(tape1);
	svgLine(tcoord1[0], tcoord1[1], col, 1, 3);
	tape1 = vector<Point2f>{ Point2f(x + f * 0.35, y + f * 1.15), Point2f(x + f * 0.35, y) };
	tcoord1 = normal_coord(tape1);
	svgLine(tcoord1[0], tcoord1[1], col, 1, 3);

	dMeasure(x, y + f * 1.4, f*1.6, "160cm", 0);
	dMeasureV(x + f * 1.0, y + f * 0.62, f * 1.15, "115cm", 0); // 0.575

	tape1 = vector<Point2f>{ Point2f(x - f * 1.3, y+f*0.1), Point2f(x - f * 0.8, y - f * 0.1) };
	tcoord1 = normal_coord(tape1);
	col = rgb6(BGR_MEASURE);
	svgText("30cm", tcoord1[0], col, 0);
	svgText("45cm", tcoord1[1], col, 0);

	tape1 = vector<Point2f>{ Point2f(x - f * 0.65, y + f * 0.6), Point2f(x - f*0.05, y + f * 0.6), Point2f(x + f * 0.5, y + f * 0.6),
							Point2f(x - f * 0.65, y + f * 0.07), Point2f(x - f*0.05, y + f * 0.07), Point2f(x + f * 0.5, y + f * 0.07) };
	tcoord1 = normal_coord(tape1);
	col = rgb6(BGR_SCORE);
	svgText("5", tcoord1[0], col, 2);
	svgText("2", tcoord1[1], col, 2);
	svgText("5", tcoord1[2], col, 2);
	svgText("3", tcoord1[3], col, 2);
	svgText("1", tcoord1[4], col, 2);
	svgText("3", tcoord1[5], col, 2);
}

void Scalable::dRink4x4(double x, double y, double w, double h)
{
	vector<Point2f>link{ Point2f(x - w / 2, y + h / 2), Point2f(w / 2, -h / 2),
		Point2f(x, y), Point2f(x - w / 2 + 1.85, y + h / 2 - 1.0), Point2f(x, y + h / 2 - 1.0), Point2f(x + w / 2 - 1.85, y + h / 2 - 1.0),
					  Point2f(x - w / 2 + 1.85, y - h / 2 + 1.0), Point2f(x, y - h / 2 + 1.0), Point2f(x + w / 2 - 1.85, y - h / 2 + 1.0) };
	vector<Point2i>coord = normal_coord(link);
	string col = rgb6(BGR_LINE);
	svgRink(coord[0].x, coord[0].y, coord[1].x - coord[0].x, coord[1].y - coord[0].y, col);
	dMeasure(x, y + h / 2 + h / 12, w, u8"20Å`24 m", 0);
	dMeasureV(x + w / 2 + w / 9, y, h, u8"12Å`14 m", 0);

	double gx = w / 2 - 1.85;
	double gy = y;
	dGoalCage(x + gx, y, 90);
	dKeeperarea(x + gx, y, 90);
	dGoalCage(x - gx, y, -90);
	dKeeperarea(x - gx, y, -90);

	col = rgb6(BGR_FACEOFF_DOT);
	for (int i = 2; i < coord.size(); i++)
	{
		ss << "  <circle cx=\"" << coord[i].x << "\" cy=\"" << coord[i].y << "\" r=\"5\" fill=\"" << col << "\" />" << endl;
	}
	dMeasure(x - 10 + 1.85 / 2, y + 1.5, 1.85, "1.85m", 0);
	dMeasureV(x - 10 + 2.2, y + 5.5, 1.0, "1m", 0);

	dMeasure(x + 10 - 2.35, y + 1.9, 1.0, "1m", 0);
	dMeasureV(x + 10 - 4.0, y, 2.5, "2.5m", 0);

	col = rgb6(BGR_FACEOFF_DOT);
	for (int i = 2; i < coord.size(); i++)
	{
		ss << "  <circle cx=\"" << coord[i].x << "\" cy=\"" << coord[i].y << "\" r=\"5\" fill=\"" << col << "\" />" << endl;
	}
	dMeasure(x - 10 + 1.85 / 2, y + 1.5, 1.85, "1.85m", 0);
	dMeasureV(x - 10 + 2.2, y + 5.5, 1.0, "1m", 0);

	dMeasure(x + 10 - 2.35, y + 1.9, 1.0, "1m", 0);
	dMeasureV(x + 10 - 4.0, y, 2.5, "2.5m", 0);
}
void Scalable::dRink6x6(double x, double y, double w, double h)
{
	vector<Point2f>link{ Point2f(x - w / 2, y + h / 2), Point2f(x + w / 2, -h / 2),
	Point2f(x, y), Point2f(x - w / 2 + 3.5, y + h / 2 - 1.5), Point2f(x, y + h / 2 - 1.5), Point2f(x + w / 2 - 3.5, y + h / 2 - 1.5),
		Point2f(x - w / 2 + 3.5, y - h / 2 + 1.5), Point2f(x, y - h / 2 + 1.5), Point2f(x + w / 2 - 3.5, y - h / 2 + 1.5) };
	vector<Point2i>coord = normal_coord(link);
	string col = rgb6(BGR_LINE);
	svgRink(coord[0].x, coord[0].y, coord[1].x - coord[0].x, coord[1].y - coord[0].y, col);
	dMeasure(x, y + h / 2 + h / 12, w, u8"36Å`44 m", 0);
	dMeasureV(x + w / 2 + w / 14, y, h, u8"18Å`22 m", 0);

	double gx = w / 2 - 2.85;
	double gy = y;
	dGoalCrease(x + gx, gy, 90, 5.0, 4.0);
	dGoalCrease(x - gx, gy, -90, 5.0, 4.0);

	gx = w / 2 - 3.5;
	dKeeperarea(x + gx, gy, 90);
	dKeeperarea(x - gx, gy, -90);

	dGoalPost(x + gx, gy, -90);
	dGoalPost(x - gx, gy, 90);

	col = rgb6(BGR_FACEOFF_DOT);
	for (int i = 2; i < coord.size(); i++)
	{
		ss << "  <circle cx=\"" << coord[i].x << "\" cy=\"" << coord[i].y << "\" r=\"5\" fill=\"" << col << "\" />" << endl;
	}
	dMeasureV(x - w / 2 + 4.0, y + 8.25, 1.5, "1.5m", 0);

	dMeasure(x - w / 2 + 2.85 / 2, y + 3.5, 2.85, "2.85m", 0);
	dMeasure(x - w / 2 + 4.85, y + 3.5, 4.0, "4.0m", 0);
	dMeasureV(x - w / 2 + 8.5, y, 5.0, "5.0m", 0);

	dMeasure(x - w / 2 + 3.5 / 2, y - 1.25, 3.5, "3.5m", 0);

	gx = x + w / 2 + 11.0;
	gy = y - 8.0;
	dGoalCrease(gx, gy, 90, 5.0*1.5, 4.0*1.5);
	gx -= 0.65 * 1.5;
	dKeeperarea(gx, gy, 91);

	dMeasure(gx - 0.5*1.5, gy + 2.3, 1.0*1.5, "1.0m", 0);
	dGoalPost(gx, gy, -91);
	dMeasureV(gx + 0.4, gy, 2.5*1.5, "2.5m", 0);

}
void Scalable::dRink5x5unified(double x, double y, double w, double h)
{
	vector<Point2f>link{ Point2f(x - w / 2, y + h / 2), Point2f(w / 2, -h / 2),
	Point2f(x, y), Point2f(x - w / 2 + 1.85, y + h / 2 - 1.0), Point2f(x, y + h / 2 - 1.0), Point2f(x + w / 2 - 1.85, y + h / 2 - 1.0),
				  Point2f(x - w / 2 + 1.85, y - h / 2 + 1.0), Point2f(x, y - h / 2 + 1.0), Point2f(x + w / 2 - 1.85, y - h / 2 + 1.0) };

	vector<Point2i>coord = normal_coord(link);
	string col = rgb6(BGR_LINE);
	svgRink(coord[0].x, coord[0].y, coord[1].x - coord[0].x, coord[1].y - coord[0].y, col);
	dMeasure(x, y + h / 2 + h / 12, w, u8"24Å`30 m", 0);
	dMeasureV(x + w / 2 + w / 9, y, h, u8"14Å`15 m", 0);

	double gx = w / 2 - 1.85;
	double gy = y;
	dGoalCage(x + gx, y, 90);
	dKeeperarea(x + gx, y, 90);
	dGoalCage(x - gx, y, -90);
	dKeeperarea(x - gx, y, -90);

	col = rgb6(BGR_FACEOFF_DOT);
	for (int i = 2; i < coord.size(); i++)
	{
		ss << "  <circle cx=\"" << coord[i].x << "\" cy=\"" << coord[i].y << "\" r=\"5\" fill=\"" << col << "\" />" << endl;
	}
	dMeasure(x - 12 + 1.85 / 2, y + 1.0, 1.85, "1.85m", 0);
	dMeasureV(x - 12 + 2.2, y + 6.5, 1.0, "1m", 0);

	dMeasure(x + 12 - 2.35, y + 1.9, 1.0, "1m", 0);
	dMeasureV(x + 12 - 4.0, y, 2.5, "2.5m", 0);
}

void Scalable::dBall(double x, double y, double d, double dh)
{
	double t1 = 45 * 1.5 / (180.0 / pi);
	double t2 = 45 * 0.5 / (180.0 / pi);
	float a = d * 0.42 * cos(t1);
	float b = d * 0.42 * sin(t1);
	vector<Point2f>coord{ Point2f(x, y), 
		Point2f(x, y + d / 4), Point2f(x + d / 4, y), Point2f(x, y - d / 4), Point2f(x - d / 4, y),

		Point2f(x - a, y + b), Point2f(x + a, y + b), Point2f(x + b, y + a), Point2f(x + b, y - a), Point2f(x + a, y - b), 
			Point2f(x - a, y - b), Point2f(x - b, y - a), Point2f(x - b, y + a) };
	vector<Point2i>nor = normal_coord(coord);

	ss << "  <circle cx=\"" << nor[0].x << "\" cy=\"" << nor[0].y << "\" r = \"" << normal_height(d * 0.5) << "\" fill=\"LightGreen\" />" << endl;
	ss << "  <circle cx=\"" << nor[0].x << "\" cy=\"" << nor[0].y << "\" r = \"" << normal_height(dh * 0.5) << "\" fill=\"Green\" />" << endl;

	ss << "  <circle cx=\"" << nor[1].x << "\" cy=\"" << nor[1].y << "\" r = \"" << normal_height(dh * 0.4) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[2].x << "\" cy=\"" << nor[2].y << "\" r = \"" << normal_height(dh * 0.4) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[3].x << "\" cy=\"" << nor[3].y << "\" r = \"" << normal_height(dh * 0.4) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[4].x << "\" cy=\"" << nor[4].y << "\" r = \"" << normal_height(dh * 0.4) << "\" fill=\"Green\" />" << endl;

	ss << "  <circle cx=\"" << nor[5].x << "\" cy=\"" << nor[5].y << "\" r = \"" << normal_height(dh * 0.34) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[6].x << "\" cy=\"" << nor[6].y << "\" r = \"" << normal_height(dh * 0.34) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[7].x << "\" cy=\"" << nor[7].y << "\" r = \"" << normal_height(dh * 0.34) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[8].x << "\" cy=\"" << nor[8].y << "\" r = \"" << normal_height(dh * 0.34) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[9].x << "\" cy=\"" << nor[9].y << "\" r = \"" << normal_height(dh * 0.34) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[10].x << "\" cy=\"" << nor[10].y << "\" r = \"" << normal_height(dh * 0.34) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[11].x << "\" cy=\"" << nor[11].y << "\" r = \"" << normal_height(dh * 0.34) << "\" fill=\"Green\" />" << endl;
	ss << "  <circle cx=\"" << nor[12].x << "\" cy=\"" << nor[12].y << "\" r = \"" << normal_height(dh * 0.34) << "\" fill=\"Green\" />" << endl;

}

void Scalable::wrt_field(string path)
{
	ss << endl << "</svg>" << endl;

	std::ofstream ofs(path.c_str());
	if (ofs) {
		ofs << ss.str() << endl;
	}

	cout << "write " << path << endl;
}
void Scalable::svgPolyline(const vector<Point2i>& points3, string col, int line_width)
{
	stringstream pts;

	int i = 0;
	for (Point2i p : points3)
	{
		if (i++ > 0) {
			pts << " , ";
		}
		pts << to_string(p.x) << " " << to_string(p.y);
	}
	ss << "  <polyline points=\"" << pts.str() << "\" fill=\"" << col << "\" stroke=\"" << col << "\" stroke-width=\"" << to_string(line_width) << "\" fill-opacity=\"0.0\" />" << endl;
}
void Scalable::svgPolygon(const vector<Point2i>& points3, string col, bool fill)
{
	stringstream pts;

	int i = 0;
	for (Point2i p : points3)
	{
		if (i++ > 0) {
			pts << " , ";
		}
		pts << to_string(p.x) << " " << to_string(p.y);
	}
	string lin = fill ? "" : "stroke=\"" + col + "\" stroke-width=\"1\" fill-opacity=\"0.0\""; // stroke-width=4
	ss << "  <polygon points=\"" << pts.str() << "\" fill=\"" << col << "\" " << lin << " />" << endl;
}
void Scalable::svgPolygonlw(const vector<Point2i>& points3, string col, int lw)
{
	stringstream pts;

	int i = 0;
	for (Point2i p : points3)
	{
		if (i++ > 0) {
			pts << " , ";
		}
		pts << to_string(p.x) << " " << to_string(p.y);
	}
	string lin = "stroke=\"" + col + "\" stroke-width=\"" + to_string(lw) + "\" fill-opacity=\"0.0\"";
	ss << "  <polygon points=\"" << pts.str() << "\" fill=\"" << col << "\" " << lin << " />" << endl;
}
void Scalable::svgLine(const Point2i p1, const Point2i p2, string col, int type, int linew)
{
	string linetype = type == 0 ? "" : "stroke-dasharray=\"2 3\"";
	linetype += " stroke-width=\"" + to_string(linew) + "\"";
	ss << "  <line x1 = \"" << to_string(p1.x) << "\" y1=\"" << to_string(p1.y) << "\"";
		ss << " x2 = \"" << to_string(p2.x) << "\" y2=\"" << to_string(p2.y) << "\" stroke=\"" << col << "\" " << linetype << " />" << endl;
}
void Scalable::svgText(const string cap, const Point2i pt, string col, int fontSz, double ang)
{
 	string tilt = ang == 0.0 ? "" : "transform=\"rotate(" + to_string(ang) + "," + to_string(pt.x) + "," + to_string(pt.y) + ")\"";
	string fsz = SvgFontSize[fontSz];
	ss << "  <text x=\"" << to_string(pt.x) << "\" y=\"" << to_string(pt.y) << "\" font-family=\"sans-serif\" font-size=\"" << fsz << "\" " << tilt << " fill= \"" << col << "\" >" << cap << "</text>" << endl;
}
void Scalable::svgRink(const int x, const int y, const int w, const int h, string col)
{
	int rx = h / 11;
	ss << "  <rect x=\"" << x << "\" y=\"" << y << "\" rx=\"40\" ry=\"40\" width=\"" << w << "\" height=\"" << h << "\" fill=\"none\" stroke=\"" << col << "\" stroke-width=\"3\" />" << endl;
}

string Scalable::rgb6(const vector<int>& bgr, string prefix)
{
	std::ostringstream ssCol;
	ssCol << std::setfill('0') << std::setw(2) << std::hex << bgr[2]; // R
	ssCol << std::setfill('0') << std::setw(2) << std::hex << bgr[1]; // G
	ssCol << std::setfill('0') << std::setw(2) << std::hex << bgr[0]; // B

	std::string s = prefix + ssCol.str();

	return s;
}

