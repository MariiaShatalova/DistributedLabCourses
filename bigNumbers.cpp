#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class MyBigInteger {
private:
    std::vector<unsigned int> digits; // Масив беззнакових цілих чисел

public:
    // Конструктор за замовчуванням
    MyBigInteger() {}

    // Метод для встановлення числа з рядка у шістнадцятковій системі числення
    void setHex(const std::string& hexStr) {
        // Очищуємо попередні значення
        digits.clear();

        // Проходимо по рядку у зворотньому порядку і додаємо кожну цифру до масиву
        for (auto it = hexStr.rbegin(); it != hexStr.rend(); ++it) {
            unsigned int digit = 0;

            // Перетворюємо шістнадцятковий символ у відповідну цифру
            if (*it >= '0' && *it <= '9') {
                digit = *it - '0';
            }
            else if (*it >= 'A' && *it <= 'F') {
                digit = *it - 'A' + 10;
            }
            else if (*it >= 'a' && *it <= 'f') {
                digit = *it - 'a' + 10;
            }

            // Додаємо цифру до масиву
            digits.push_back(digit);
        }
    }

    // Метод для повернення числа у шістнадцятковій системі числення у вигляді рядка
    std::string getHex() const {
        std::string hexStr;

        // Проходимо по масиву у зворотньому порядку і додаємо кожну цифру до рядка
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

    // Побітова інверсія
    MyBigInteger INV() const {
        MyBigInteger result = *this;

        for (auto& digit : result.digits) {
            digit = ~digit; // Застосовуємо побітову інверсію
        }

        return result;
    }

    // Побітове виключне або (XOR)
    MyBigInteger XOR(const MyBigInteger& other) const {
        MyBigInteger result = *this;

        // Застосовуємо побітове XOR
        for (size_t i = 0; i < std::max(result.digits.size(), other.digits.size()); ++i) {
            if (i < other.digits.size()) {
                result.digits[i] ^= other.digits[i];
            }
            else {
                result.digits.push_back(result.digits[i]); // Замість other.digits[i]
            }
        }

        return result;
    }

    // Побітове або (OR)
    MyBigInteger OR(const MyBigInteger& other) const {
        MyBigInteger result = *this;

        // Застосовуємо побітове OR
        for (size_t i = 0; i < std::max(result.digits.size(), other.digits.size()); ++i) {
            if (i < other.digits.size()) {
                result.digits[i] |= other.digits[i];
            }
        }

        return result;
    }

    // Побітове і (AND)
    MyBigInteger AND(const MyBigInteger& other) const {
        MyBigInteger result;

        // Застосовуємо побітове AND
        for (size_t i = 0; i < std::min(digits.size(), other.digits.size()); ++i) {
            result.digits.push_back(digits[i] & other.digits[i]);
        }

        return result;
    }

    // Зсув праворуч на n біт
    MyBigInteger shiftR(int n) const {
        MyBigInteger result;

        // Зсуваємо кожен розряд на n біт праворуч
        for (size_t i = 0; i < digits.size(); ++i) {
            result.digits.push_back(digits[i] >> n);

            // Зсуваємо найменший розряд вправо в потенційно відсутній розряд
            if (i + 1 < digits.size() && n > 0) {
                result.digits[i] |= (digits[i + 1] & ((1 << n) - 1)) << (32 - n);
            }
        }

        return result;
    }

    // Зсув ліворуч на n біт
    MyBigInteger shiftL(int n) const {
        MyBigInteger result;

        // Зсуваємо кожен розряд на n біт ліворуч
        for (size_t i = 0; i < digits.size(); ++i) {
            result.digits.push_back(digits[i] << n);

            // Додаємо найменший розряд з праворуч
            if (i + 1 < digits.size() && n > 0) {
                result.digits[i] |= (digits[i + 1] >> (32 - n));
            }
        }

        return result;
    }
};

int main() {
    // Приклад використання
    MyBigInteger numberA, numberB, numberC, result;
    numberA.setHex("51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    numberB.setHex("403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");

    // Виконуємо побітове XOR
    numberC = numberA.XOR(numberB);

    // Виводимо результат
    std::cout << "XOR result: " << numberC.getHex() << std::endl;
    return 0;
}
