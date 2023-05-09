
#include <iostream>
#include <numeric>

using namespace std;

// not a good programming but this is the way it only works in clang++ compiler 
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

            // **** getters and setters declarations ****
            int getNumerator() const; // getter for numerator
            int getDenominator() const; // getter for Denominator
            void setNumerator(int nrm); // setter for numerator 
            void setDenominator(int dnm); // setter for Denominator 

            // **** overflow tests declarations ****
            void overflow_multi_test(int num1, int num2);
            void overflow_sub_test(int num1, int num2);
            void overflow_sum_test(int num1, int num2);

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
            friend ostream& operator << (ostream& stream_out, const Fraction& fraction);
            friend std::istream& operator >> (std::istream& stream_in, Fraction& fraction);

    };
}