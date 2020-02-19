#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-12;

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    Point operator+(const Point& t) const {
        return Point(x + t.x, y + t.y);
    }
    Point operator-(const Point& t) const {
        return Point(x - t.x, y - t.y);
    }
    Point operator*(const double& t) const {
        return Point(x * t, y * t);
    }
    Point operator/(const double& t) const {
        return Point(x / t, y / t);
    }
    bool operator<(const Point& t) const {
        return fabs(x - t.x) < eps ? y < t.y : x < t.x;
    }
    bool operator==(const Point &t) const {
        return fabs(x - t.x) < eps and fabs(y - t.y) < eps;
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
    Point rot90() const {
        return Point(-y, x);
    }
};

struct Circle {
    Point o;
    double r;
    Circle(){}
    Circle(Point o, double r): o(o), r(r){}

    friend vector<Point> operator&(const Circle& c1, const Circle& c2) {
        double d = (c1.o - c2.o).len();
        if(d > c1.r + c2.r + eps or d < fabs(c1.r - c2.r) - eps) {
            return vector<Point>();
        }
        double dt = (c1.r * c1.r - c2.r * c2.r) / d, d1 = (d + dt) / 2;
        Point dir = (c2.o - c1.o) / d, pcrs = c1.o + dir * d1;
        dt = sqrt(max(0.0, c1.r * c1.r - d1 * d1));
        dir = dir.rot90();
        return vector<Point>{pcrs + dir * dt, pcrs - dir * dt};
    }
};

int main() {
    Circle c1 = {Point{0.0, 0.0}, 5.0};
    Circle c2 = {Point{0.0, 6.0}, 5.0};

    vector<Point> tmp = c1 & c2;

    for(auto p : tmp) {
        cout << p.x << " " << p.y << endl;
    }
    cout << (tmp[0] - tmp[1]).len() << endl;
    return 0;
}
