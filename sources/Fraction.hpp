
#include <iostream>
#include <numeric>

using namespace std;

namespace ariel
{
    class Fraction 
    {
        // attributes 
        private:
            int numerator; // represent the top of a fraction 
            int denominator; // represent the bottom of a fraction 
        
        public:
            Fraction(); // defaultive constructor
            Fraction(int nrm, int dnm); // constructor
            Fraction(float num); // float constructor


            // declare and define getters
            // this function gets two numbers and return their gcd 
            int gcd(int x1, int x2)
            {
                if(x2==0)
                {
                    return x1;
                }
                else
                {
                    gcd(x2, x1 % x2);
                }
                return 1;
            }

            // this function conver the fraction to float number 
            float toFloat() const;

            // return the numerator 
            int getNumerator() const
            {
                return this->numerator;
            } 
            // return the denominator 
            int getDenominator() const
            {
                return this->denominator;
            }
            // this fucntion reduce the fraction 
            void reduced()
            {
                int gcd = std::gcd(this->numerator, this->denominator);
                this->numerator = this->numerator / gcd; 
                this->denominator = this->denominator / gcd; 
            }
            // this function increment the fraction 
            void increment()
            {
                this->numerator = this->numerator + this->denominator;
                this->reduced();
            }

            void decrement()
            {
                this->numerator = this->numerator - this->denominator; 
                this->reduced();
            }


            //functions 
            // this function gets float number and convert it to Fraction and return fraction 
            Fraction floatToFraction (float flt)
            {
                int whole = flt/1; // get the whole part of float 
                float twoDigit = ((flt-whole)*100)/1; // get the 2 digits after to dot
                
                int nrm = whole*100 + twoDigit;
                int dnm = 100;
                int gcd = Fraction::gcd(nrm, dnm); // calc the gcd of nrm and dnm 
                return Fraction((nrm/gcd), (dnm/gcd));
            }

//            void checkOverflow(long nrm, long dnm)
//            {
//                int max_int = std::numeric_limits<int>::max();
//                int min_int = std::numeric_limits<int>::min();
//
//                if(nrm > max_int)
//                {
//                    throw std::overflow_error("numerator is too big");
//                }
//                else if (nrm < min_int)
//                {
//                    throw std::overflow_error("numerator is too small");
//                }
//                else if(dnm > max_int)
//                {
//                    throw std::overflow_error("denominator is too big");
//                }
//                else if (dnm < min_int)
//                {
//                    throw std::overflow_error("denominator is too small");
//                }
//            }

            static bool overflow_multi_test(int num1, int num2)
            {
                int max_int = std::numeric_limits<int>::max();
                int min_int = std::numeric_limits<int>::min();
                if ((num2 > 0 && (num1 > (max_int / num2))) || ((num2 < 0) && (num1 < (max_int / num2))))
                {
                    throw std::overflow_error("Multiplication overflow");
                }

                return true;
            }
            
            // declare overloading opertators 
            // aritmectic 
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

            //comprasion 
            // ==
            friend bool operator==(const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator<(const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator>(const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator<=(const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator>=(const Fraction& fraction1, const Fraction& fraction2);

            // increment decrement 
            Fraction& operator ++(); // overloading pre ++ operator
            Fraction operator ++(int); // overloading post ++ operator
            Fraction& operator --(); // overloading pre -- operator
            Fraction operator --(int); // overloading post -- operator
            // ostream 
            friend ostream& operator << (ostream& os, const Fraction& fraction)
            {
                return (os << fraction.numerator << "/" << fraction.denominator);
            }
            friend std::istream& operator >> (std::istream& is, Fraction& fraction)
            {
                int nrm, dnm;
                is >> nrm >>dnm;

                if (dnm<0 && nrm <0)
                {
                    dnm *=-1;
                    nrm *=-1;
                }
                else if (dnm<0)
                {
                    nrm*=-1;
                    dnm*=-1;
                }
                if(dnm==0)
                {
                    throw std::runtime_error("cant have 0 as denominator");
                }
                if(is.fail() == true)
                {
                    throw std::runtime_error("input error");
                }

                fraction.numerator = nrm;
                fraction.denominator = dnm;
                fraction.reduced();
                return is;
            }
    };
}