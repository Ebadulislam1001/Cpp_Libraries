#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Number
{
private:
    // an integer is like a vector
    // it has two elements: magnitude and sign
    string magn;
    char sign;

public:
    // constructors
    Number();
    Number(int num);
    Number(string num);
    Number(Number &num);

    // util methods
    int getSize();
    void show();
    void show(string prefix, string suffix);

    // comparisonoperators
    bool operator<(Number num);
    bool operator>(Number num);
    bool operator==(Number num);

    // arithmetic operators
    Number inverse();
    Number operator+(Number num);
    Number operator-(Number num);
    Number operator*(Number num);
    Number operator/(Number num);
    Number operator%(Number num);
    Number operator^(Number num);
};

Number::Number()
{
    // default contructor initialises Number 0
    this->sign = '+';
    this->magn = "0";
}
Number::Number(int num)
{
    // initilaises a Number from a given integer
    if (num < 0)
    {
        this->sign = '-';
        num = 0 - num;
    }
    else if (num > 0)
    {
        this->sign = '+';
    }
    else
    {
        this->sign = '+';
        this->magn = "0";
        return;
    }

    this->magn = "";
    while (num > 0)
    {
        int lastDigit = num % 10;
        this->magn.push_back((lastDigit) + '0');
        num = num / 10;
    }
};
Number::Number(string num)
{
    // initilaises a Number from a given string
    reverse(num.begin(), num.end());

    this->sign = '+';
    if (num.back() == '+')
    {
        num.pop_back();
    }
    else if (num.back() == '-')
    {
        this->sign = '-';
        num.pop_back();
    }

    while (num.size() > 1 && num.back() == '0')
    {
        // removing leading zeroes
        num.pop_back();
    }
    this->magn = num;
};
Number::Number(Number &num)
{
    // copy constructor
    this->sign = num.sign;
    this->magn = num.magn;
}

int Number::getSize()
{
    return this->magn.size();
}
void Number::show()
{
    printf("%c", this->sign);
    for (int i = this->magn.size(); i > 0; i--)
    {
        printf("%c", this->magn[i - 1]);
    }
}
void Number::show(string prefix, string suffix)
{
    printf("%s", prefix.c_str());
    this->show();
    printf("%s", suffix.c_str());
}

bool Number::operator<(Number op2)
{
    // we have two Numbers
    if (this->sign != op2.sign)
    {
        // both Numbers have opposite signs
        if (this->sign == '-')
        {
            // A < 0 && 0 <= B
            return true;
        }
        // A >= 0 && 0 > B
        return false;
    }

    // both Numbers have same signs
    if (this->magn.size() != op2.magn.size())
    {
        // both Numbers have different no of digits
        return ((this->sign == '+') != (this->magn.size() > op2.magn.size()));
    }

    // both Numbers have same signs and same no of digits
    for (int i = this->magn.size() - 1; i >= 0; i--)
    {
        if (this->magn[i] < op2.magn[i])
        {
            return (this->sign == '+');
        }
        if (this->magn[i] > op2.magn[i])
        {
            return (this->sign == '-');
        }
    }
    // both Numbers are equal
    return false;
}
bool Number::operator==(Number op2)
{
    // (A == B) if and only if (A.sign == B.sign && A.magn == B.magn)
    return (this->sign == op2.sign && this->magn == op2.magn);
}
bool Number::operator>(Number op2)
{
    return !(*this < op2 || *this == op2);
}

Number Number::inverse()
{
    Number result = *this;
    if (this->sign == '-' || this->magn == "0")
    {
        result.sign = '+';
        return result;
    }
    result.sign = '-';
    return result;
}
Number Number::operator+(Number op2)
{
    // Converting negative operands to positive
    if (this->sign == '-' && op2.sign == '-')
    {
        // (A + B)  ==  -((-A) + (-B))
        return (this->inverse() + op2.inverse()).inverse();
    }
    if (this->sign == '-')
    {
        // (A + B)  == -((-A) - B)
        return (this->inverse() - op2).inverse();
    }
    if (op2.sign == '-')
    {
        // (A + B)  ==  A - (-B)
        return (*this - op2.inverse());
    }

    // At this point, both Numbers are positive
    // printf("\n( Addition algo is used )\n");
    Number sum;
    sum.magn = "";

    int i = 0;
    int carry = 0;
    while (i < this->magn.size() && i < op2.magn.size())
    {
        int res = (this->magn[i] - '0') + (op2.magn[i] - '0') + carry;
        carry = res / 10;
        res = res % 10;
        sum.magn.push_back(res + '0');
        i += 1;
    }
    while (i < this->magn.size())
    {
        int res = (this->magn[i] - '0') + carry;
        carry = res / 10;
        res = res % 10;
        sum.magn.push_back(res + '0');
        i += 1;
    }
    while (i < op2.magn.size())
    {
        int res = (op2.magn[i] - '0') + carry;
        carry = res / 10;
        res = res % 10;
        sum.magn.push_back(res + '0');
        i += 1;
    }
    if (carry)
    {
        sum.magn.push_back(carry + '0');
        i += 1;
    }

    return sum;
}
Number Number::operator-(Number op2)
{
    // Converting negative operands to positive
    if (this->sign == '-' && op2.sign == '-')
    {
        // (A - B) == -((-A) - (-B))
        return (this->inverse() - op2.inverse()).inverse();
    }
    if (this->sign == '-')
    {
        // (A - B) == -((-A) + B)
        return (this->inverse() + op2).inverse();
    }
    if (op2.sign == '-')
    {
        // (A - B) == A + (-B)
        return (*this + op2.inverse());
    }

    // At this point, both Numbers are positive
    if (*this == op2)
    {
        // (A - A) == 0
        Number zero(0);
        return zero;
    }
    if (*this < op2)
    {
        // (A - B) == -(B - A)
        return (op2 - *this).inverse();
    }

    // At this point, A >= B >= 0
    // printf("\n( Subtraction algo is used )\n");
    Number difference;
    difference.magn = "";

    int i = 0;
    int carry = 0;
    while (i < this->magn.size() && i < op2.magn.size())
    {
        int res = (this->magn[i] - '0') - (op2.magn[i] - '0') - carry;
        carry = (res < 0) ? 1 : 0;
        res = (res + 10) % 10;
        difference.magn.push_back(res + '0');
        i += 1;
    }
    while (i < this->magn.size())
    {
        int res = (this->magn[i] - '0') - carry;
        carry = (res < 0) ? 1 : 0;
        res = (res + 10) % 10;
        difference.magn.push_back(res + '0');
        i += 1;
    }

    while (difference.magn.size() > 1 && difference.magn.back() == '0')
    {
        // removing leading zeroes
        difference.magn.pop_back();
    }
    return difference;
}
Number Number::operator*(Number op2)
{
    // Converting negative operands to positive
    if (this->sign == '-' && op2.sign == '-')
    {
        // (A * B)  ==  (-A) * (-B)
        return (this->inverse() * op2.inverse());
    }
    if (this->sign == '-')
    {
        // (A * B)  == -((-A) * B)
        return (this->inverse() * op2).inverse();
    }
    if (op2.sign == '-')
    {
        // (A * B)  ==  -(A * (-B))
        return (*this * op2.inverse()).inverse();
    }

    Number zero(0);
    if (*this == zero || op2 == zero)
    {
        return zero;
    }

    // At this point, both Numbers are positive
    // printf("\n( Multiplication algo is used )\n");
    Number product(0); // product is initialised with Number 0
    for (int i = 0; i < this->magn.size(); i++)
    {
        Number partial_product; // what we get after op2 * this->magn[i]
        partial_product.magn = "";
        for (int t = 0; t < i; t++)
        {
            partial_product.magn.push_back('0');
        }

        int carry = 0;
        for (int j = 0; j < op2.magn.size(); j++)
        {
            int res = ((this->magn[i] - '0') * (op2.magn[j] - '0')) + carry; // 0 <= res <= 89
            carry = (res / 10);                                              // 0 <= carry <= 8
            res = res % 10;                                                  // 0 <= res <= 9

            partial_product.magn.push_back(res + '0');
        }

        if (carry) // 0 <= carry <= 8
        {
            partial_product.magn.push_back(carry + '0');
        }
        Number temp = product + partial_product;
        product = temp;
    }
    return product;
}
Number Number::operator/(Number op2)
{
    // Converting negative operands to positive
    if (this->sign == '-' && op2.sign == '-')
    {
        // (A / B)  ==  (-A) / (-B)
        return (this->inverse() / op2.inverse());
    }
    if (this->sign == '-')
    {
        // (A / B)  == -((-A) / B)
        return (this->inverse() / op2).inverse();
    }
    if (op2.sign == '-')
    {
        // (A / B)  ==  -(A / (-B))
        return (*this / op2.inverse()).inverse();
    }

    Number zero(0);
    if (op2 == zero)
    {
        return zero;
        // division is not defined when divisor is 0, but we still return 0
        // because we will never let this case arise in the first place
    }

    // At this point, both Numbers are positive
    // printf("\n( Division algo is used )\n");
    Number dividend = *this; // since we need to update it
    Number quotient(0);      // quotient is initialised with Number 0
    while (dividend > op2 || dividend == op2)
    {
        Number temp = dividend - op2;
        dividend = temp;

        Number one(1);
        quotient = quotient + one;
    }
    return quotient;
}
Number Number::operator%(Number op2)
{
    Number zero(0);
    Number two(2);
    if (op2 < two)
    {
        return zero;
        // modulus must be greater than 1, but we still return 0
        // because we will never let this case arise in the first place
    }

    // At this point, modulus > 1
    // printf("\n( Division algo is used )\n");
    Number remainder = *this; // since we need to update it
    while (remainder > op2 || remainder == op2)
    {
        Number temp = remainder - op2;
        remainder = temp;
    }
    while (remainder < zero)
    {
        Number temp = remainder + op2;
        remainder = temp;
    }
    return remainder;
}
Number Number::operator^(Number op2)
{
    Number zero(0);
    Number one(1);

    if (op2.sign == '-')
    {
        // (A ^ -1) == (1 / A) == (0)
        return zero;
    }
    if (op2 == zero)
    {
        // (A ^ 0) == 1
        return one;
    }
    if (op2 == one)
    {
        // (A ^ 1) == A
        return *this;
    }

    // At this point, 1 < B
    Number two(2);
    Number parity = op2 % two; // (B % 2)
    Number halfEx = op2 / two; // (B / 2)

    // B = halfEx + halfEx + parity
    Number temp1 = this->operator^(halfEx); // A ^ (halfEx)
    Number temp2 = temp1 * temp1;           // A ^ (halfEx + halfEx)
    Number power = temp2 *((*this) ^ parity);        // A ^ (halfEx + halfEx + parity) = (A ^ B)

    // op2.show("returning after calculting power for(",")\n");
    return power;
}

int main()
{
    Number A;

    while (true)
    {
        int choice;
        cout << "\n################ MENU ################\n";
        A.show("\nNum = (", ")\n");
        cout << "\n\t1. Find Sum        \n\t2. Find Difference";
        cout << "\n\t3. Find Product    \n\t4. Find Quotient";
        cout << "\n\t5. Find Remainder  \n\t6. Find Power";
        cout << "\n\t0. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)

        {
        case 0:
        {
            cout << "\nGoodBye World!\n";
            return 0;
        }
        case 1:
        {
            string strNum;
            cout << "Enter second operand: ";
            cin >> strNum;
            Number B(strNum);

            Number Result = A + B;
            A.show("\nResult = (", ")");
            B.show(" + (", ")");
            Result.show(" = (", ")\n");

            A = Result;
            break;
        }
        case 2:
        {
            string strNum;
            cout << "Enter second operand: ";
            cin >> strNum;
            Number B(strNum);

            Number Result = A - B;
            A.show("\nResult = (", ")");
            B.show(" - (", ")");
            Result.show(" = (", ")\n");

            A = Result;
            break;
        }
        case 3:
        {
            string strNum;
            cout << "Enter second operand: ";
            cin >> strNum;
            Number B(strNum);

            Number Result = A * B;
            A.show("\nResult = (", ")");
            B.show(" * (", ")");
            Result.show(" = (", ")\n");

            A = Result;
            break;
        }
        case 4:
        {
            string strNum;
            cout << "Enter second operand: ";
            cin >> strNum;
            Number B(strNum);
            Number zero(0);

            if (B == zero)
            {
                printf("Exception: Cannot divide by ZERO !\n");
                break;
            }

            Number Result = A / B;
            A.show("\nResult = (", ")");
            B.show(" / (", ")");
            Result.show(" = (", ")\n");

            A = Result;
            break;
        }
        case 5:
        {
            string strNum;
            cout << "Enter second operand: ";
            cin >> strNum;
            Number B(strNum);
            Number two(2);

            if (B < two)
            {
                printf("Exception: Modulus must be greater than (+1) !\n");
                break;
            }

            Number Result = A % B;
            A.show("\nResult = (", ")");
            B.show(" % (", ")");
            Result.show(" = (", ")\n");

            A = Result;
            break;
        }
        case 6:
        {
            string strNum;
            cout << "Enter second operand: ";
            cin >> strNum;
            Number B(strNum);

            Number Result = A ^ B;
            A.show("\nResult = (", ")");
            B.show(" ^ (", ")");
            Result.show(" = (", ")\n");
            printf("No of digits = %d", Result.getSize());

            A = Result;
            break;
        }
        }
    }
}
