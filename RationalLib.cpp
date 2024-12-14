#include <iostream>
#include "NumberLib.cpp"
#include <algorithm>
using namespace std;

class Rational
{
private:
    // a rational number has two components
    // numerator and denominator
    Number num; // an integer
    Number den; // a natural number 

public:
    // constructors
    Rational();
    Rational(Number num, Number den);
    Rational(Rational &rational);

    // util methods
    void show();
    void show(string prefix, string suffix);

    // comparisonoperators
    bool operator<(Rational rational);
    bool operator>(Rational rational);
    bool operator==(Rational rational);

    // arithmetic operators
    Rational additive_inverse();
    Rational multiplicative_inverse();
    Rational operator+(Rational rational);
    Rational operator-(Rational rational);
    Rational operator*(Rational rational);
    Rational operator/(Rational rational);
};