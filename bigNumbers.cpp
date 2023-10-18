#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class MyBigInteger {
private:
    std::vector<unsigned int> digits;

public:
    MyBigInteger() {}

    void setHex(const std::string& hexStr) {
        // Î÷èùóºìî ïîïåðåäí³ çíà÷åííÿ
        digits.clear();

        for (auto it = hexStr.rbegin(); it != hexStr.rend(); ++it) {
            unsigned int digit = 0;

            if (*it >= '0' && *it <= '9') {
                digit = *it - '0';
            }
            else if (*it >= 'A' && *it <= 'F') {
                digit = *it - 'A' + 10;
            }
            else if (*it >= 'a' && *it <= 'f') {
                digit = *it - 'a' + 10;
            }

            digits.push_back(digit);
        }
    }

    std::string getHex() const {
        std::string hexStr;

        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            if (*it < 10) {
                hexStr += (*it + '0');
            }
            else {
                hexStr += (*it - 10 + 'A');
            }
        }

        return hexStr;
    }

    MyBigInteger INV() const {
        MyBigInteger result = *this;

        for (auto& digit : result.digits) {
            digit = ~digit;
        }

        return result;
    }

    MyBigInteger XOR(const MyBigInteger& other) const {
        MyBigInteger result = *this;
        
        for (size_t i = 0; i < std::max(result.digits.size(), other.digits.size()); ++i) {
            if (i < other.digits.size()) {
                result.digits[i] ^= other.digits[i];
            }
            else {
                result.digits.push_back(result.digits[i]);
            }
        }

        return result;
    }

    MyBigInteger OR(const MyBigInteger& other) const {
        MyBigInteger result = *this;

        for (size_t i = 0; i < std::max(result.digits.size(), other.digits.size()); ++i) {
            if (i < other.digits.size()) {
                result.digits[i] |= other.digits[i];
            }
        }

        return result;
    }

    MyBigInteger AND(const MyBigInteger& other) const {
        MyBigInteger result;

        for (size_t i = 0; i < std::min(digits.size(), other.digits.size()); ++i) {
            result.digits.push_back(digits[i] & other.digits[i]);
        }

        return result;
    }

    MyBigInteger shiftR(int n) const {
        MyBigInteger result;

        for (size_t i = 0; i < digits.size(); ++i) {
            result.digits.push_back(digits[i] >> n);

            if (i + 1 < digits.size() && n > 0) {
                result.digits[i] |= (digits[i + 1] & ((1 << n) - 1)) << (32 - n);
            }
        }

        return result;
    }

    MyBigInteger shiftL(int n) const {
        MyBigInteger result;

        for (size_t i = 0; i < digits.size(); ++i) {
            result.digits.push_back(digits[i] << n);

            if (i + 1 < digits.size() && n > 0) {
                result.digits[i] |= (digits[i + 1] >> (32 - n));
            }
        }

        return result;
    }
};
