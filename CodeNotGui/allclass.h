#pragma once
#pragma once
#include <QtCore/QCoreApplication>
#include<qapplication.h>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iterator>
#include <algorithm>
#include<math.h>
#include<QTextStream>
#include<qbuffer.h>
#include<qmessagebox.h>
#include<qstylefactory.h>
#include<qpixmap.h>
#include<qpainter.h>
#include<qinputdialog.h>
#include<qfiledialog.h>
#include<qtextcodec.h>
using namespace std;
#define LineType 1
#define EllipseType 2
#define PolygonType 3
#define CurveType 4
struct Color
{
	int r;
	int g;
	int b;
};
struct CurvePoint
{
	double x;
	double y;
};

struct PainterData
{
	int id;
	int type;
	int pointcount;
	string algorithm;
	vector<float> point;
	vector<int> allpointx;
	vector<int> allpointy;
	vector<int>radius;
	Color color;
};

struct CanvasData
{
	int width;
	int height;
};

class UseForPaint
{

public:
	CanvasData cd;
	QPixmap* qmap;
	QPainter* qpainter;
	QColor* qcolor;
	vector<PainterData>pd;
	vector<vector<string>> order;
};

class PaintFunction: public QWidget
{
public:
	void SplitOrder(char *filename);
	void UseOrder();
	void CreateCanvas(int width, int length);
	void SaveCanvas(string name);
	void SetColor(int r, int g, int b);
	void CreateDDALine(float x1, float y1, float x2, float y2,int index);
	void CreateBresenham(float x1, float y1, float x2, float y2,int index);
	void CreateDDAPolygon(int pointcount, vector<int> point,int index);
	void CreateBresenhamPolygon(int pointcount, vector<int> point,int index);
	void CreateElipse(int x, int y, int rx, int ry,int index);
	void SetFourPoint(int x1, int y1, int x, int y,int index);
	vector<CurvePoint> CreateBezierCurve(vector<CurvePoint> point,int index);
	vector<CurvePoint> CreateBSplineCurve(vector<CurvePoint> point, int index);


	void Translate(int id, int dx, int dy);
	void Rotate(int id, int x, int y, int r);
	void Scale(int id, int x, int y, int s);
	void ClipCohen(int id, int x1, int y1, int x2, int y2);
	void ClipLiang(int id, int x1, int y1, int x2, int y2);
	
};
extern UseForPaint ufp;