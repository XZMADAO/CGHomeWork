#pragma once

#include <QtWidgets/QWidget>
#include "ui_BigProject.h"
#include "ui_NewCanvas.h"


#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<fstream>
#include<sstream>
#include<iterator>
#include <algorithm>
#include <QPainter>
#include<qpoint.h>
#include<QMouseEvent>
#include<QTextStream>
#include<qtimer.h>
#include<qbuffer.h>
#include<qmessagebox.h>
#include<qstylefactory.h>
#include<qpixmap.h>
#include<qpainter.h>
#include<qdebug.h>
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
struct CurvePoint
{
	double x;
	double y;
};
struct CanvasData
{
	int width;
	int height;
};

class UseForPaint
{
public :
	friend class BigProject;
	friend class LineEdit;
	friend class EllipseEdit;
	friend class PolygonEdit;
public:
	int IDcount;
	CanvasData cd;
	QPixmap* drawingmap;
	QPixmap* qmap;
	QPainter* qpainter;
	QPainter* drawingpainter;
	QColor* qcolor;
	vector<PainterData>pd;
};










class NewCanvas : public QWidget
{
	Q_OBJECT

public:
	NewCanvas(QWidget *parent = Q_NULLPTR);
	~NewCanvas();
private slots:
	void CreateCanvasData();
	void CloseWin();
signals:
	void SendCanvasData(int width, int length);

private:
	Ui::NewCanvas ui;

};




class BigProject : public QWidget
{
	Q_OBJECT

public:


	BigProject(QWidget *parent = Q_NULLPTR);
	NewCanvas *nc;
private slots:
	//void ClickPolygon();
	void CreateNewCanvasDialog();

	void CreateCanvas(int width, int length);
	void SaveCanvas();
	void SetColor();
	void CreateDDALine(float x1, float y1, float x2, float y2, int choose,int index);
	void CreateBresenham(float x1, float y1, float x2, float y2, int choose,int index);
	void CreateDDAPolygon(int id, int pointcount, vector<int> point);
	void CreateBresenhamPolygon(int id, int pointcount, vector<int> point);
	void CreateElipse(int choose, int x, int y, int rx, int ry,int index);
	vector<CurvePoint> CreateBezierCurve(vector<CurvePoint> point);
	void Translate(int id, int dx, int dy);
	void ClipCohen(int id, int x1, int y1, int x2, int y2);



	//void Rotate(int id, int x, int y, int r);
private:
	bool IsPress;
	/* For Line */
	QPoint StartPoint;
	QPoint LastPoint;
	/* For Ellipse */
	QPoint Centre;
	float RadiusX;
	float RadiusY;
	/* For Polygon*/
	bool IsFirst;
	QPoint FirstStartPoint;
	/* For Curve*/
	vector<CurvePoint> curpoint;
	/*For Translate*/
	int OffsetX;
	int OffsetY;
	int ChooseID;
	vector<int>ClipId;

	void mousePressEvent(QMouseEvent *e);

	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void paintEvent(QPaintEvent *e);
	void SetFourPoint(int x1, int y1, int x, int y,int choose,int index);
	int FindID(QMouseEvent *e);
	vector<int> FindIDs(int x1,int y1,int x2,int y2);
	bool IsinMap(QMouseEvent *e);

	Ui::BigProjectClass ui;
};

extern UseForPaint ufp;
