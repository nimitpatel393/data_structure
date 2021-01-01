/**
 * Assignment 5. Roman numerals
 * Spring 2020
 *
 * Author: Ron Mak
 *         Department of Computer Engineering
 *         San Jose State University
 */
#include <iostream>
#include <fstream>
#include <string>
#include "RomanNumeral.h"

using namespace std;

RomanNumeral::RomanNumeral() : roman(""), decimal(0) {}

RomanNumeral::RomanNumeral(string str) : roman(str)
{
    // Compute the decimal value.
    to_decimal();
}

RomanNumeral::RomanNumeral(int value) : decimal(value)
{
    // Compute the Roman numeral string.
    to_roman();
}

string RomanNumeral::get_roman()   const { return roman; }
int    RomanNumeral::get_decimal() const { return decimal; }

RomanNumeral RomanNumeral::operator +(const RomanNumeral& other) const
{
    RomanNumeral sum(decimal + other.decimal);
    return sum;
}

RomanNumeral RomanNumeral::operator -(const RomanNumeral& other) const
{
    RomanNumeral diff(decimal - other.decimal);
    return diff;
}

RomanNumeral RomanNumeral::operator *(const RomanNumeral& other) const
{
    RomanNumeral prod(decimal*other.decimal);
    return prod;
}

RomanNumeral RomanNumeral::operator /(const RomanNumeral& other) const
{
    RomanNumeral quot(decimal/other.decimal);
    return quot;
}

bool RomanNumeral::operator ==(const RomanNumeral& other) const
{
    return decimal == other.decimal;
}

bool RomanNumeral::operator !=(const RomanNumeral& other) const
{
    return decimal != other.decimal;
}

istream& operator >>(istream& in, RomanNumeral& numeral)
{
    string str;
    in >> str;

    numeral.roman = str;
    numeral.to_decimal();

    return in;
}

ostream& operator <<(ostream& out, const RomanNumeral& numeral)
{
    out << "[" << numeral.decimal << ":" << numeral.roman << "]";
    return out;
}

void RomanNumeral::to_roman()
{
    int temp = decimal;
    roman = "";

    // Append Roman numeral characters to the string
    // and subtract their corresponding values.

    while (temp >= 1000)
    {
        roman += "M";
        temp -= 1000;
    }

    if (temp >= 900)
    {
        roman += "CM";
        temp -= 900;
    }
    else if (temp >= 500)
    {
        roman += "D";
        temp -= 500;
    }
    else if (temp >= 400)
    {
        roman += "CD";
        temp -= 400;
    }

    while (temp >= 100)
    {
        roman += "C";
        temp -= 100;
    }

    if (temp >= 90)
    {
        roman += "XC";
        temp -= 90;
    }
    else if (temp >= 50)
    {
        roman += "L";
        temp -= 50;
    }
    else if (temp >= 40)
    {
        roman += "XL";
        temp -= 40;
    }

    while (temp >= 10)
    {
        roman += "X";
        temp -= 10;
    }

    if (temp >= 9)
    {
        roman += "IX";
        temp -= 9;
    }
    else if (temp >= 5)
    {
        roman += "V";
        temp -= 5;
    }
    else if (temp >= 4)
    {
        roman += "IV";
        temp -= 4;
    }

    while (temp >= 1)
    {
        roman += "I";
        temp--;
    }
}

void RomanNumeral::to_decimal()
{
    int length = roman.length();
    decimal = 0;

    // Scan the Roman numeral string from left to right
    // and add the corresponding character values.
    for (int i = 0; i < length; i++)
    {
        switch (roman[i])
        {
            case 'M':
                decimal += 1000;
                break;

            case 'D':
                decimal += 500;
                break;

            case 'C':
                if (i+1 < length)
                {
                    switch (roman[i+1])
                    {
                        case 'D':  // CD
                            decimal += 400;
                            i++;
                            break;

                        case 'M':  // CM
                            decimal += 900;
                            i++;
                            break;

                        default:
                            decimal += 100;
                            break;
                    }
                }
                else decimal += 100;
                break;

            case 'L':
                decimal += 50;
                break;

            case 'X':
                if (i+1 < length)
                {
                    switch (roman[i+1])
                    {
                        case 'L':  // XL
                            decimal += 40;
                            i++;
                            break;

                        case 'C':  // XC
                            decimal += 90;
                            i++;
                            break;

                        default:
                            decimal += 10;
                            break;
                    }
                }
                else decimal += 10;
                break;

            case 'V':
                decimal += 5;
                break;

            case 'I':
                if (i+1 < length)
                {
                    switch (roman[i+1])
                    {
                        case 'V':  // IV
                            decimal += 4;
                            i++;
                            break;

                        case 'X':  // IX
                            decimal += 9;
                            i++;
                            break;

                        default:
                            decimal++;
                            break;
                    }
                }
                else decimal++;
                break;
        }
    }
}
