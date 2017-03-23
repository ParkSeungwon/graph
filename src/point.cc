#include"point.h"
using namespace std;

Point::Point(int x, int y) : complex<double>(x, y) {}
Point::Point(complex<double> im) : complex<double>(im) {}
int Point::x() const {return real();}
int Point::y() const {return imag();}

