#ifndef _BIG_INT_H
#define _BIG_INT_H

#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

class BigInt {
private:

    // the value of the input
    string num;

public:
    // required constructors
    BigInt(string);

    ~BigInt();

    // Check if characters of the input are between '0' and '9'
    bool isValid();

    // return the value of the num
    string getNum() const;

    // override + operator, store inversely each number in an array using a for loop, add each cell of the first number
    // with corresponding cell in the second number and the carry over of previous cells, calculate the carry over of
    // these cells, store the result in sum array, convert each cell of sum array into the string.
    // if the most valuable digits have carry over, the sum array must have one cell more than maximum size of two numbers.
    BigInt operator+(BigInt const &);

};

BigInt::BigInt(string num) : num(num) {

}

BigInt::~BigInt() {

}

bool BigInt::isValid() {

    for (char character : num) {
        if (character < '0' || character > '9') {
            return false;
        }
    }
    return true;
}

string BigInt::getNum() const {
    return num;
}

BigInt BigInt::operator+(BigInt const &other) {

    int carryOver = 0, sum;

    int first[this->num.length()];
    int second[other.num.length()];
    int sumArraySize = max(this->num.length(), other.num.length()) + 1;
    int sumArray[sumArraySize];

    string result;


    for (int i = 0, j = this->num.length() - 1; i < this->num.length(); ++i, --j) {
        first[i] = (int) (this->num.at(j)) - 48;
    }

    for (int i = 0, j = other.num.length() - 1; i < other.num.length(); ++i, --j) {
        second[i] = (int) (other.num.at(j)) - 48;
    }

    for (int i = 0; i < min(this->num.length(), other.num.length()); ++i) {
        sum = carryOver + first[i] + second[i];

        if (sum >= 10) {
            carryOver = sum / 10;
            sum %= 10;
        } else carryOver = 0;

        sumArray[i] = sum;

    }

    for (int i = min(this->num.length(), other.num.length()); i < sumArraySize - 1; ++i) {

        if (this->num.length() > other.num.length()) {

            sum = carryOver + first[i];

            if (sum >= 10) {
                carryOver = sum / 10;
                sum %= 10;
            } else carryOver = 0;

            sumArray[i] = sum;

        } else if (this->num.length() < other.num.length()) {

            sum = carryOver + second[i];

            if (sum >= 10) {
                carryOver = sum / 10;
                sum %= 10;
            } else carryOver = 0;

            sumArray[i] = sum;
        }

    }

    if (carryOver != 0) {
        sumArray[sumArraySize - 1] = carryOver;
    } else sumArraySize--;

    for (int i = sumArraySize - 1; i >= 0; i--) {
        result += to_string(sumArray[i]);
    }

    return BigInt(result);
}

#endif

