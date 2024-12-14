#include <iostream>
#include "NumberLib.cpp"
#include <algorithm>
using namespace std;

class Rational_Number
{
private:
    // a rational number has two components
    // numerator and denominator
    Number num; // an integer
    Number den; // a natural number 

public:
    // constructors
    Rational_Number();
    Rational_Number(Number num, Number den);
    Rational_Number(Rational_Number &rational);

    // util methods
    void show();
    void show(string prefix, string suffix);

    // comparisonoperators
    bool operator<(Rational_Number rational);
    bool operator>(Rational_Number rational);
    bool operator==(Rational_Number rational);

    // arithmetic operators
    Rational_Number additive_inverse();
    Rational_Number multiplicative_inverse();
    Rational_Number operator+(Rational_Number rational);
    Rational_Number operator-(Rational_Number rational);
    Rational_Number operator*(Rational_Number rational);
    Rational_Number operator/(Rational_Number rational);
};