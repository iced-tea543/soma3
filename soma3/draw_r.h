// draw_r.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#define PI 3.1415926535897932384626433832795
class vec {
public:
    double x, y;
    vec(double x, double y) :x(x), y(y) {};
    vec() = default;
    double operator*(vec dot) { return x * dot.x + y * dot.y; }
    inline double size() { return sqrt(x * x + y * y); }
};
inline vec change(double x, double y , double precision)
{
    x = int(x / precision) * precision;
    y = int(y / precision) * precision;
    return vec(x, y);
}
vec change(vec& location, double precision)
{
    location.x = int(location.x / precision) * precision;
    location.y = int(location.y / precision) * precision;
    return location;
}
inline double Pythagorean(double a, double b)
{
    return std::sqrt(a * a - b * b);
}
/*
double cal(double x, double k, double intercept)
{
    return x * k + intercept;
}
*/
std::vector<vec> draw(vec a, vec b, vec o = { 0,0 }, short way = 1, double precision = 0.001) {
    std::vector<vec> p;
    change(a, precision); change(b, precision);
    if (way == 0)
    {   
        if (a.x == b.x)//竖着的时候
        {
            double y;
            for (y = std::min(a.y, b.y); y < std::max(a.y, b.y); y += precision)
                p.push_back(change(a.x, y, precision));
            p.push_back(change(a.x, std::max(a.y, b.y), precision));
            return p;
        }
        double k = ((a.y - b.y) / (a.x - b.x)), intercept = a.y - a.x * k;
        double x;
        for (x = std::min(a.x, b.x); x < std::max(a.x, b.x); x += precision)
            p.push_back(change(x, x * k + intercept, precision));
        p.push_back(change(std::max(a.x, b.x), std::max(a.x, b.x) * k + intercept, precision));
        return p;
    }
    double r = sqrt((a.x - o.x) * (a.x - o.x) + (a.y - o.y) * (a.y - o.y));
    
    bool n = false;
    
    double per = asin(precision / r);
    if (way == -1)std::swap(a, b), n = true;
    vec oa(a.x - o.x, a.y - o.y), ob(b.x - o.x, b.y - o.y), x(1, 0);
    double roa = acos(oa * x / oa.size()), rob = acos(ob * x / ob.size());
    
    
    if (a.y < o.y)roa = 2 * PI - roa;  if (b.y < o.y)rob = 2 * PI - rob;
    //std::cout << roa / PI * 180 << " " << rob / PI * 180 << " " << per << " ";
    while (roa > rob)rob += 2 * PI;//std::cout << roa << " " << rob << " ";
    for (double i = roa; i < rob; i += per)
        p.push_back(change(cos(i) * r + o.x, std::sin(i) * r + o.y,precision));
    p.push_back(b);
    if (n)for (int i = 0; i < p.size() / 2; i++)std::swap(p[i], p[p.size() - i]);
    
    /*废弃方法，因为无序
    if (a.x == b.x)//竖着的时候
    {
        if (a.y > b.y)std::swap(a, b), way *= -1, n = true;
        for (double y = a.y; y <= b.y; y += precision)
        {
            p.push_back(change(-Pythagorean(r, y - o.y) * way + o.x, y, precision));
        }
        if (n)
            for (int i = 0; i < p.size() / 2; i++)
                std::swap(p[i], p[p.size() - i]);
        return p;
    }
    std::cout<<k<<" " << intercept<<" ";
    double k = (a.y - b.y) / (a.x - b.x), intercept = a.y - a.x * k;
    if (a.x > b.x)std::swap(a, b), way *= -1;
    for (double x = o.x - r; x <= o.x + r; x+=precision)
    {
        vec top(x, Pythagorean(r, x - o.x) + o.y), bottom(x, -Pythagorean(r, x - o.x) + o.y);
        //std::cout << top.x << ' ' << top.y << "\t" << bottom.x << " " << bottom.y << std::endl;;
        double val = x * k + intercept;
        if (way == 1)
        {
            if (top.y < val)p.push_back(change(top, precision));
              if (bottom.y < val)p.push_back(change(bottom, precision));
        }
        if (way == -1)
        {
            if (top.y > val)p.push_back(change(top,precision));
            if (bottom.y > val)p.push_back(change(bottom, precision));
        }
    }
    */
    return p;
}
