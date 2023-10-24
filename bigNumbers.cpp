#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class MyBigInteger {
private:
    std::vector<unsigned int> digits;

public:
    MyBigInteger() {}

    // Method for setting a number from a string in hexadecimal
    void setHex(const std::string& hexStr) {
        digits.clear();

        // Go through the line in reverse order and add each number to the array
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

    //The method to return a number in hexadecimal as a string
    std::string getHex() const {
        std::string hexStr;
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            // Extract the lower 4 bits and convert to a hexadecimal character
            char hexChar = (*it & 0xF) + ((*it & 0xF) < 10 ? '0' : 'A' - 10);
            hexStr += hexChar;
        }

        return hexStr;
    }

    MyBigInteger INV() const {
        MyBigInteger result = *this;

        for (unsigned int& digit : result.digits) {
            digit = digit ^ 0xFFFFFFFF;
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

        // Add remaining digits if any
        for (size_t i = std::min(digits.size(), other.digits.size()); i < digits.size(); ++i) {
            result.digits.push_back(digits[i]);
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
                result.digits[i] |= (digits[i + 1] >> (32 - n)) & ((1 << n) - 1);
            }
        }

        return result;
    }
};

int main() {
    MyBigInteger numberA, numberB, numberC, result;
    numberA.setHex("51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    numberB.setHex("403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");

    // XOR
    numberC = numberA.XOR(numberB);
    result.setHex("1182d8299c0ec40ca8bf3f49362e95e4ecedaf82bfd167988972412095b13db8");
    std::cout << "XOR result:  \t" << numberC.getHex() << std::endl;
    std::cout << "Expected result: " << result.getHex() << std::endl;
    if (numberC.getHex() == result.getHex())
        std::cout << "True" << std::endl << std::endl;

    // INV
    numberC = numberA.INV();
    std::cout << "INV result: \t" << numberC.getHex() << std::endl;
    result.setHex("ae409f7beb52a8d95c3e413f670884e4ab004d878072ad758b3e280219b8f15b");
    std::cout << "Expected result: " << result.getHex() << std::endl;
    if (numberC.getHex() == result.getHex())
        std::cout << "True" << std::endl << std::endl;

    // OR
    numberC = numberA.OR(numberB);
    std::cout << "OR result: \t" << numberC.getHex() << std::endl;
    result.setHex("51bff8ad9cafd72eabffbfc9befffffffcffbffaffdd779afdf3d7fdf7f73fbc");
    std::cout << "Expected result: " << result.getHex() << std::endl;
    if (numberC.getHex() == result.getHex())
        std::cout << "True" << std::endl << std::endl;


    // AND
    numberC = numberA.AND(numberB);
    std::cout << "AND result: \t" << numberC.getHex() << std::endl;
    result.setHex("403d208400a113220340808088d16a1b10121078400c1002748196dd62460204");
    std::cout << "Expected result: " << result.getHex() << std::endl;
    if (numberC.getHex() == result.getHex())
        std::cout << "True" << std::endl << std::endl;

    return 0;
}
