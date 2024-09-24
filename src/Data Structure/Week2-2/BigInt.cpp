#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class BigInteger {
private:
    std::string number;
    bool isNegative;

    void removeLeadingZeros() {
        while (number.size() > 1 && number[0] == '0') {
            number.erase(number.begin());
        }
        if (number == "0") isNegative = false;
    }

public:
    BigInteger(const std::string &num) : isNegative(false) {
        if (num.empty()) {
            std::cerr<<"Invalid number";
            exit(0);
        }
        if (num[0] == '-') {
            isNegative = true;
            number = num.substr(1);
        } else {
            number = num;
        }
        removeLeadingZeros();
    }

    BigInteger operator+(const BigInteger &other) const {
        if (isNegative && other.isNegative) {
            BigInteger result = addAbsoluteValues(*this, other);
            result.isNegative = true;
            return result;
        }
        if (!isNegative && !other.isNegative) {
            return addAbsoluteValues(*this, other);
        }
        if (isNegative) {
            return other - BigInteger(number);
        }
        return *this - BigInteger(other.number);
    }

    BigInteger operator-(const BigInteger &other) const {
        if (isNegative && other.isNegative) {
            return BigInteger(other.number) - BigInteger(number);
        }
        if (!isNegative && !other.isNegative) {
            return subtractAbsoluteValues(*this, other);
        }
        if (isNegative) {
            return BigInteger("-" + addAbsoluteValues(*this, other).number);
        }
        return addAbsoluteValues(*this, other);
    }

    BigInteger operator*(const BigInteger &other) const {
        BigInteger result = multiplyAbsoluteValues(*this, other);
        result.isNegative = isNegative != other.isNegative;
        return result;
    }

    BigInteger power(int exponent) const {
        if (exponent == 0) return BigInteger("1");
        if (number == "0") return BigInteger("0");
        BigInteger result("1");
        BigInteger base = *this;

        while (exponent > 0) {
            if (exponent % 2 == 1) result = result * base;
            base = base * base;
            exponent /= 2;
        }
        return result;
    }

    void print() const {
        if (isNegative) std::cout << "-";
        std::cout << number << std::endl;
    }

private:
    static BigInteger addAbsoluteValues(const BigInteger &a, const BigInteger &b) {
        std::string num1 = a.number;
        std::string num2 = b.number;
        std::string result;
        int carry = 0;

        while (num1.size() < num2.size()) num1.insert(num1.begin(), '0');
        while (num2.size() < num1.size()) num2.insert(num2.begin(), '0');

        for (int i = num1.size() - 1; i >= 0; --i) {
            int sum = (num1[i] - '0') + (num2[i] - '0') + carry;
            result.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        if (carry) result.push_back(carry + '0');

        std::reverse(result.begin(), result.end());
        return BigInteger(result);
    }

    static BigInteger subtractAbsoluteValues(const BigInteger &a, const BigInteger &b) {
        std::string num1 = a.number;
        std::string num2 = b.number;
        std::string result;
        bool isNegative = false;

        if (num1 < num2) {
            std::swap(num1, num2);
            isNegative = true;
        }

        int borrow = 0;

        while (num1.size() < num2.size()) num1.insert(num1.begin(), '0');

        for (int i = num1.size() - 1; i >= 0; --i) {
            int sub = (num1[i] - '0') - (num2[i] - '0') - borrow;
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(sub + '0');
        }

        std::reverse(result.begin(), result.end());
        BigInteger res(result);
        res.isNegative = isNegative;
        res.removeLeadingZeros();
        return res;
    }

    static BigInteger multiplyAbsoluteValues(const BigInteger &a, const BigInteger &b) {
        std::string num1 = a.number;
        std::string num2 = b.number;
        std::vector<int> result(num1.size() + num2.size(), 0);

        for (int i = num1.size() - 1; i >= 0; --i) {
            for (int j = num2.size() - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                result[i + j + 1] += mul;
                result[i + j] += result[i + j + 1] / 10;
                result[i + j + 1] %= 10;
            }
        }

        std::string product;
        for (int num : result) {
            if (!(product.empty() && num == 0)) {
                product.push_back(num + '0');
            }
        }

        return product.empty() ? BigInteger("0") : BigInteger(product);
    }
};

int main() {
    std::string operation, input1, input2;
    int exponent;

	std::cout << "Enter operation, operand1, operand2 ('quit' to exit)\n";
    while (true) {
        std::cin>>operation>>input1>>input2;
        if (operation == "exit") break;

        BigInteger num1(input1);
        BigInteger num2(input2);

		if (operation == "add")
        	(num1 + num2).print();
		else if (operation == "substract")
        	(num1 - num2).print();
        else if (operation == "multiply")
        	(num1 * num2).print();
    }

    return 0;
}

