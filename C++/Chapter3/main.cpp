#include <iostream>
#include <cmath>

struct Point {
    double x;
    double y;

    Point(double x,double y):x(x),y(y) { };
    Point(const Point &point):x(point.x),y(point.y) { };
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual double get_surface() const = 0;
    virtual void describe_object() const { std::cout << "this is a shape" << std::endl; };

    double get_double_surface() const { return 2 * get_surface(); };
};

class Square: public Shape {
private:
    Point top_left;
    double side_length;
public:
    Square(const Point &top_left,const double side_length):top_left(top_left),side_length(side_length) { };
    double get_surface() const override { return side_length * side_length; };
    void describe_object() const override { std::cout << "this is a square starting at (" 
                                            << top_left.x << "," << top_left.y << "),with a length of " << side_length << std::endl; };
};

class Circle: public Shape {
private:
    Point center;
    double radius;
public:
    Circle(const Point &center,const double radius):center(center),radius(radius) { };
    double get_surface() const override { return radius * radius * M_PI; };

    double get_diameter() const { return 2 * radius;};

};


int main(int argc,char *argv[])
{
    Square sq(Point(1,1),2);
    sq.describe_object();
    std::cout << "Square area is : " << sq.get_surface() << std::endl;

    Circle circle(Point(0,0),2);
    Shape &sp = circle;

    std::cout << "Diameter: " << static_cast<Circle*>(&sp)->get_diameter() << std::endl;
    std::cout << "Diameter: " << dynamic_cast<Circle*>(&sp)->get_diameter() << std::endl;

    std::cout << "The shape has a surface of " << sp.get_surface() << std::endl;

    Circle *pc = dynamic_cast<Circle*>(&sp);
    if(pc)
        std::cout << "The shape is a circle of diameter " << std::endl;
    else    
        std::cout << "The shape isn't a circle !" << std::endl;

    return 0;
}