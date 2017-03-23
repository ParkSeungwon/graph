#pragma once
#include<complex>

class Point : public std::complex<double>
{
public:
	Point(int x=0, int y=0);
	Point(std::complex<double> im);
	int x() const; 		
	int y() const; 	
};

