#include "Fraction.hpp"
#include <numeric>
#include <cmath>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>


using namespace std;

namespace ariel {
// **** define constructors ****

// define defaultive constructor
Fraction::Fraction(): numerator(0), denominator(1000){}
// define constructor loaded with integers
Fraction::Fraction(int nrm, int dnm): numerator(nrm), denominator(dnm)
{
    // check if the denominator is not zero otherwise throws exeception
    if (this->denominator == 0)
    {
        throw std::invalid_argument("cant have 0 as denominator");
    }

    //reduce the fraction to reduced form
    this->reduced();

    //if fraction is positive with minus on both denominator and numerator, show it as positive without minus
    if (this->denominator<0&&this->numerator<0)
    {
        this->numerator*=-1;
        this->denominator*=-1;
    }
    // if the fraction is negative set the minus at the numerator 
    else if(this->denominator < 0)
    {
        this->denominator *=-1;
        this->numerator *=-1;
    }
}

// define constructor loaded with float num
Fraction::Fraction(float num)
{
    // take only 3 numbers after dot
    int nrm = std::round(num*1000);
    int dnm = 1000;
    
    this->numerator = nrm; 
    this->denominator = dnm;
    
    //if fraction is positive with minus show it as positive without minus 
    if (this->denominator<0 && this->numerator<0)
    {
        this->numerator*=-1;
        this->denominator*=-1;
    }
    // if the fraction is negative set the minus at the numerator 
    else if(this->denominator < 0)
    {
        this->denominator *=-1;
        this->numerator *=-1;
    }

    this->reduced();
}

// **** define overflow test ****

// this method handle overflow multipactation
//source: https://stackoverflow.com/questions/1815367/catch-and-compute-overflow-during-multiplication-of-two-large-integers and chatgpt
void Fraction::overflow_multi_test(int num1, int num2)
{
    int mul = num1 * num2;
    if (num1 != 0 && mul / num1 != num2) {
        throw std::overflow_error("multiplictation overflow");
    }
}
// this method handle sum overflow
//source: https://www.geeksforgeeks.org/check-for-integer-overflow/ and chatgpt
void Fraction::overflow_sum_test(int num1, int num2)
{
    int sum = num1+num2;
    if(num1 > 0 && num2 > 0 && sum < 0)
        throw std::overflow_error("sum overflow");
    if(num1 < 0 && num2 < 0 && sum > 0)
        throw std::overflow_error("sum overflow");
}

// this method handle sub overflow
//source: https://www.geeksforgeeks.org/check-for-integer-overflow/ and chatgpt
void Fraction::overflow_sub_test(int num1, int num2)
{
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    if ((num2 < 0 && num1 > (max_int + num2)) || (num2 > 0 && num1 < (min_int + num2))) {
        throw std::overflow_error("Subtraction overflow");

    }
}

// **** define getters and setters ****

// return the numerator
int Fraction::getNumerator() const
{
    return this->numerator;
}
// return the denominator
int Fraction::getDenominator() const
{
    return this->denominator;
}
// set the value of the numerator 
void Fraction::setNumerator(int nrm)
{
    this->numerator = nrm; 
}
// set the value of the denominator 
void Fraction::setDenominator(int dnm)
{
    this->denominator = dnm; 
}

// **** define functions ****

// this function reduce the fraction
void Fraction::reduced()
{
    int gcd = std::gcd(this->numerator, this->denominator);
    this->numerator = this->numerator / gcd;
    this->denominator = this->denominator / gcd;
}

// this function increment the fraction
void Fraction::increment()
{
    this->numerator = this->numerator + this->denominator;
    this->reduced();
}
void Fraction::decrement()
{
    this->numerator = this->numerator - this->denominator;
    this->reduced();
}

//**** define overloading operators ****

// sums two fractions 
Fraction Fraction::operator + (const Fraction& other)
{
    // overflow test
    overflow_multi_test(this->getNumerator(),other.getDenominator());
    overflow_multi_test(other.getNumerator(),this->getDenominator());
    overflow_multi_test(other.getDenominator(),this->getDenominator());
    overflow_sum_test(this->getNumerator()*other.getDenominator(), other.getNumerator()*this->getDenominator());

    return Fraction((this->getNumerator()*other.getDenominator()+other.getNumerator()*this->getDenominator()), this->getDenominator()*other.getDenominator());
}

Fraction operator +(float num, const Fraction& frac)
{
    // send to basic fraction with fraction + operator
    return (Fraction(num)+frac);
}

// substract two fractions 
Fraction Fraction::operator - (const Fraction& other)
{
    // overflow tests
    overflow_multi_test(this->getNumerator(), other.getDenominator());
    overflow_multi_test(other.getNumerator(), this->getDenominator());
    overflow_multi_test(this->getDenominator(), other.getDenominator());
    overflow_sub_test(this->getNumerator()*other.getDenominator(), other.getNumerator()*this->getDenominator());

    return Fraction((this->getNumerator()*other.getDenominator()-other.getNumerator()*this->getDenominator()), this->getDenominator()*other.getDenominator());
}
Fraction operator -(float num, const Fraction& frac)
{
    // send to basic fraction with fraction - operator
    return (Fraction(num)-frac);
}

// multiply two fractions 
Fraction Fraction::operator * (const Fraction& other)
{
    // overflow tests
    overflow_multi_test(this->getNumerator(), other.getNumerator());
    overflow_multi_test(this->getDenominator(), other.getDenominator());

    return Fraction(this->getNumerator()*other.getNumerator(), this->getDenominator()*other.getDenominator());
}
Fraction operator *(float num, const Fraction& frac)
{
    // send to basic fraction with fraction - operator
    return (Fraction(num)*frac);
}

// divide two fractions 
Fraction Fraction::operator / (const Fraction& other)
{
    // check if we do not divide by zero
    if (other == Fraction(0, 1000))
    {
        throw std::runtime_error("cant divide by zero");
    }

    return *this * Fraction(other.getDenominator(), other.getNumerator());
}

Fraction operator / (float num, const Fraction& frac)
{
    // send to basic fraction with fraction / operator
    return (Fraction(num)/frac);
}

// **** compare two fractions ****
// ==
bool operator==(const Fraction& fraction1, const Fraction& fraction2)
{
    return fraction1.getNumerator() * fraction2.getDenominator() == fraction2.getNumerator() * fraction1.getDenominator();
}
// <
bool  operator<(const Fraction& fraction1, const Fraction& fraction2)
{
    return fraction1.getNumerator() * fraction2.getDenominator() < fraction2.getNumerator() * fraction1.getDenominator();
}
// >
bool  operator>(const Fraction& fraction1, const Fraction& fraction2)
{
    return fraction1.getNumerator() * fraction2.getDenominator() > fraction2.getNumerator() * fraction1.getDenominator(); 
}
// <=
bool   operator<=(const Fraction& fraction1, const Fraction& fraction2)
{
    return fraction1.getNumerator() * fraction2.getDenominator() <= fraction2.getNumerator() * fraction1.getDenominator(); 
}
// >=
bool  operator>=(const Fraction& fraction1, const Fraction& fraction2)
{
    return fraction1.getNumerator() * fraction2.getDenominator() >= fraction2.getNumerator() * fraction1.getDenominator(); 
}

// increment fraction
//pre
Fraction& Fraction::operator++()
{
    this->increment();
    return *this;
}
//post
Fraction Fraction::operator++(int)
{
    Fraction temp(*this);
    ++*this;
    return temp;
}

// decrement fraction
//pre
Fraction& Fraction::operator--()
{
    this->decrement();
    return *this;
}
//post
Fraction Fraction::operator--(int)
{
    Fraction temp(*this);
    --*this;
    return temp;
}
// **** define ostream functions ****
// this function handle the output
ostream& operator << (ostream& stream_out, const Fraction& fraction)
{
    return (stream_out << fraction.getNumerator() << "/" << fraction.getDenominator());
}

// this function handle the input
std::istream& operator >> (std::istream& stream_in, Fraction& fraction)
{
    int nrm, dnm;
    stream_in >> nrm >>dnm;

    // IF both integers with are negative show the fraction in positive form
    if (dnm<0 && nrm <0)
    {
        dnm *=-1;
        nrm *=-1;
    }
    // if the fraction is negative set the minus in the numerator
    else if (dnm<0)
    {
        nrm*=-1;
        dnm*=-1;
    }
    // if the denominator is 0 throws an error
    if(dnm==0)
    {
        throw std::runtime_error("cant have 0 as denominator");
    }
    // if input has failed throws an error
    if(stream_in.fail() == true)
    {
        throw std::runtime_error("input error");
    }

    fraction.setNumerator(nrm);
    fraction.setDenominator(dnm);
    fraction.reduced();
    return stream_in;
}
}









