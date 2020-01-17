#include "point.hpp"

Point::Point(){
  x=0;
  y=0;
}


//--------------
// Question 1.a
//--------------
Point::Point(int x1, int y1){
  x = x1;
  y = y1;
}

//--------------
// Question 1.b
//--------------
int Point::lire_x(){
  return x;
}
int Point::lire_y(){
  return y;
}

//--------------
// Question 1.c
//--------------
std::ostream& operator<<(std::ostream& os, Point& p){
  return os << p.lire_x() << p.lire_y();
}

//--------------
// Question 1.d
//--------------
Point millieu(Point p1, Point p2){
  return Point(((p1.lire_x()+p2.lire_x())/2),((p1.lire_y()+p2.lire_y())/2));
}

//--------------
// Question 1.e
//--------------

int distance(Point p1, Point p2){
  return sqrt((p1.lire_x()-p2.lire_x())*(p1.lire_x()-p2.lire_x()) + (p1.lire_y()-p2.lire_y())*(p1.lire_y()-p2.lire_y()));
}