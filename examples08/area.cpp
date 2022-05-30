#include <chrono>
#include <iostream>
#include <random>
using namespace std;

struct Point {
    double x, y;
    Point() = default;
    Point(double x, double y) : x(x), y(y){};
};

class Shape {
   public:
    virtual bool contains(Point p) = 0;
};

class Circle : public Shape {
   private:
    double radius;
    Point center;

   public:
    Circle(double radius, Point center = Point(0, 0)) : radius(radius), center(center){};

    virtual bool contains(Point p) {
        return (p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y) <= 1.0;
    }
};

class Rectangle : public Shape {
    Point top_left, top_right, bottom_left, bottom_right;

   public:
    Rectangle(Point top_left, Point top_right, Point bottom_left, Point bottom_right) : top_left(top_left), top_right(top_right), bottom_left(bottom_left), bottom_right(bottom_right){};
    Rectangle(double left, double top, double width, double height) {
        top_left = Point(left, top);
        top_right = Point(left + width, top);
        bottom_left = Point(left, top - height);
        bottom_right = Point(left + width, top - height);
    }
    Point get_top_left() { return top_left; }
    Point get_top_right() { return top_right; }
    Point get_bottom_right() { return bottom_right; }
    Point get_bottom_left() { return bottom_left; }
    virtual bool contains(Point p) {
        return p.x >= top_left.x && p.x <= top_right.x && p.y >= bottom_left.y && p.y <= top_left.y;
    }
    double area() {
        return (top_right.x - top_left.x) * (top_left.y - bottom_left.y);
    }
};

/**
 * @brief the assignment
 *
 * @param container - the rectangle that the shape lies within
 * @param s - the shape whose area we are approximating
 * @param tries - number of points to generate
 * @return double
 */
double approximate_area_of_shape(Rectangle container, Shape* s, size_t tries = 1000) {
    double x1 = container.get_top_left().x;
    double x2 = container.get_top_right().x;
    double y1 = container.get_bottom_left().y;
    double y2 = container.get_top_left().y;

    // initialize random engine and distributers
    default_random_engine engine(chrono::system_clock::now().time_since_epoch().count());
    uniform_real_distribution<double> x_distributer(x1, x2 + 0.1);
    uniform_real_distribution<double> y_distributer(y1, y2 + 0.1);

    // test points
    double num_in_container = 0;
    double num_in_shape = 0;
    for (size_t i = 0; i < tries; ++i) {
        Point temp(x_distributer(engine), y_distributer(engine));
        if (container.contains(temp)) {
            ++num_in_container;
        }
        if (s->contains(temp)) {
            ++num_in_shape;
        }
    }

    double approx_area = container.area() * num_in_shape / num_in_container;
    return approx_area;
}

int main() {
    Circle unit_circle(1);
    for (int i = 0; i < 5; ++i) {
        cout << approximate_area_of_shape(Rectangle(-1, 1, 2, 2), &unit_circle, 10000) << endl;
    }
}