#include "BigProject.h"

BigProject::BigProject(QWidget *parent)
	: QWidget(parent)
{


	ui.setupUi(this);
	nc = new NewCanvas();
	connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(CreateNewCanvasDialog()));
	connect(ui.pushButton_2, SIGNAL(clicked(bool)), this, SLOT(SaveCanvas()));
	connect(ui.pushButton_7, SIGNAL(clicked(bool)), this, SLOT(SetColor()));
	connect(nc, SIGNAL(SendCanvasData(int,int)), this, SLOT(CreateCanvas(int,int)));
	/*Map Init*/
	ufp.IDcount = 0;
	ufp.qmap = new QPixmap(640, 480);
	ufp.drawingmap = new QPixmap(640, 480);
	ufp.drawingmap->fill(Qt::transparent);
	ufp.qpainter = new QPainter(ufp.qmap);
	ufp.drawingpainter = new QPainter(ufp.drawingmap);
	ufp.qpainter->fillRect(0, 0, 640, 480, Qt::white);
	ufp.qcolor = new QColor(0, 0, 0);
	ufp.cd.width = 640;
	ufp.cd.height = 480;
	if (640 > ui.label->width() || 480 > ui.label->height())
	{
		ui.label->setGeometry(10, 100, 640, 480);
	}
	if (640 > ui.label_5->width() || 480 > ui.label_5->height())
	{
		ui.label_5->setGeometry(10, 100, 640, 480);
	}
	ui.label->setPixmap(*ufp.qmap);
	ui.label_5->setPixmap(*ufp.drawingmap);
	ufp.qcolor = new QColor(0, 0, 0);
	IsPress = false;
	StartPoint.setX(-1);
	IsFirst = false;
}
void BigProject::CreateNewCanvasDialog()
{
	nc->show();
}


void BigProject::CreateCanvas(int width, int length)
{
	ufp.pd.clear();
	ufp.qmap = new QPixmap(width, length);
	ufp.drawingmap = new QPixmap(width, length);
	ufp.drawingmap->fill(Qt::transparent);
	ufp.qpainter = new QPainter(ufp.qmap);
	ufp.drawingpainter = new QPainter(ufp.drawingmap);
	ufp.qpainter->fillRect(0, 0, width, length, Qt::white);
	
	ufp.qcolor = new QColor(0, 0, 0);
	ufp.cd.width = width;
	ufp.cd.height = length;
	if (width > ui.label->width() || length > ui.label->height())
	{
		ui.label->setGeometry(10, 100, width, length);
	}
	if (width > ui.label_5->width() || length > ui.label_5->height())
	{
		ui.label_5->setGeometry(10, 100, width, length);
	}
	ui.label->setPixmap(*ufp.qmap);
	ui.label_5->setPixmap(*ufp.drawingmap);
}

void BigProject::SaveCanvas()
{
	QString SaveName = ui.lineEdit->text();
	if (SaveName.toStdString() == "")
	{
		QMessageBox::warning(NULL, tr("Warning"), QString("SaveName is empty!"));
		ui.lineEdit->clear();
		return;
	}
	SaveName = SaveName + ".bmp";
	QFile file(SaveName);
	if(!file.open(QFile::WriteOnly))
	{
		QMessageBox::warning(NULL, tr("Warning"), QString("Failed to open file!"));
		ui.lineEdit->clear();
		return;
	}
	QTextStream qt(&file);
	QByteArray qba;
	QBuffer qb(&qba);
	qb.open(QIODevice::WriteOnly);
	ufp.qmap->save(&qb, "BMP");
	file.write(qba);
	ui.lineEdit->clear();

}


void BigProject::SetColor()
{
	QString sr = ui.lineEdit_2->text();
	QString sg = ui.lineEdit_3->text();
	QString sb = ui.lineEdit_4->text();
	if (sr.toStdString() == "")
	{
		QMessageBox::warning(NULL, tr("Warning"), QString("R is empty!"));
		ui.lineEdit_2->clear();
		ui.lineEdit_3->clear();
		ui.lineEdit_4->clear();
		return;
	}
	if (sg.toStdString() == "")
	{
		QMessageBox::warning(NULL, tr("Warning"), QString("G is empty!"));
		ui.lineEdit_2->clear();
		ui.lineEdit_3->clear();
		ui.lineEdit_4->clear();
		return;
	}
	if (sb.toStdString() == "")
	{
		QMessageBox::warning(NULL, tr("Warning"), QString("B is empty!"));
		ui.lineEdit_2->clear();
		ui.lineEdit_3->clear();
		ui.lineEdit_4->clear();
		return;
	}
	int int_sr = sr.toInt();
	int int_sg = sg.toInt();
	int int_sb = sb.toInt();
	*ufp.qcolor = QColor(int_sr, int_sg, int_sb);
	ufp.qpainter->setPen(*ufp.qcolor);
	ufp.drawingpainter->setPen(*ufp.qcolor);
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.lineEdit_4->clear();

}



void BigProject::CreateDDALine(float x1, float y1, float x2, float y2, int choose,int index)
{
	float m;
	m = (y2 - y1) / (x2 - x1);
	if (abs(m) <= 1)
	{
		if (x1 > x2)
		{
			swap(x1, x2);
			swap(y1, y2);
		}
		if (choose == 0)
			ufp.drawingpainter->drawPoint((int)x1, (int)y1);
		else
		{
			ufp.qpainter->drawPoint((int)x1, (int)y1);
			ufp.pd[index].allpointx.push_back((int)x1);
			ufp.pd[index].allpointy.push_back((int)y1);
		}
		float yk = y1;
		for (int xk = (int)x1 + 1; xk <= (int)x2; xk++)
		{
			yk = yk + m;
			if(choose==0)
				ufp.drawingpainter->drawPoint(xk, (int)(yk+0.5));
			else
			{
				ufp.qpainter->drawPoint(xk, (int)(yk + 0.5));
				ufp.pd[index].allpointx.push_back((int)xk);
				ufp.pd[index].allpointy.push_back((int)(yk + 0.5));
			}
		}
	}
	else
	{
		if (y1 > y2)
		{
			swap(x1, x2);
			swap(y1, y2);
		}
		if (choose == 0)
			ufp.drawingpainter->drawPoint((int)x1, (int)y1);
		else
		{
			ufp.qpainter->drawPoint((int)x1, (int)y1);
			ufp.pd[index].allpointx.push_back((int)x1);
			ufp.pd[index].allpointy.push_back((int)y1);
		}
		float xk = x1;
		for (int yk = (int)y1 + 1; yk <= (int)y2; yk++)
		{
			xk = xk + 1/m;
			if (choose == 0)
				ufp.drawingpainter->drawPoint((int)(xk + 0.5), (int)yk);
			else
			{
				ufp.qpainter->drawPoint((int)(xk + 0.5), (int)yk);
				ufp.pd[index].allpointx.push_back((int)(xk + 0.5));
				ufp.pd[index].allpointy.push_back((int)yk);
			}
		}
	}

	if (choose == 0)
		ui.label_5->setPixmap(*ufp.drawingmap);
	else
		ui.label->setPixmap(*ufp.qmap);
}

void BigProject::CreateBresenham(float x1, float y1, float x2, float y2, int choose,int index)
{
	if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}
	float m = (y2 - y1) / (x2 - x1);
	int deltax = abs(x2 - x1);
	int deltay = abs(y2 - y1);
	int p;
	if (abs(m) <= 1)
	{
		p =2 * deltay - deltax;
		if(choose==0)
		ufp.drawingpainter->drawPoint((int)x1, (int)y1);
		else
		{
			ufp.qpainter->drawPoint((int)x1, (int)y1);
			ufp.pd[index].allpointx.push_back((int)x1);
			ufp.pd[index].allpointy.push_back((int)y1);
		}
		int yk = y1;
		for (int xk = (int)x1 + 1; xk <= (int)x2; xk++)
		{
			if (p < 0)
			{
				if(choose==0)
					ufp.drawingpainter->drawPoint(xk, yk);
				else
				{
					ufp.qpainter->drawPoint(xk, yk);
					ufp.pd[index].allpointx.push_back((int)xk);
					ufp.pd[index].allpointy.push_back((int)yk);
				}
				p = p + 2 * deltay;
			}
			else
			{
				if (m > 0)
					yk = yk + 1;

				else
					yk = yk - 1;
				if(choose==0)
					ufp.drawingpainter->drawPoint(xk, yk);
				else
				{
					ufp.qpainter->drawPoint(xk, yk);
					ufp.pd[index].allpointx.push_back((int)xk);
					ufp.pd[index].allpointy.push_back((int)yk);
				}
				p = p + 2 * deltay - 2 * deltax;
			}
		}
	}
	else
	{
		if (y2 < y1) 
		{ 
			swap(x1, x2); swap(y1, y2); 
		}
		p = 2 * deltax - deltay;
		if(choose==0)
			ufp.drawingpainter->drawPoint((int)x1, (int)y1);
		else
		{
			ufp.qpainter->drawPoint((int)x1, (int)y1);
			ufp.pd[index].allpointx.push_back((int)x1);
			ufp.pd[index].allpointy.push_back((int)y1);
		}
		int xk = x1;
		for (int yk = (int)y1 + 1; yk <= (int)y2; yk++)
		{
			if (p < 0)
			{
				if(choose==0)
					ufp.drawingpainter->drawPoint(xk, yk);
				else
				{
					ufp.qpainter->drawPoint(xk, yk);
					ufp.pd[index].allpointx.push_back((int)xk);
					ufp.pd[index].allpointy.push_back((int)yk);
				}
				p = p + 2 * deltax;
			}
			else
			{
				if (m > 0)
					xk = xk + 1;
				else
					xk = xk - 1;
				if(choose==0)
					ufp.qpainter->drawPoint(xk, yk);
				else
				{
					ufp.qpainter->drawPoint(xk, yk);
					ufp.pd[index].allpointx.push_back((int)xk);
					ufp.pd[index].allpointy.push_back((int)yk);
				}
				p = p + 2 * deltax - 2 * deltay;
			}
		}
	}
	if (choose == 0)
		ui.label_5->setPixmap(*ufp.drawingmap);
	else
		ui.label->setPixmap(*ufp.qmap);
}


void BigProject::CreateDDAPolygon(int id, int pointcount, vector<int> point)
{
	for (int i = 0; i < pointcount; i++)
	{
		float x1 = (float)point[i * 2];
		float y1 = (float)point[i * 2 + 1];
		float x2 = (float)point[(i * 2 + 2) % (2 * pointcount)];
		float y2 = (float)point[(i * 2 + 3) % (2 * pointcount)];
		CreateDDALine(x1, y1, x2, y2, id,0);
	}

}

void BigProject::CreateBresenhamPolygon(int id, int pointcount, vector<int> point)
{
	for (int i = 0; i < pointcount; i++)
	{
		float x1 = (float)point[i * 2];
		float y1 = (float)point[i * 2 + 1];
		float x2 = (float)point[(i * 2 + 2) % (2 * pointcount)];
		float y2 = (float)point[(i * 2 + 3) % (2 * pointcount)];
		CreateBresenham(x1, y1, x2, y2, id,0);
	}
}

void BigProject::CreateElipse(int choose, int x, int y, int rx, int ry,int index)
{
	double sqa = rx * rx;
	double sqb = ry * ry;
	double p = sqb + sqa * (0.25 - ry);
	int xi = 0;
	int yi = ry;
	if(choose==0)
		SetFourPoint(x, y, xi, yi,0,-1);
	else
		SetFourPoint(x, y, xi, yi, 1,index);
	while( sqb*(xi + 1) < sqa*(yi - 0.5))
	{
		if (p < 0)
		{
			p = p + sqb * (2 * xi + 3);
		}
		else
		{
			p = p + (sqb*(2 * xi + 3) + sqa * ((-2)*yi + 2));
			yi--;
		}
		xi++;
		if (choose == 0)
			SetFourPoint(x, y, xi, yi, 0,-1);
		else
			SetFourPoint(x, y, xi, yi, 1,index);
	}
	//p = sqb * (xi + 1 / 2)*(xi + 1 / 2) + sqa * (yi - 1) - sqa * sqb;
	p = (ry*(xi + 0.5)) * 2 + (rx*(yi - 1)) * 2 - (rx*ry) * 2;
	while(yi>0)
	{
		if (p >= 0)
		{
			p = p + sqa * ((-2)*yi + 3);
		}
		else
		{
			p = p + sqb * (2 * xi + 2) + sqa * ((-2)*yi + 3);
			xi++;
		}
		yi--;
		if (choose == 0)
			SetFourPoint(x, y, xi, yi, 0,-1);
		else
			SetFourPoint(x, y, xi, yi, 1,index);
	}
	if (choose == 1)
		ui.label->setPixmap(*ufp.qmap);
	else
		ui.label_5->setPixmap(*ufp.drawingmap);
}

vector<CurvePoint>BigProject:: CreateBezierCurve(vector<CurvePoint> point)
{
	if (point.size() < 1)
		return point;
	float step = 0.01;
	vector<CurvePoint> respoint;
	if (point.size() == 1)
	{
		for (float t = 0; t < 1; t += step)
			respoint.push_back(point[0]);
		return respoint;
	}
	vector<CurvePoint> point1;
	vector<CurvePoint> point2;
	point1.assign(point.begin(), point.end() - 1);
	point2.assign(point.begin() + 1, point.end());

	vector<CurvePoint> ppoint1 = CreateBezierCurve(point1);
	vector<CurvePoint> ppoint2 = CreateBezierCurve(point2);
	for (float t = 0; t < 1; t += step) {
		CurvePoint temp;
		temp.x = (1.0 - t) * ppoint1[(int)(1.0 / step * t + 0.5)].x + t * ppoint2[(int)(1.0 / step * t + 0.5)].x;
		temp.y = (1.0 - t) * ppoint1[(int)(1.0 / step * t + 0.5)].y + t * ppoint2[(int)(1.0 / step * t + 0.5)].y;
		respoint.push_back(temp);
	}
	return respoint;
}

void BigProject::Translate(int id, int dx, int dy)
{
	int i;
	for (i = 0; i < ufp.pd.size(); i++)
	{
		if (ufp.pd[i].id == id)
			break;
	}
	ufp.qpainter->fillRect(0, 0, ufp.cd.width, ufp.cd.height, Qt::white);
	for (int k = 0; k < ufp.pd[i].allpointx.size(); k++)
	{
		ufp.pd[i].allpointx[k] += dx;
		ufp.pd[i].allpointy[k] += dy;
	}
	for (int k = 0; k < ufp.pd[i].point.size(); k++)
	{
		if (k % 2 == 0)
			ufp.pd[i].point[k] += dx;
		else
			ufp.pd[i].point[k] += dy;
	}
	for (int j = 0; j < ufp.pd.size(); j++)
	{
		QColor tempColor = QColor(ufp.pd[j].color.r, ufp.pd[j].color.g, ufp.pd[j].color.b);
		ufp.qpainter->setPen(tempColor);
		for (int k = 0; k < ufp.pd[j].allpointx.size(); k++)
			ufp.qpainter->drawPoint(ufp.pd[j].allpointx[k], ufp.pd[j].allpointy[k]);

	}
	ufp.qpainter->setPen(*ufp.qcolor);
	ui.label->setPixmap(*ufp.qmap);
}

void BigProject::ClipCohen(int id, int x1, int y1, int x2, int y2)
{
	vector<bool>area1;
	vector<bool>area2;
	vector<bool>area3;
	vector<bool>area4;
	int i;
	for (i = 0; i < ufp.pd.size(); i++)
	{
		if (ufp.pd[i].id == id)
			break;
	}
	ufp.qpainter->fillRect(0, 0, ufp.cd.width, ufp.cd.height, Qt::white);
	for (int k = 0; k < ufp.pd[i].allpointx.size(); k++)
	{
		int xk = ufp.pd[i].allpointx[k];
		int yk = ufp.pd[i].allpointy[k];
		if (yk > y2)
			area1.push_back(true);
		else
			area1.push_back(false);
		if (yk < y1)
			area2.push_back(true);
		else
			area2.push_back(false);
		if (xk < x1)
			area3.push_back(true);
		else
			area3.push_back(false);
		if (xk > x2)
			area4.push_back(true);
		else
			area4.push_back(false);
	}
	for (int j = 0; j < ufp.pd.size(); j++)
	{
		QColor tempColor = QColor(ufp.pd[j].color.r, ufp.pd[j].color.g, ufp.pd[j].color.b);
		ufp.qpainter->setPen(tempColor);
		if (j == i)
		{
			vector<int>tempx;
			vector<int>tempy;
			for (int k = 0; k < ufp.pd[i].allpointx.size(); k++)
			{
				int xk = ufp.pd[i].allpointx[k];
				int yk = ufp.pd[i].allpointy[k];
				if (!area1[k] && !area2[k] && !area3[k] && !area4[k])
				{
					tempx.push_back(xk);
					tempy.push_back(yk);
					ufp.qpainter->drawPoint(xk, yk);
				}
			}
			ufp.pd[i].allpointx.clear();
			ufp.pd[i].allpointy.clear();
			for (int v = 0; v < tempx.size(); v++)
			{
				if (v == 0)
				{
					ufp.pd[i].point[0] = tempx[v];
					ufp.pd[i].point[1] = tempy[v];
				}
				if (v == tempx.size() - 1)
				{
					ufp.pd[i].point[2] = tempx[v];
					ufp.pd[i].point[3] = tempy[v];
				}
				ufp.pd[i].allpointx.push_back(tempx[v]);
				ufp.pd[i].allpointy.push_back(tempy[v]);
			}
		}
		else
		{
			for (int k = 0; k < ufp.pd[j].allpointx.size(); k++)
				ufp.qpainter->drawPoint(ufp.pd[j].allpointx[k], ufp.pd[j].allpointy[k]);
		}
	}
	ufp.qpainter->setPen(*ufp.qcolor);
	ui.label->setPixmap(*ufp.qmap);
}




void BigProject::SetFourPoint(int x1, int y1, int x, int y,int choose,int index)
{
	if(choose==1)
	{
		ufp.qpainter->drawPoint((x1 + x), (y1 + y));
		ufp.pd[index].allpointx.push_back(x1 + x);
		ufp.pd[index].allpointy.push_back(y1 + y);
		ufp.qpainter->drawPoint((x1 + x), (y1 - y));
		ufp.pd[index].allpointx.push_back(x1 + x);
		ufp.pd[index].allpointy.push_back(y1 - y);
		ufp.qpainter->drawPoint((x1 - x), (y1 + y));
		ufp.pd[index].allpointx.push_back(x1 - x);
		ufp.pd[index].allpointy.push_back(y1 + y);
		ufp.qpainter->drawPoint((x1 - x), (y1 - y));
		ufp.pd[index].allpointx.push_back(x1 - x);
		ufp.pd[index].allpointy.push_back(y1 - y);
	}
	else
	{
		ufp.drawingpainter->drawPoint((x1 + x), (y1 + y));
		ufp.drawingpainter->drawPoint((x1 + x), (y1 - y));
		ufp.drawingpainter->drawPoint((x1 - x), (y1 + y));
		ufp.drawingpainter->drawPoint((x1 - x), (y1 - y));
	}
}


bool BigProject::IsinMap(QMouseEvent*e)
{
	int posx = e->pos().x();
	int posy = e->pos().y();
	if (posx > 10 + ufp.cd.width)
		return false;
	if (posy > 100 + ufp.cd.height)
		return false;
	return true;
}

int BigProject::FindID(QMouseEvent *e)
{

	int posx = e->pos().x()-10;
	int posy = e->pos().y()-100;
	int id=0;
	int mindis=99999999;
	/*
	queue<int> pointx;
	queue<int> pointy;
	queue<int> count;
	pointx.push(posx);
	pointy.push(posy);
	count.push(counttime);
	Color[posx - 10][posy - 100] = true;
	while (pointx.size() != 0)
	{
		int tempcount = count.front();
		posx = pointx.front();
		posy = pointy.front();
		count.pop();
		pointx.pop();
		pointy.pop();
		for (int j = 0; j < ufp.pd.size(); j++)
		{
			for (int k = 0; k < ufp.pd[j].allpointx.size(); k++)
			{
				if (posx == ufp.pd[j].allpointx[k]&&posy==ufp.pd[j].allpointy[k])
					return ufp.pd[j].id;
			}
		}

		int tempposx1 = posx + 1, temposy1 = posy + 1;
		if (!Color[tempposx1-10][temposy1-100]&&tempcount<20)
		{
			pointx.push(tempposx1);
			pointy.push(temposy1);
			count.push(tempcount + 1);
			Color[tempposx1-10][temposy1-100] = true;
		}
		int tempposx2 = posx + 1, temposy2 = posy + 0;
		if (!Color[tempposx2-10][temposy2-100] && tempcount < 20)
		{
			pointx.push(tempposx2);
			pointy.push(temposy2);
			count.push(tempcount + 1);
			Color[tempposx2-10][temposy2-100] = true;
		}
		int tempposx3 = posx + 1, temposy3 = posy - 1;
		if (!Color[tempposx3-10][temposy3-100] && tempcount < 20)
		{
			pointx.push(tempposx3);
			pointy.push(temposy3);
			count.push(tempcount + 1);
			Color[tempposx3-10][temposy3-100] = true;
		}
		int tempposx4 = posx + 0, temposy4 = posy - 1;
		if (!Color[tempposx4 -10][temposy4 -100] && tempcount < 20)
		{
			pointx.push(tempposx4);
			pointy.push(temposy4);
			count.push(tempcount + 1);
			Color[tempposx4-10][temposy4-100] = true;
		}
		int tempposx5 = posx - 1, temposy5 = posy - 1;
		if (!Color[tempposx5-10][temposy5-100] && tempcount < 20)
		{
			pointx.push(tempposx5);
			pointy.push(temposy5);
			count.push(tempcount + 1);
			Color[tempposx5-10][temposy5-100] = true;
		}
		int tempposx6 = posx - 1, temposy6 = posy + 0;
		if (!Color[tempposx6-10][temposy1-100] && tempcount < 20)
		{
			pointx.push(tempposx6);
			pointy.push(temposy6);
			count.push(tempcount + 1);
			Color[tempposx6-10][temposy6-100] = true;
		}
		int tempposx7 = posx - 1, temposy7 = posy + 1;
		if (!Color[tempposx7-10][temposy7-100] && tempcount < 20)
		{
			pointx.push(tempposx7);
			pointy.push(temposy7);
			count.push(tempcount + 1);
			Color[tempposx7-10][temposy7-100] = true;
		}
		int tempposx8 = posx + 0, temposy8 = posy + 1;
		if (!Color[tempposx8-10][temposy8-100] && tempcount < 20)
		{
			pointx.push(tempposx8);
			pointy.push(temposy8);
			count.push(tempcount + 1);
			Color[tempposx8-10][temposy8-100] = true;
		}
	}
	*/
	for (int j = 0; j < ufp.pd.size(); j++)
	{
		for (int k = 0; k < ufp.pd[j].allpointx.size(); k++)
		{
			int dis = pow((ufp.pd[j].allpointx[k] - posx), 2) + pow((ufp.pd[j].allpointy[k] - posy), 2);
			if (dis < mindis)
			{
				id = ufp.pd[j].id;
				mindis = dis;
			}
		}
	}
	return id;
}
/*Paint Test*/

void BigProject::paintEvent(QPaintEvent *e)
{

	if (ui.pushButton_3->isChecked())
	{
		if (IsPress&&StartPoint.x() > 0)
		{
			ufp.drawingmap->fill(Qt::transparent);
			ui.label_5->setPixmap(*ufp.drawingmap);
			CreateDDALine(StartPoint.x(), StartPoint.y(), LastPoint.x(), LastPoint.y(), 0, -1);
		}
	}
	if (ui.pushButton_5->isChecked())
	{
		if (IsPress&&StartPoint.x() > 0)
		{
			ufp.drawingmap->fill(Qt::transparent);
			ui.label_5->setPixmap(*ufp.drawingmap);
			CreateElipse(0, Centre.x(), Centre.y(), RadiusX, RadiusY,-1);
		}
	}
	if (ui.pushButton_4->isChecked())
	{
		if (IsPress&&StartPoint.x() > 0)
		{
			ufp.drawingmap->fill(Qt::transparent);
			ui.label_5->setPixmap(*ufp.drawingmap);
			CreateDDALine(StartPoint.x(), StartPoint.y(), LastPoint.x(), LastPoint.y(), 0, -1);
		}
	}
	if (ui.pushButton_6->isChecked())
	{
		if (IsPress)
		{
			if (curpoint.size() >= 2)
			{
				ufp.drawingmap->fill(Qt::transparent);
				ui.label_5->setPixmap(*ufp.drawingmap);
				QColor tempColor = QColor(0, 255, 255);
				ufp.drawingpainter->setPen(tempColor);

				for (int k = 0; k < curpoint.size() - 1; k++)
				{
					CreateDDALine(curpoint[k].x, curpoint[k].y, curpoint[k + 1].x, curpoint[k + 1].y, 0,-1);
				}
				ufp.drawingpainter->setPen(*ufp.qcolor);
				vector<CurvePoint>respoint = CreateBezierCurve(curpoint);
				for (int k = 0; k < respoint.size() - 1; k++)
				{
					CurvePoint temppoint1 = respoint[k];
					CurvePoint temppoint2 = respoint[k + 1];
					CreateDDALine((int)temppoint1.x, (int)temppoint1.y, (int)temppoint2.x, (int)temppoint2.y, 0,-1);

				}
			}
		}
	}
	if (ui.pushButton_9->isChecked())
	{
		if (IsPress)
		{
			int w = LastPoint.x() - StartPoint.x();
			int h  = LastPoint.y() - StartPoint.y();
			ufp.drawingmap->fill(Qt::transparent);
			ui.label_5->setPixmap(*ufp.drawingmap);
			QColor tempColor = QColor(0, 255, 255);
			ufp.drawingpainter->setPen(tempColor);
			ufp.drawingpainter->drawRect(StartPoint.x(), StartPoint.y(),w,h);
			ui.label_5->setPixmap(*ufp.drawingmap);
		}
	}
}




void BigProject::mousePressEvent(QMouseEvent *e)
{
	if (ui.pushButton_3->isChecked())
	{
		StartPoint = e->pos();
		LastPoint = e->pos();
		StartPoint.setX(StartPoint.x() - 10);
		StartPoint.setY(StartPoint.y() - 100);
		LastPoint.setX(LastPoint.x() - 10);
		LastPoint.setY(LastPoint.y() - 100);
		IsPress = true;
		update();
	}
	if (ui.pushButton_5->isChecked())
	{
		StartPoint = e->pos();
		LastPoint = e->pos();
		StartPoint.setX(StartPoint.x() - 10);
		StartPoint.setY(StartPoint.y() - 100);
		LastPoint.setX(LastPoint.x() - 10);
		LastPoint.setY(LastPoint.y() - 100);
		IsPress = true;
		Centre.setX(abs((LastPoint.x() + StartPoint.x())) / 2);
		Centre.setY(abs((LastPoint.y() + StartPoint.y())) / 2);
		RadiusX = abs((LastPoint.x() - StartPoint.x())) / 2;
		RadiusY = abs((LastPoint.y() - StartPoint.y())) / 2;
		update();

	}
	if (ui.pushButton_4->isChecked())
	{
		if (e->button()== Qt::LeftButton)
		{
			if (!IsFirst)
			{
				StartPoint = e->pos();
				LastPoint = e->pos();
				StartPoint.setX(StartPoint.x() - 10);
				StartPoint.setY(StartPoint.y() - 100);
				LastPoint.setX(LastPoint.x() - 10);
				LastPoint.setY(LastPoint.y() - 100);
				FirstStartPoint = StartPoint;
				IsPress = true;
				update();
			}
			else
			{
				LastPoint = e->pos();
				LastPoint.setX(LastPoint.x() - 10);
				LastPoint.setY(LastPoint.y() - 100);
				IsPress = true;
				update();
			}
		}
	}
	if (ui.pushButton_6->isChecked())
	{
		if (e->button() == Qt::LeftButton)
		{
			CurvePoint temppoint;
			temppoint.x = e->pos().x() - 10;
			temppoint.y = e->pos().y() - 100;
			curpoint.push_back(temppoint);
			IsPress = true;
			update();
		}
	}
	if (ui.pushButton_8->isChecked())
	{
		if (e->button() == Qt::LeftButton)
		{
			StartPoint = e->pos();
			LastPoint = e->pos();
			StartPoint.setX(StartPoint.x() - 10);
			StartPoint.setY(StartPoint.y() - 100);
			LastPoint.setX(LastPoint.x() - 10);
			LastPoint.setY(LastPoint.y() - 100);
			OffsetX = LastPoint.x() - StartPoint.x();
			OffsetY = LastPoint.y() - StartPoint.y();
			IsPress = true;
			update();
		}
		if (e->button() == Qt::RightButton)
		{
			ufp.drawingmap->fill(Qt::transparent);
			ui.label_5->setPixmap(*ufp.drawingmap);
			ChooseID = FindID(e);
			ufp.drawingpainter->setPen(QPen(*ufp.qcolor, 2));
			for (int i = 0; i < ufp.pd.size(); i++)
			{
				if (ufp.pd[i].id == ChooseID)
				{
					for (int j = 0; j < ufp.pd[i].allpointx.size(); j++)
					{
						ufp.drawingpainter->drawPoint(ufp.pd[i].allpointx[j],ufp.pd[i].allpointy[j]);
					}
				}
			}
			ui.label_5->setPixmap(*ufp.drawingmap);
		}
	}
	if (ui.pushButton_9->isChecked())
	{
		if (e->button() == Qt::LeftButton)
		{
			StartPoint = e->pos();
			LastPoint = e->pos();
			StartPoint.setX(StartPoint.x() - 10);
			StartPoint.setY(StartPoint.y() - 100);
			LastPoint.setX(LastPoint.x() - 10);
			LastPoint.setY(LastPoint.y() - 100);
			IsPress = true;
			update();
		}
	}
	if (ui.pushButton_10->isChecked())
	{

	}
}
void BigProject::mouseMoveEvent(QMouseEvent *e)
{
	int eposx = e->pos().x();
	int eposy = e->pos().y();
	if (IsinMap(e))
	{
		QString posstate = "Map:" + QString::number(ufp.cd.width) + "*"
			+ QString::number(ufp.cd.height) + " MousePos: " + "(" + QString::number(eposx) + "," + QString::number(eposy) + ")";
		ui.label_7->setText(posstate);
	}
	if (ui.pushButton_3->isChecked())
	{
		if (IsPress)
		{
			LastPoint = e->pos();
			LastPoint.setX(LastPoint.x() - 10);
			LastPoint.setY(LastPoint.y() - 100);
			update();
		}
	}
	if (ui.pushButton_5->isChecked())
	{
		if (IsPress)
		{
			LastPoint = e->pos();
			LastPoint.setX(LastPoint.x() - 10);
			LastPoint.setY(LastPoint.y() - 100);
			Centre.setX(abs((LastPoint.x() + StartPoint.x())) / 2);
			Centre.setY(abs((LastPoint.y() + StartPoint.y())) / 2);
			RadiusX = abs((LastPoint.x() - StartPoint.x())) / 2;
			RadiusY = abs((LastPoint.y() - StartPoint.y())) / 2;
			update();
		}
	}
	if (ui.pushButton_4->isChecked())
	{
		if (e->buttons() & Qt::LeftButton)
		{
			if (IsPress)
			{
				LastPoint = e->pos();
				LastPoint.setX(LastPoint.x() - 10);
				LastPoint.setY(LastPoint.y() - 100);
				update();
			}
		}
	}
	if (ui.pushButton_6->isChecked())
	{
		if (e->buttons() & Qt::LeftButton)
		{
			if (IsPress)
			{
				curpoint[curpoint.size()-1].x= e->pos().x() - 10;
				curpoint[curpoint.size() - 1].y = e->pos().y() - 100;
				update();
			}
		}
	}
	if (ui.pushButton_8->isChecked())
	{
		if (IsPress)
		{
			LastPoint = e->pos();
			LastPoint.setX(LastPoint.x() - 10);
			LastPoint.setY(LastPoint.y() - 100);
			OffsetX = LastPoint.x() - StartPoint.x();
			OffsetY = LastPoint.y() - StartPoint.y();
			StartPoint = LastPoint;
			if (IsPress&&StartPoint.x() > 0)
			{
				int id = ChooseID;
				Translate(id, OffsetX, OffsetY);
			}
	
		}
	}
	if (ui.pushButton_9->isChecked())
	{
		if (e->buttons() & Qt::LeftButton)
		{
			if (IsPress)
			{
				LastPoint = e->pos();
				LastPoint.setX(LastPoint.x() - 10);
				LastPoint.setY(LastPoint.y() - 100);
				update();
			}
		}
	}
}

void BigProject::mouseReleaseEvent(QMouseEvent *e)
{
	if (ui.pushButton_3->isChecked())
	{
		IsPress = false;
		PainterData temp;
		int id = ufp.IDcount;
		ufp.IDcount++;

		temp.id = id;
		temp.point.push_back(StartPoint.x());
		temp.point.push_back(StartPoint.y());
		temp.point.push_back(LastPoint.x());
		temp.point.push_back(LastPoint.y());
		temp.type = LineType;
		temp.algorithm = "DDA";
		temp.color.r = ufp.qcolor->red();
		temp.color.g = ufp.qcolor->green();
		temp.color.b = ufp.qcolor->blue();
		ufp.pd.push_back(temp);
		CreateDDALine(StartPoint.x(), StartPoint.y(), LastPoint.x(), LastPoint.y(), 1, ufp.pd.size() - 1);
		ufp.drawingmap->fill(Qt::transparent);
		ui.label_5->setPixmap(*ufp.drawingmap);
		StartPoint.setX(-1);
		update();
	}
	if (ui.pushButton_5->isChecked())
	{
		IsPress = false;
		PainterData temp;
		int id = ufp.IDcount;
		ufp.IDcount++;


		temp.id = id;
		temp.point.push_back((float)Centre.x());
		temp.point.push_back((float)Centre.y());
		temp.radius.push_back(RadiusX);
		temp.radius.push_back(RadiusY);
		temp.type = EllipseType;
		temp.color.r = ufp.qcolor->red();
		temp.color.g = ufp.qcolor->green();
		temp.color.b = ufp.qcolor->blue();
		ufp.pd.push_back(temp);
		CreateElipse(1, Centre.x(), Centre.y(), RadiusX, RadiusY,ufp.pd.size()-1);
		ufp.drawingmap->fill(Qt::transparent);
		ui.label_5->setPixmap(*ufp.drawingmap);
		StartPoint.setX(-1);
		update();
	}
	if (ui.pushButton_4->isChecked())
	{
		if (e->button() == Qt::LeftButton)
		{
			IsPress = false;
			if (!IsFirst)
			{
				PainterData temp;
				int id = ufp.IDcount;
				ufp.IDcount++;
	
				temp.pointcount = 2;
				temp.id = id;
				temp.point.push_back(StartPoint.x());
				temp.point.push_back(StartPoint.y());
				temp.point.push_back(LastPoint.x());
				temp.point.push_back(LastPoint.y());
				temp.type = LineType;
				temp.algorithm = "DDA";
				temp.color.r = ufp.qcolor->red();
				temp.color.g = ufp.qcolor->green();
				temp.color.b = ufp.qcolor->blue();
				ufp.pd.push_back(temp);
			}
			else
			{
				ufp.pd[ufp.pd.size() - 1].pointcount += 1;
				ufp.pd[ufp.pd.size() - 1].point.push_back(LastPoint.x());
				ufp.pd[ufp.pd.size() - 1].point.push_back(LastPoint.y());
			}
			CreateDDALine(StartPoint.x(), StartPoint.y(), LastPoint.x(), LastPoint.y(), 1, ufp.pd.size() - 1);
			ui.label_5->setPixmap(*ufp.drawingmap);
			StartPoint = LastPoint;
			ufp.drawingmap->fill(Qt::transparent);
			ui.label_5->setPixmap(*ufp.drawingmap);
			IsFirst = true;
			update();
		}
		if (e->button() == Qt::RightButton)
		{
			CreateDDALine(LastPoint.x(), LastPoint.y(), FirstStartPoint.x(), FirstStartPoint.y(), 1, ufp.pd.size() - 1);
			ufp.drawingmap->fill(Qt::transparent);
			ui.label_5->setPixmap(*ufp.drawingmap);
			IsFirst = false;
			update();
		}

	}
	if (ui.pushButton_6->isChecked())
	{
		if (e->button() == Qt::LeftButton)
		{
			IsPress = false;
			update();
		}
		if (e -> button() == Qt::RightButton)
		{
			IsPress = false;
			PainterData temp;
			ufp.IDcount++;
			int id = ufp.IDcount;

			temp.id = id;
			temp.pointcount = curpoint.size();
			temp.type = CurveType;
			temp.color.r = ufp.qcolor->red();
			temp.color.g = ufp.qcolor->green();
			temp.color.b = ufp.qcolor->blue();
			for (int k = 0; k < curpoint.size(); k++)
			{
				temp.point.push_back(curpoint[k].x);
				temp.point.push_back(curpoint[k].y);
			}
			ufp.pd.push_back(temp);
			ufp.drawingmap->fill(Qt::transparent);
			ui.label_5->setPixmap(*ufp.drawingmap);
			vector<CurvePoint>respoint = CreateBezierCurve(curpoint);
			for (int k = 0; k < respoint.size() - 1; k++)
			{
				CurvePoint temppoint1 = respoint[k];
				CurvePoint temppoint2 = respoint[k + 1];
				CreateDDALine((int)temppoint1.x, (int)temppoint1.y, (int)temppoint2.x, (int)temppoint2.y, 1,ufp.pd.size()-1);
			}
			curpoint.clear();
			IsPress = false;
		}
	}
	if (ui.pushButton_8->isChecked())
	{
		IsPress = false;
		StartPoint.setX(-1);
	}
	if (ui.pushButton_9->isChecked())
	{
		
		if (e->button() == Qt::LeftButton)
		{
			IsPress = false;
			ufp.drawingpainter->setPen(*ufp.qcolor);
			update();
		}
		if (e->button() == Qt::RightButton)
		{
			IsPress = false;

			int id;


			ClipCohen(id, StartPoint.x(), StartPoint.y(), LastPoint.x(), LastPoint.y());
			ufp.drawingmap->fill(Qt::transparent);
			ui.label_5->setPixmap(*ufp.drawingmap);
			StartPoint.setX(-1);
			ufp.drawingpainter->setPen(*ufp.qcolor);
			update();
		}
	}
}




