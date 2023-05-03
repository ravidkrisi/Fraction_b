#include "Fraction.hpp"
#include <numeric>
#include <cmath>

using namespace ariel;
using namespace std;

// define constructor loaded with integers 
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

    float a = this->toFloat();
    float b = other.toFloat();

    return Fraction(a+b);
}

// substract two fractions 
Fraction Fraction::operator - (const Fraction& other)
{
    // int nrm = (this->getNumerator()*other.getDenominator()) - (other.getNumerator()*this->getDenominator()); // calc new fraction nrm
    // int dnm = this->getDenominator()*other.getDenominator(); // calc new fraction dnm
    // int gcd = Fraction::gcd(nrm, dnm); // calc the gcd of nrm and dnm 

    // return Fraction((nrm/gcd), (dnm/gcd)); 

    float a = this->toFloat();
    float b = other.toFloat();

    return Fraction (a-b);

}

// multiply two fractions 
Fraction Fraction::operator * (const Fraction& other)
{
    int nrm = this->getNumerator() * other.getNumerator();
    int dnm = this->getDenominator() * other.getDenominator();

    int gcd = Fraction::gcd(nrm, dnm);

    return Fraction((nrm/gcd), (dnm/gcd));
}

// divide two fractions 
Fraction Fraction::operator / (const Fraction& other)
{
    return *this * Fraction(other.getDenominator(), other.getNumerator());
}

// compare two fractions  
bool Fraction::operator == (const Fraction& other)
{
    cout << "im here" <<  endl;
    int left = this->getNumerator() * other.getDenominator();
    int right = this->getDenominator() * other.getNumerator();
    if(left == right) return true;
    return false;
}

// compare two fractions  
bool Fraction::operator < (const Fraction& other)
{
    int left = this->getNumerator() * other.getDenominator();
    int right = this->getDenominator() * other.getNumerator();
    if(left > right) return true;
    return false;
}

// compare two fractions  
bool Fraction::operator > (const Fraction& other)
{
    int left = this->getNumerator() * other.getDenominator();
    int right = this->getDenominator() * other.getNumerator();
    if(left < right) return true;
    return false;
}

// compare two fractions  
bool Fraction::operator <= (const Fraction& other)
{
    int left = this->getNumerator() * other.getDenominator();
    int right = this->getDenominator() * other.getNumerator();
    if(left <= right) return true;
    return false;
}

// compare two fractions  
bool Fraction::operator >= (const Fraction& other)
{
    int left = this->getNumerator() * other.getDenominator();
    int right = this->getDenominator() * other.getNumerator();
    if(left >= right) return true;
    return false;
}

// increment fraction 
Fraction& Fraction::operator++()
{
    this->increment();
    return *this;
}

Fraction Fraction::operator++(int)
{

    return Fraction(this->getNumerator()+this->getDenominator(),this->getDenominator());
}

// decrement fraction 
Fraction& Fraction::operator--()
{
    this->decrement();
    return *this;
}

Fraction Fraction::operator--(int)
{
    return Fraction(this->getNumerator()-this->getDenominator(),this->getDenominator());
}









