
#include <iostream>
#include <numeric>

using namespace std;

namespace ariel
{
    class Fraction 
    {
        //  *** attributes ***
        private:
            int numerator; // represent the top of a fraction 
            int denominator; // represent the bottom of a fraction 
        
        public:
            // **** constructors declarations ****
            Fraction(); // defaultive constructor
            Fraction(int nrm, int dnm); // two integers constructor
            Fraction(float num); // float constructor

            // **** getters declarations ****
            int getNumerator() const; // getter for numerator
            int getDenominator() const; // getter for Denominator

            // **** overflow tests declarations ****
            void overflow_multi_test(int a, int b);
            void overflow_sub_test(int a, int b);
            void overflow_sum_test(int a, int b);

            // **** functions declarations ****
            void reduced(); // this function reduce the fraction
            void increment();// this function increment the fraction
            void decrement(); // this function decrement the function


            
            // **** declare overloading operators ****
            // arithmetic
            //+
            Fraction operator + (const Fraction& other); // overloading + operator
            friend Fraction operator+(float num, const Fraction &frac);
            // -
            Fraction operator - (const Fraction& other); // overloading - operator
            friend Fraction operator-(float num, const Fraction &frac);
            // *
            Fraction operator * (const Fraction& other); // overloading * operator
            friend Fraction operator*(float num, const Fraction &frac);
            // /
            Fraction operator / (const Fraction& other); // overloading / operator
            friend Fraction operator / (float num, const Fraction &frac);

            // compersion
            // ==
            friend bool operator==(const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator<(const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator>(const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator<=(const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator>=(const Fraction& fraction1, const Fraction& fraction2);

            // **** increment decrement operators overloading declarations ****
            Fraction& operator ++(); // overloading pre ++ operator
            Fraction operator ++(int); // overloading post ++ operator
            Fraction& operator --(); // overloading pre -- operator
            Fraction operator --(int); // overloading post -- operator

            // **** input output operators overloading declarations ****
            friend ostream& operator << (ostream& os, const Fraction& fraction);
            friend std::istream& operator >> (std::istream& is, Fraction& fraction);

    };
}