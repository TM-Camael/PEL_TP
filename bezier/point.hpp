#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <math.h>
using namespace std;

class Point{
private:
  double x,y;
public:
  //Constructeur vide
    Point(); 

  //--------------
  // Question 1.a
  //--------------
    Point(double x, double y);

  //--------------
  // Question 1.b
  //--------------
    double lire_x();
    double lire_y();
  
};


//--------------
// Question 1.c
//--------------
std::ostream& operator<<(std::ostream& os, Point& p);

//--------------
// Question 1.d
//--------------

Point millieu(Point p1, Point p2);

//--------------
// Question 1.e
//--------------

int distance(Point p1, Point p2);

#endif
