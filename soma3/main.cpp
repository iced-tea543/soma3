#define _SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING
#define _SILENCE_CXX20_CISO646_REMOVED_WARNING 
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<format>
struct Point2d
{
	double x, y;
	Point2d() {
		this->x = 0, this->y = 0;
	}
	Point2d(double x,double y) {
		this->x = x, this->y = y;
	}
	bool operator==(Point2d* p2) const {
		return this->x == p2->x and this->y == p2->y;
	}
	std::string to_string()
	{
		return std::to_string(x) + ' ' + std::to_string(y);
	}
};
Point2d* CalcMidPoint(Point2d *a,Point2d *b)
{
	return new Point2d((a->x + b->x) / 2, (a->y + b->y) / 2);
}
class line
{
protected:
	double k, b;
public:
	line(double k=0,double b=0) { this->k=k,this->b=b;}
	line(Point2d *p1,Point2d *p2)
	{
		double x1 = p1->x, y1 = p1->y, x2 = p2->x, y2 = p2->y;
		this->k = (y2 - y1) / (x2 - x1);
		this->b = y1 - k * x1;
	}
	double getk() { return this->k; }
	double getb() { return this->b; }
	void calcb(Point2d *p)
	{
		this->b = p->y - k * p->x;
	}
};
Point2d* CalcIntersectantPoint(line* a, line* b)
{
	if (a->getk() == b->getk())
		return NULL;
	double k1 = a->getk(), k2 = b->getk(), b1 = a->getb(), b2 = b->getb();
	double x = (b2 - b1) / (k1 - k2);
	return new Point2d(x, k1 * x + b1);
}
class perpendicular_bisector : public line
{
public:

	perpendicular_bisector(Point2d *p1, Point2d *p2):line{}
	{
		line l(p1, p2);
		this->k = -1 / l.getk();
		Point2d* midpoint = CalcMidPoint(p1, p2);
		this->calcb(midpoint);
		delete[] midpoint;
	}
};

struct Tree
{
	Point2d* data;
	Tree(Point2d* data) {
		this->data = data;
	}
	std::vector<Tree*> children;
	bool has_child()
	{
		return !children.empty();
	}
	std::string to_string()
	{
		return data->to_string();
	}
	void print_tree()
	{
		std::cout << to_string() << std::endl;
		for (auto i : children)
		{
			std::cout << "child:\t";
			i->print_tree();
		}
	}
};
std::vector<Tree*> get_last_element(Point2d* points, int num, int& index)
{
	std::vector<Tree*> vp = { new Tree(&points[index]) };
	index--;
	for (; index >= 0 and points[index].x == points[index + 1].x; index--)
		vp.insert(vp.begin(), new Tree(&points[index]));
	return vp;
}
void printvt(std::vector<Tree*> v)
{
	for (auto i : v)
		i->print_tree();
}
std::vector<Tree*> soma(Point2d* points, int num)
{
	int index = num - 1;
	std::vector<Tree*> base2, base1 = get_last_element(points, num, index);

	do {
		base2 = base1;
		base1 = get_last_element(points, num, index);
		std::sort(base1.begin(), base1.end(), [](Tree* a, Tree* b) {
			return a->data->y < b->data->y;
			}
		);
		std::sort(base2.begin(), base2.end(), [](Tree* a, Tree* b) {
			return a->data->y < b->data->y;
			}
		);
		if (base2.size() > base1.size())
		{
			int k = base2.size() / base1.size(), n = base2.size() % base1.size();
			if (!n)
				for (int i = 0, cnt = 0; i < base2.size(); cnt++)
					for (int j = k; j; j--, i++)
						base1[cnt]->children.push_back(base2[i]);
			else
			{
				int cnt = 0;
				for (int i = 0; i < n; i++)
					for (int j = k + 1; j; j--, cnt++)
						base1[i]->children.push_back(base2[cnt]);
				for (int i = n; i < base1.size(); i++)
					for (int j = k; j; j--, cnt++)
						base1[i]->children.push_back(base2[cnt]);
			}
		}
		else if (base2.size() == base1.size())
		{
			for (int i = 0; i < base1.size(); i++)
				base1[i]->children.push_back(base2[i]);
		}
		else
		{
			int k = base1.size() / base2.size(), n = base1.size() % base2.size();
			if (!n)
				for (int i = 0; i < base1.size(); i += k)
					base1[i]->children.push_back(base2[i / k]);
			else
			{
				for (int i = 0; i < n * (k + 1); i += k + 1)
					base1[i]->children.push_back(base2[i / (k + 1)]);
				for (int i = n * (k + 1); i < base1.size(); i += k)
					base1[i]->children.push_back(base2[n + (i - n * (k + 1)) / k]);
			}
		}
	} while (index >= 0);
	return base1;
}
std::vector<Point2d*> draw_soma(Tree* t)
{

}
#include"draw_r.h"
int main()
{
	Point2d* p = new Point2d[20]();
	for (int i = 0; i < 14; i++)
		p[i].x = 0, p[i].y = i;
	for (int i = 14; i < 18; i++)
		p[i].x = 1, p[i].y = i;
	for (int i = 18; i < 20; i++)
		p[i].x = 2, p[i].y = i;
	std::vector<Tree*> v=soma(p,20);
	
	printvt(v);
	/*
	initgraph(1000, 500, EX_SHOWCONSOLE);
	vec a, b, o; double precision; short way;

	std::cin >> a.x >> a.y >> b.x >> b.y >> o.x >> o.y >> way >> precision;
	std::vector<vec> p = draw(a, b, o, way, precision);
	std::cout << p.size();
	if (p.size() > 8000)BeginBatchDraw();
	settextstyle(30, 15, nullptr);
	outtextxy(a.x - 15, a.y - 7.5, 'A');
	outtextxy(b.x - 15, b.y - 7.5, 'B');
	outtextxy(o.x - 15, o.y - 7.5, 'O');

	for (vec a : p)
	{
		putpixel(a.x, a.y, WHITE);
		if (p.size() < 8000)if (int(a.x / precision) % 50 == 0)Sleep(1);
	}

	if (p.size() > 8000)EndBatchDraw();

	while (true);*/
}

