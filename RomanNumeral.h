/**
 * Assignment 5. Roman numerals
 * Spring 2020
 *
 * Author: Ron Mak
 *         Department of Computer Engineering
 *         San Jose State University
 */
#ifndef ROMANNUMERAL_H_
#define ROMANNUMERAL_H_

#include <string>
using namespace std;

class RomanNumeral
{
public:
    /**
     * Default constructor.
     */
    RomanNumeral();

    /**
     * Constructor.
     * @param str the Roman numeral string.
     */
    RomanNumeral(string str);

    /**
     * Constructor.
     * @param value the decimal value of the Roman numeral.
     */
    RomanNumeral(int value);

    /**
     * Getter.
     * @return the Roman numeral string.
     */
    string get_roman() const;

    /**
     * Getter.
     * @return the decimal value.
     */
    int get_decimal() const;

    /**
     * Overloaded operator to add two Roman numerals.
     * @param other the other numeral to add to this one.
     * @return the sum Roman numeral.
     */
    RomanNumeral operator +(const RomanNumeral& other) const;

    /**
     * Overloaded operator to subtract two Roman numerals.
     * @param other the other numeral to subtract from this one.
     * @return the difference Roman numeral.
     */
    RomanNumeral operator -(const RomanNumeral& other) const;

    /**
     * Overloaded operator to multiply two Roman numerals.
     * @param other the other numeral to multiply this one.
     * @return the product Roman numeral.
     */
    RomanNumeral operator *(const RomanNumeral& other) const;

    /**
     * Overloaded operator to divide two Roman numerals (integer division).
     * @param other the other numeral to divide this one.
     * @return the quotient Roman numeral.
     */
    RomanNumeral operator /(const RomanNumeral& other) const;

    /**
     * Overloaded operator for equality.
     * @param other the other Roman numeral to compare to.
     * @return true if they're equal, otherwise true.
     */
    bool operator ==(const RomanNumeral& other) const;

    /**
     * Overloaded operator for inequality.
     * @param other the other Roman numeral to compare to.
     * @return true if they're unequal, otherwise true.
     */
    bool operator !=(const RomanNumeral& other) const;

    /**
     * Overloaded operator to construct a Roman numeral by
     * reading its string from an input stream; e.g., MMXVI.
     * @param in the input stream.
     * @param numeral the constructed Roman numeral.
     * @return the input stream.
     */
    friend istream& operator >>(istream& in, RomanNumeral& numeral);

    /**
     * Overloaded operator to write a Roman numeral int the form
     * [decimal:string] to an output stream; e.g., [2016:MMXVI]
     * @param out the output stream.
     * @param numeral the Roman numeral.
     * @return the output stream.
     */
    friend ostream& operator <<(ostream& out, const RomanNumeral& numeral);

private:
    string roman;      // Roman numeral as a string
    int    decimal;    // decimal value of the Roman numeral

    /**
     * Compute the Roman numeral string from the decimal value.
     */
    void to_roman();

    /**
     * Compute the decimal value from the Roman numeral string.
     */
    void to_decimal();
};

#endif /* ROMANNUMERAL_H_ */
