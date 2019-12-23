#include"allclass.h"
void PaintFunction::SplitOrder(char *filename)
{
	ifstream is;
	is.open(filename, ios::in);
	if (!is.is_open())
	{
		cout << "Can't not open file." << endl;
		exit(-1);
	}
	string line;
	while (getline(is, line))
	{
		string result;
		vector<string> temp;
		stringstream ss(line);
		while (ss >> result)
		{
			temp.push_back(result);
		}
		ufp.order.push_back(temp);
	}
	UseOrder();
}
void PaintFunction::UseOrder()
{
	for (int i = 0; i < ufp.order.size(); i++)
	{
		if (ufp.order[i][0] == "resetCanvas")
		{
			int w = atoi(ufp.order[i][1].c_str());
			int h = atoi(ufp.order[i][2].c_str());
			CreateCanvas(w, h);
		}

		if (ufp.order[i][0] == "saveCanvas")
		{
			SaveCanvas(ufp.order[i][1]);
		}

		if (ufp.order[i][0] == "setColor")
		{
			int r = atoi(ufp.order[i][1].c_str());
			int g = atoi(ufp.order[i][2].c_str());
			int b = atoi(ufp.order[i][3].c_str());
			SetColor(r, g, b);
		}

		if (ufp.order[i][0] == "drawPolygon")
		{
			PainterData temp;
			vector<int> t_point;
			temp.id = atoi(ufp.order[i][1].c_str());
			int pointcount = atoi(ufp.order[i][2].c_str());
			temp.algorithm = ufp.order[i][3];
			i++;
			for (int j = 0; j < pointcount*2; j++)
			{
				float temp1 = atoi(ufp.order[i][j].c_str());
				t_point.push_back((int)temp1);
				temp.point.push_back(temp1);
			}

			temp.pointcount = pointcount;
			temp.color.r = ufp.qcolor->red();
			temp.color.g = ufp.qcolor->green();
			temp.color.b = ufp.qcolor->blue();
			temp.type = PolygonType;
			ufp.pd.push_back(temp);
			if (temp.algorithm == "DDA")
				CreateDDAPolygon(pointcount, t_point, ufp.pd.size() - 1);
			else
				CreateBresenhamPolygon(pointcount, t_point, ufp.pd.size() - 1);
		}

		if (ufp.order[i][0] == "drawLine")
		{

			float float_x1 = atof(ufp.order[i][2].c_str());
			float float_y1 = atof(ufp.order[i][3].c_str());
			float float_x2 = atof(ufp.order[i][4].c_str());
			float float_y2 = atof(ufp.order[i][5].c_str());
			int int_id = atoi(ufp.order[i][1].c_str());
			PainterData temp;
			temp.id = int_id;
			temp.point.push_back(float_x1);
			temp.point.push_back(float_y1);
			temp.point.push_back(float_x2);
			temp.point.push_back(float_y2);
			temp.type = LineType;
			temp.algorithm = ufp.order[i][6];
			temp.color.r = ufp.qcolor->red();
			temp.color.g = ufp.qcolor->green();
			temp.color.b = ufp.qcolor->blue();
			ufp.pd.push_back(temp);
			if (temp.algorithm == "DDA")
				CreateDDALine(float_x1, float_y1, float_x2, float_y2,ufp.pd.size()-1);
			else
				CreateBresenham(float_x1, float_y1, float_x2, float_y2, ufp.pd.size() - 1);
		}

		if (ufp.order[i][0] == "drawEllipse")
		{
			int int_id = atoi(ufp.order[i][1].c_str());
			PainterData temp;
			float x = atof(ufp.order[i][2].c_str());
			float y = atof(ufp.order[i][3].c_str());
			float rx = atof(ufp.order[i][4].c_str());
			float ry = atof(ufp.order[i][5].c_str());
			temp.point.push_back(x);
			temp.point.push_back(y);
			temp.radius.push_back(rx);
			temp.radius.push_back(ry);
			temp.type = EllipseType;
			temp.id = int_id;
			temp.color.r = ufp.qcolor->red();
			temp.color.g = ufp.qcolor->green();
			temp.color.b = ufp.qcolor->blue();
			ufp.pd.push_back(temp);
			CreateElipse(x, y, rx, ry, ufp.pd.size() - 1);
		}

		if (ufp.order[i][0] == "translate")
		{
			int id = atoi(ufp.order[i][1].c_str());
			int dx = atoi(ufp.order[i][2].c_str());
			int dy = atoi(ufp.order[i][3].c_str());
			Translate(id, dx, dy);
		}

		if (ufp.order[i][0] == "rotate")
		{
			int id = atoi(ufp.order[i][1].c_str());
			int x = atoi(ufp.order[i][2].c_str());
			int y = atoi(ufp.order[i][3].c_str());
			int r = atoi(ufp.order[i][4].c_str());
			Rotate(id,x, y, r);
		}

		if (ufp.order[i][0] == "scale")
		{
			int id = atoi(ufp.order[i][1].c_str());
			int x = atoi(ufp.order[i][2].c_str());
			int y = atoi(ufp.order[i][3].c_str());
			int s = atoi(ufp.order[i][4].c_str());
			Rotate(id, x, y, s);
		}

		if (ufp.order[i][0] == "clip")
		{
			int id = atoi(ufp.order[i][1].c_str());
			int x1 = atoi(ufp.order[i][2].c_str());
			int y1 = atoi(ufp.order[i][3].c_str());
			int x2 = atoi(ufp.order[i][4].c_str());
			int y2 = atoi(ufp.order[i][5].c_str());
			string algorithm = ufp.order[i][6].c_str();
			if (algorithm == "Cohen-Sutherland")
				ClipCohen(id, x1, y1, x2, y2);
			if (algorithm == "Liang-Barsky")
				ClipLiang(id, x1, y1, x2, y2);
		}

		if (ufp.order[i][0] == "drawCurve")
		{
			PainterData temp;
			vector<CurvePoint>cp;
			CurvePoint tempcp;
			temp.id = atoi(ufp.order[i][1].c_str());
			temp.pointcount = atoi(ufp.order[i][2].c_str());
			temp.algorithm = ufp.order[i][3];
			i++;
			for (int j = 0; j < temp.pointcount * 2; j++)
			{
				float temp1 = atoi(ufp.order[i][j].c_str());
				if(j%2==0)
					tempcp.x= atoi(ufp.order[i][j].c_str());
				else
				{
					tempcp.y = atoi(ufp.order[i][j].c_str());
					cp.push_back(tempcp);
				}
				temp.point.push_back(temp1);
			}
			temp.color.r = ufp.qcolor->red();
			temp.color.g = ufp.qcolor->green();
			temp.color.b = ufp.qcolor->blue();
			temp.type = CurveType;
			ufp.pd.push_back(temp);
			if (temp.algorithm == "Bezier")
			{
				vector< CurvePoint> cp2;
				cp2=CreateBezierCurve(cp, ufp.pd.size() - 1);
				for (int j = 0; j < cp2.size()-1; j++)
				{
					CurvePoint temppoint1 = cp2[j];
					CurvePoint temppoint2=cp2[j+1];
					CreateDDALine((int)temppoint1.x, (int)temppoint1.y, (int)temppoint2.x, (int)temppoint2.y, ufp.pd.size() - 1);

				}
			}
			else if (temp.algorithm == "B-spline")
			{
				vector< CurvePoint> cp2;
				cp2 = CreateBSplineCurve(cp, ufp.pd.size() - 1);
				for (int j = 0; j < cp2.size() - 1; j++)
				{
					ufp.qpainter->drawPoint((int)cp2[j].x, (int)cp2[j].y);
				}
			}
		}
	}
}

void PaintFunction::CreateCanvas(int width, int length)
{
	ufp.pd.clear();
	ufp.qmap = new QPixmap(width, length);
	ufp.qpainter = new QPainter(ufp.qmap);
	ufp.qpainter->fillRect(0, 0, width, length, Qt::white);
	ufp.qcolor = new QColor(0, 0, 0);
	ufp.cd.width = width;
	ufp.cd.height = length;
}

void PaintFunction::SaveCanvas(string name)
{
	QString SaveName;
	SaveName = QString(QString::fromLocal8Bit(name.c_str()));
	SaveName = SaveName + ".bmp";
	QFile file(SaveName);
	if (!file.open(QFile::WriteOnly))
	{
		cout << "Can't not open file." << endl;
		exit(-1);
	}
	QTextStream qt(&file);
	QByteArray qba;
	QBuffer qb(&qba);
	qb.open(QIODevice::WriteOnly);
	ufp.qmap->save(&qb, "BMP");
	file.write(qba);
	cout << "Save Successfullly." << endl;
}
void PaintFunction::SetColor(int r, int g, int b)
{
	*ufp.qcolor = QColor(r, g, b);
	ufp.qpainter->setPen(*ufp.qcolor);
}
void PaintFunction::CreateDDALine(float x1, float y1, float x2, float y2,int index)
{
	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
	{
		cout << "Can't be Negative." << endl;
		return;
	}
	float m;
	m = (y2 - y1) / (x2 - x1);
	if (abs(m) <= 1)
	{
		if (x1 > x2)
		{
			swap(x1, x2);
			swap(y1, y2);
		}
		ufp.qpainter->drawPoint((int)x1, (int)y1);
		ufp.pd[index].allpointx.push_back((int)x1);
		ufp.pd[index].allpointy.push_back((int)y1);
		float yk = y1;
		for (int xk = (int)x1 + 1; xk <= (int)x2; xk++)
		{
			yk = yk + m;
			ufp.qpainter->drawPoint(xk, (int)(yk+0.5));
			ufp.pd[index].allpointx.push_back((int)xk);
			ufp.pd[index].allpointy.push_back((int)(yk+0.5));
		}
	}
	else
	{
		if (y1 > y2)
		{
			swap(x1, x2);
			swap(y1, y2);
		}
		ufp.qpainter->drawPoint((int)x1, (int)y1);
		ufp.pd[index].allpointx.push_back((int)x1);
		ufp.pd[index].allpointy.push_back((int)y1);
		float xk = x1;
		for (int yk = (int)y1 + 1; yk <= (int)y2; yk++)
		{
			xk = xk + 1 / m;
			ufp.qpainter->drawPoint((int)(xk+0.5), yk);
			ufp.pd[index].allpointx.push_back((int)(xk+0.5));
			ufp.pd[index].allpointy.push_back((int)yk);
		}
	}
}

void PaintFunction::CreateBresenham(float x1, float y1, float x2, float y2,int index)
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
		p = 2 * deltay - deltax;
		ufp.qpainter->drawPoint((int)x1, (int)y1);
		ufp.pd[index].allpointx.push_back((int)x1);
		ufp.pd[index].allpointy.push_back((int)y1);
		int yk = y1;
		for (int xk = (int)x1 + 1; xk <= (int)x2; xk++)
		{
			if (p < 0)
			{
				ufp.qpainter->drawPoint(xk, yk);
				ufp.pd[index].allpointx.push_back((int)xk);
				ufp.pd[index].allpointy.push_back((int)yk);
				p = p + 2 * deltay;
			}
			else
			{
				if (m > 0)
					yk = yk + 1;

				else
					yk = yk - 1;
				ufp.qpainter->drawPoint(xk, yk);
				ufp.pd[index].allpointx.push_back((int)xk);
				ufp.pd[index].allpointy.push_back((int)yk);
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
		ufp.qpainter->drawPoint((int)x1, (int)y1);
		ufp.pd[index].allpointx.push_back((int)x1);
		ufp.pd[index].allpointy.push_back((int)y1);
		int xk = x1;
		for (int yk = (int)y1 + 1; yk <= (int)y2; yk++)
		{
			if (p < 0)
			{
				ufp.qpainter->drawPoint(xk, yk);
				ufp.pd[index].allpointx.push_back((int)xk);
				ufp.pd[index].allpointy.push_back((int)yk);
				p = p + 2 * deltax;
			}
			else
			{
				if (m > 0)
					xk = xk + 1;
				else
					xk = xk - 1;
				ufp.qpainter->drawPoint(xk, yk);
				ufp.pd[index].allpointx.push_back((int)xk);
				ufp.pd[index].allpointy.push_back((int)yk);
				p = p + 2 * deltax - 2 * deltay;
			}
		}
	}

}

void PaintFunction::CreateDDAPolygon(int pointcount, vector<int> point,int index)
{
	for (int i = 0; i < pointcount; i++)
	{
		float x1 = (float)point[i * 2];
		float y1 = (float)point[i * 2 + 1];
		float x2 = (float)point[(i * 2 + 2) % (2 * pointcount)];
		float y2 = (float)point[(i * 2 + 3) % (2 * pointcount)];
		CreateDDALine(x1, y1, x2, y2,index);
	}
}
void PaintFunction::CreateBresenhamPolygon(int pointcount, vector<int> point,int index)
{
	for (int i = 0; i < pointcount; i++)
	{
		float x1 = (float)point[i * 2];
		float y1 = (float)point[i * 2 + 1];
		float x2 = (float)point[(i * 2 + 2) % (2 * pointcount)];
		float y2 = (float)point[(i * 2 + 3) % (2 * pointcount)];
		CreateBresenham(x1, y1, x2, y2, index);
	}
}
void PaintFunction::CreateElipse(int x, int y, int rx, int ry,int index)
{
	double sqa = rx * rx;
	double sqb = ry * ry;
	double p = sqb + sqa * (0.25 - ry);
	int xi = 0;
	int yi = ry;
	SetFourPoint(x, y, xi, yi,index);
	while (sqb*(xi + 1) < sqa*(yi - 0.5))
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
		SetFourPoint(x, y, xi, yi,index);
	}
	//p = sqb * (xi + 1 / 2)*(xi + 1 / 2) + sqa * (yi - 1) - sqa * sqb;
	p = (ry*(xi + 0.5)) * 2 + (rx*(yi - 1)) * 2 - (rx*ry) * 2;
	while (yi > 0)
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
		SetFourPoint(x, y, xi, yi,index);
	}
}

vector<CurvePoint> PaintFunction::CreateBezierCurve(vector<CurvePoint> point, int index)
{
	if (point.size()<1)
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

	vector<CurvePoint> ppoint1 = CreateBezierCurve(point1,index);
	vector<CurvePoint> ppoint2 = CreateBezierCurve(point2,index);
	for (float t = 0; t < 1; t += step) 
	{
		CurvePoint temp;
		temp.x = (1.0 - t) * ppoint1[(int)(1.0 / step * t+0.5)].x + t * ppoint2[(int)(1.0 / step * t+0.5)].x;
		temp.y = (1.0 - t) * ppoint1[(int)(1.0 / step * t + 0.5)].y + t * ppoint2[(int)(1.0 / step * t + 0.5)].y;
		respoint.push_back(temp);
	}
	return respoint;

}

vector<CurvePoint> PaintFunction::CreateBSplineCurve(vector<CurvePoint> point, int index)
{
	
	vector<CurvePoint> temp;
	vector<CurvePoint>res;

	for (int i = 0; i < point.size(); i++)
		temp.push_back(point[i]);
	for (int i = 0; i < point.size() - 3; i++)
	{
		CurvePoint point1 = temp[i];
		CurvePoint point2 = temp[i+1];
		CurvePoint point3 = temp[i+2];
		CurvePoint point4 = temp[i+3];
		float step = 0.01;
		for (float t = 0; t <= 1; t += step)
		{

			double N03 = 1.0 / 6 *( -pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1);
			double N13 = 1.0 / 6 * (3 * pow(t, 3) - 6 * pow(t, 2) + 4);
			double N23 = 1.0 / 6 * (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1);
			double N33 = 1.0 / 6 * pow(t, 3);
			CurvePoint steppoint;
			steppoint.x = N03 * point1.x + N13 * point2.x + N23 * point3.x + N33 * point4.x;
			steppoint.y = N03 * point1.y + N13 * point2.y + N23 * point3.y + N33 * point4.y;
			res.push_back(steppoint);
		}
	}
	return res;
	
	/*
	vector<CurvePoint>res;
	int n = point.size();
	for (int i = 0; i < n - 3; i++)
	{
		int x0 = point[i].x, y0 = point[i].y;
		int x1 = point[i+1].x, y1 = point[i+1].y;
		int x2 = point[i+2].x, y2 = point[i+2].y;
		int x3 = point[i+3].x, y3 = point[i+3].y;
		double a3 = (double)-x0 / 6 + x1 / 2 - x2 / 2 + x3 / 6, b3 = (double)-y0 / 6 + y1 / 2 - y2 / 2 + y3 / 6;
		double a2 = (double)x0 / 2 - x1 + x2 / 2, b2 = (double)y0 / 2 - y1 + y2 / 2;
		double a1 = (double)-x0 / 2 + x2 / 2, b1 = (double)-y0 / 2 + y2 / 2;
		double a0 = (double)x0 / 6 + 2 * x1 / 3 + x2 / 6, b0 = (double)y0 / 6 + 2 * y1 / 3 + y2 / 6;
		for (int j = 0; j <= 100; j++)
		{
			double t = (double)j / 100;
			double xj = a3 * t*t*t + a2 * t*t + a1 * t + a0;
			double yj = b3 * t*t*t + b2 * t*t + b1 * t + b0;
			CurvePoint temppoint;
			temppoint.x = xj;
			temppoint.y = yj;
			res.push_back(temppoint);
		}
	}
	return res;
	*/
}


void PaintFunction::Translate(int id, int dx, int dy)
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
}

void PaintFunction::Rotate(int id, int x, int y, int r)
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
		int xk = ufp.pd[i].allpointx[k];
		int yk = ufp.pd[i].allpointy[k];
		double ang = r * 3.1415926535 / 180;
		ufp.pd[i].allpointx[k] = (int)(x + (xk - x)*cos(ang) - (yk - y)*sin(ang)+0.5f);
		ufp.pd[i].allpointy[k] = (int)(y + (xk - x)*sin(ang) + (yk - y)*cos(ang)+0.5f);
	}
	for (int k = 0; k < ufp.pd[i].point.size()/2; k++)
	{
		double ang = r * 3.1415926535 / 180;
		int xk = ufp.pd[i].point[2*k];
		int yk = ufp.pd[i].point[2 * k+1];
		ufp.pd[i].point[2*k] = (int)(x + (xk - x)*cos(ang) - (yk - y)*sin(ang) + 0.5f);
		ufp.pd[i].point[2*k+1] = (int)(y + (xk - x)*sin(ang) + (yk - y)*cos(ang) + 0.5f);
	}

	
	for (int j = 0; j < ufp.pd.size(); j++)
	{
		QColor tempColor = QColor(ufp.pd[j].color.r, ufp.pd[j].color.g, ufp.pd[j].color.b);
		ufp.qpainter->setPen(tempColor);
		for (int k = 0; k < ufp.pd[j].allpointx.size(); k++)
			ufp.qpainter->drawPoint(ufp.pd[j].allpointx[k], ufp.pd[j].allpointy[k]);
	}
	ufp.qpainter->setPen(*ufp.qcolor);
}
void PaintFunction::Scale(int id, int x, int y, int s)
{
	int i;
	for (i = 0; i < ufp.pd.size(); i++)
	{
		if (ufp.pd[i].id == id)
			break;
	}
	ufp.qpainter->fillRect(0, 0, ufp.cd.width, ufp.cd.height, Qt::white);

	for (int j = 0; j < ufp.pd.size(); j++)
	{
		QColor tempColor = QColor(ufp.pd[j].color.r, ufp.pd[j].color.g, ufp.pd[j].color.b);
		ufp.qpainter->setPen(tempColor);
		if (j == i)
		{
			if (ufp.pd[j].type == LineType)
			{
				ufp.pd[j].allpointx.clear();
				ufp.pd[j].allpointy.clear();
				for (int k = 0; k < ufp.pd[j].point.size() ; k++)
				{
					if (k % 2 == 0)
						ufp.pd[j].point[k] =(int)( ufp.pd[j].point[k] * s + x * (1 - s)+0.5f);
					else
						ufp.pd[j].point[k] =(int)( ufp.pd[j].point[k] * s + y * (1 - s)+0.5f);
				}
				if (ufp.pd[j].algorithm == "DDA")
					CreateDDALine(ufp.pd[j].point[0], ufp.pd[j].point[1], ufp.pd[j].point[2], ufp.pd[j].point[3], i);
				else
					CreateBresenham(ufp.pd[j].point[0], ufp.pd[j].point[1], ufp.pd[j].point[2], ufp.pd[j].point[3], i);
			}
			if (ufp.pd[j].type == EllipseType)
			{
				ufp.pd[j].allpointx.clear();
				ufp.pd[j].allpointy.clear();
				for (int k = 0; k < ufp.pd[j].point.size(); k++)
				{
					if (k % 2 == 0)
						ufp.pd[j].point[k] = (int)(ufp.pd[j].point[k] * s + x * (1 - s)+0.5f);
					else
						ufp.pd[j].point[k] = (int)(ufp.pd[j].point[k] * s + y * (1 - s)+0.5f);
				}
				ufp.pd[j].radius[0] *= s;
				ufp.pd[j].radius[1] *= s;
				CreateElipse(ufp.pd[j].point[0], ufp.pd[j].point[1], ufp.pd[j].radius[0], ufp.pd[j].radius[1], i);
			}
			if (ufp.pd[j].type == PolygonType)
			{
				ufp.pd[j].allpointx.clear();
				ufp.pd[j].allpointy.clear();
				vector<int>temp;
				for (int k = 0; k < ufp.pd[j].point.size(); k++)
				{
					if (k % 2 == 0)
						ufp.pd[j].point[k] = (int)(ufp.pd[j].point[k] * s + x * (1 - s)+0.5f);
				
					else
						ufp.pd[j].point[k] =(int)( ufp.pd[j].point[k] * s + y * (1 - s)+0.5f);
					temp.push_back((int)ufp.pd[j].point[k]);
				}
				if (ufp.pd[j].algorithm == "DDA")
					CreateBresenhamPolygon(ufp.pd[j].pointcount, temp, j);
				else
					CreateBresenhamPolygon(ufp.pd[j].pointcount, temp, j);
			}
		}
		else
		{
			for (int k = 0; k < ufp.pd[j].allpointx.size(); k++)
				ufp.qpainter->drawPoint(ufp.pd[j].allpointx[k], ufp.pd[j].allpointy[k]);
		}
	}
	ufp.qpainter->setPen(*ufp.qcolor);
}

void PaintFunction::ClipCohen(int id, int x1, int y1, int x2 ,int y2)
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
}

void PaintFunction::ClipLiang(int id, int x1, int y1, int x2, int y2)
{
	int i;
	for (i = 0; i < ufp.pd.size(); i++)
	{
		if (ufp.pd[i].id == id)
			break;
	}
	ufp.qpainter->fillRect(0, 0, ufp.cd.width, ufp.cd.height, Qt::white);
	int deltax = ufp.pd[i].point[2] - ufp.pd[i].point[0];
	int deltay = ufp.pd[i].point[3]- ufp.pd[i].point[1];
	int p[4];
	int q[4];
	float tempx1 = ufp.pd[i].point[0];
	float tempy1= ufp.pd[i].point[1];
	p[0] = -deltax;
	p[1] = deltax;
	p[2] = -deltay;
	p[3] = deltay;
	q[0] = ufp.pd[i].point[0] - x1;
	q[1] = x2 - ufp.pd[i].point[0];
	q[2] = ufp.pd[i].point[1] - y1;
	q[3] = y2 - ufp.pd[i].point[1];
	double u1 = 0;
	double u2 = 1;
	bool isinter = true;
	for (int i = 0; i < 4; i++)
	{

		double r = (double)q[i] / p[i];
		if (p[i] < 0)
		{
			if (r > u2)
				isinter = false;
			if (r > u1)
				u1 = r;
		}
		else if (p[i] > 0)
		{
			if (r < u1)
				isinter = false;
			if (r < u2)
				u2 = r;
		}
		else if (q[i] < 0)
			isinter =  false;
	}
	if (isinter == false)
	{
		ufp.pd[i].point[0] = 0;
		ufp.pd[i].point[1] = 0;
		ufp.pd[i].point[2] = 0;
		ufp.pd[i].point[3] = 0;
	}
	ufp.pd[i].point[0] = tempx1 + u1 * deltax;
	ufp.pd[i].point[1] = tempy1 + u1 * deltay;
	ufp.pd[i].point[2] = tempx1 + u2 * deltax;
	ufp.pd[i].point[3] = tempy1 + u2 * deltay;
	for (int j = 0; j < ufp.pd.size(); j++)
	{
		QColor tempColor = QColor(ufp.pd[j].color.r, ufp.pd[j].color.g, ufp.pd[j].color.b);
		ufp.qpainter->setPen(tempColor);
		if (j == i)
		{
			
			ufp.pd[i].allpointx.clear();
			ufp.pd[i].allpointy.clear();
			if (isinter)
			{
				if (ufp.pd[i].algorithm == "DDA")
					CreateDDALine(ufp.pd[i].point[0], ufp.pd[i].point[1], ufp.pd[i].point[2], ufp.pd[i].point[3], i);
				else
					CreateBresenham(ufp.pd[i].point[0], ufp.pd[i].point[1], ufp.pd[i].point[2], ufp.pd[i].point[3], i);
			}
		}
		else
		{
			
			for (int k = 0; k < ufp.pd[j].allpointx.size(); k++)
				ufp.qpainter->drawPoint(ufp.pd[j].allpointx[k], ufp.pd[j].allpointy[k]);
		}
		
	}
	ufp.qpainter->setPen(*ufp.qcolor);
}

void PaintFunction::SetFourPoint(int x1, int y1, int x, int y,int index)
{
	ufp.qpainter->drawPoint((x1 + x), (y1 + y));
	ufp.pd[index].allpointx.push_back(x1+x);
	ufp.pd[index].allpointy.push_back(y1+y);
	ufp.qpainter->drawPoint((x1 + x), (y1 - y));
	ufp.pd[index].allpointx.push_back(x1+x);
	ufp.pd[index].allpointy.push_back(y1-y);
	ufp.qpainter->drawPoint((x1 - x), (y1 + y));
	ufp.pd[index].allpointx.push_back(x1-x);
	ufp.pd[index].allpointy.push_back(y1+y);
	ufp.qpainter->drawPoint((x1 - x), (y1 - y));
	ufp.pd[index].allpointx.push_back(x1-x);
	ufp.pd[index].allpointy.push_back(y1-y);
}

