#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Point {
    long x;
    long y;

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

long double ccw(Point a, Point b, Point c) {
    return (long double)(b.x - a.x) * (c.y - a.y) - (long double)(b.y - a.y) * (c.x - a.x);
}

struct Compare {
    Point p_0;
    explicit Compare(Point p_0): p_0(p_0) {}
    bool operator()(Point a, Point b) {
        long double res = ccw(p_0, a, b);
        return res > 0 || (res == 0 && a.y < b.y);
    }
};

int main() {
    // input
    int n;
    std::cin >> n;
    if (n == 0) {
        return 0;
    }
    std::set<Point> unique_points;
    for (int i = 0; i < n; i++) {
        Point point;
        std::cin >> point.x >> point.y;
        unique_points.insert(point);
    }

    // copy unique points to vector
    std::vector<Point> points;
    points.assign(unique_points.begin(), unique_points.end());
    int min_index = 0;
    for (int i = 1; i < static_cast<int>(points.size()); i++) {
        if (points[i].y < points[min_index].y
            || (points[i].y == points[min_index].y && points[i].x < points[min_index].x))
        {
            min_index = i;
        }
    }
    std::swap(points[0], points[min_index]);

    // sort by polar angle
    Compare comp(points[0]);
    std::sort(points.begin() + 1, points.end(), comp);

    // graham scan
    std::vector<Point> s;
    for (auto point: points) {
        while (s.size() >= 2 && ccw(s[s.size() - 2], s[s.size() - 1], point) <= 0) {
            s.pop_back();
        }
        s.push_back(point);
    }

    // output
    for (auto point: s) {
        std::cout << point.x << ' ' << point.y << std::endl;
    }
    return 0;
}
