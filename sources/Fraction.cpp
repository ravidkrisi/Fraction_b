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


using namespace ariel;
using namespace std;

// define constructor loaded with integers
Fraction::Fraction(): numerator(0), denominator(1000){}

Fraction::Fraction(int nrm, int dnm): numerator(nrm), denominator(dnm)
{
    if (this->denominator == 0)
    {
        throw std::invalid_argument("cant have 0 as denominator");
    }
    this->reduced();

    //if fraction is positive with minus show it as positive without minus 
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
    int nrm = std::round(num*1000);
    int dnm = 1000;
    
    this->numerator = nrm; 
    this->denominator = dnm;
    
    //if fraction is positive with minus show it as positive without minus 
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

    this->reduced();
}


float Fraction:: toFloat() const
{
    return (float)this->numerator/(float)this->denominator;
}

//overlaoding operators

// sums two fractions 
Fraction Fraction::operator + (const Fraction& other)
{
    long nrm = static_cast<long> (this->getNumerator()*other.getDenominator()+other.getNumerator()*this->getDenominator());
    long dnm = static_cast<long> (this->getDenominator()*other.getDenominator());

//    checkOverflow(nrm, dnm);

    return Fraction((this->getNumerator()*other.getDenominator()+other.getNumerator()*this->getDenominator()), this->getDenominator()*other.getDenominator());

}

Fraction ariel::operator +(float num, const Fraction& frac)
{
    return (Fraction(num)+frac);
}

// substract two fractions 
Fraction Fraction::operator - (const Fraction& other)
{
    long nrm = static_cast<long> (this->getNumerator()*other.getDenominator()-other.getNumerator()*this->getDenominator());
    long dnm = static_cast<long> (this->getDenominator()*other.getDenominator());

//    checkOverflow(nrm, dnm);

    return Fraction((this->getNumerator()*other.getDenominator()-other.getNumerator()*this->getDenominator()), this->getDenominator()*other.getDenominator());
}
Fraction ariel::operator -(float num, const Fraction& frac)
{
    return (Fraction(num)-frac);
}

// multiply two fractions 
Fraction Fraction::operator * (const Fraction& other)
{

    overflow_multiplication_check(this->getNumerator(), other.getNumerator());
    overflow_multiplication_check(this->getDenominator(), other.getDenominator());


    return Fraction(this->getNumerator()*other.getNumerator(), this->getDenominator()*other.getDenominator());
}
Fraction ariel::operator *(float num, const Fraction& frac)
{
    return (Fraction(num)*frac);
}

// divide two fractions 
Fraction Fraction::operator / (const Fraction& other)
{
    if (other == Fraction(0, 1000))
    {
        throw std::runtime_error("cant divide by zero");
    }
    return *this * Fraction(other.getDenominator(), other.getNumerator());
}

Fraction ariel::operator / (float num, const Fraction& frac)
{
    return (Fraction(num)/frac);
}

// compare two fractions  
bool ariel::operator==(const Fraction& fraction1, const Fraction& fraction2)
{

    return fraction1.getNumerator() * fraction2.getDenominator() == fraction2.getNumerator() * fraction1.getDenominator();
}

bool  ariel::operator<(const Fraction& fraction1, const Fraction& fraction2)
{
    return fraction1.getNumerator() * fraction2.getDenominator() < fraction2.getNumerator() * fraction1.getDenominator();
}

bool  ariel::operator>(const Fraction& fraction1, const Fraction& fraction2)
{
    return fraction1.getNumerator() * fraction2.getDenominator() > fraction2.getNumerator() * fraction1.getDenominator(); 
}

bool   ariel::operator<=(const Fraction& fraction1, const Fraction& fraction2)
{
    return fraction1.getNumerator() * fraction2.getDenominator() <= fraction2.getNumerator() * fraction1.getDenominator(); 
}

bool  ariel::operator>=(const Fraction& fraction1, const Fraction& fraction2)
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









