#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Integer
{
private:
    // an Integer is like a vector
    // it has two elements: magnitude and sign
    char sign;
    vector<int> magn;

public:
    // constructors
    Integer();
    Integer(int num);
    Integer(string num);
    Integer(char sign, vector<int> num);
    Integer(const Integer &num);

    // util methods
    int digitCount();
    void show();
    void show(string prefix, string suffix);

    // comparison operators
    bool operator<(Integer num);
    bool operator>(Integer num);
    bool operator==(Integer num);
    bool operator!=(Integer num);
    bool operator<=(Integer num);
    bool operator>=(Integer num);

    // arithmetic methods
    bool isNegative();
    bool isNonNegative();
    bool isOdd();
    bool isEven();
    bool isFactorOf(Integer num);
    bool isMultipleOf(Integer num);

    // arithmetic operators
    Integer inverse();
    Integer operator+(Integer num);
    Integer operator-(Integer num);
    Integer operator*(Integer num);
    Integer operator/(Integer num);
    Integer operator%(Integer num);
    Integer operator^(Integer num);
};

Integer::Integer()
{
    // default contructor initialises an Integer 0
    this->sign = '+';
    this->magn = {0};
}
Integer::Integer(int num)
{
    // initilaises an Integer from a given int
    this->sign = '+';
    if (num == 0)
    {
        this->magn = {0};
        return;
    }
    else if (num < 0)
    {
        this->sign = '-';
        num = 0 - num;
    }

    this->magn.clear();
    while (num > 0)
    {
        int last3Digit = num % 1000;
        this->magn.push_back(last3Digit);
        num = num / 1000;
    }
}
Integer::Integer(string num)
{
    // initilaises an Integer from a given string
    // TODO : Validate the format of the input string i.e. REGEX = ^[+-]?[0-9]+$

    reverse(num.begin(), num.end());
    if (num.back() != '+' && num.back() != '-')
    {
        num.push_back('+');
    }
    this->sign = (num.back() == '+')? '+' : '-';
    num.pop_back();

    while (num.size() > 1 && num.back() == '0')
    {
        // removing leading zeroes
        num.pop_back();
    }
    while (num.size() % 3 != 0)
    {
        // adding leading zeroes for padding
        num.push_back('0');
    }

    this->magn.clear();
    for (int i = 0; i < num.size(); i += 3)
    {
        int temp = (num[i] - '0') + (num[i + 1] - '0') * 10 + (num[i + 2] - '0') * 100;
        this->magn.push_back(temp);
    }
}
Integer::Integer(char sign, vector<int> num)
{
    // initilaises an Integer from a given vector of ints
    // TODO : check if the passed vector is in valid format i.e. 0 <= num[i] <= 999 for i in range(num.size())
    this->sign = sign;
    reverse(num.begin(), num.end());
    this->magn = num;
}
Integer::Integer(const Integer &num)
{
    // copy constructor
    this->sign = num.sign;
    this->magn = num.magn;
}

int Integer::digitCount()
{
    int count = this->magn.size() * 3;
    if (this->magn.back() < 100)
    {
        count -= 1;
    }
    if (this->magn.back() < 10)
    {
        count -= 1;
    }
    // if (this->magn.back() < 1)
    // {
    //     count -= 1;
    // }
    return count;
}
void Integer::show()
{
    printf("%c", this->sign);
    for (int i = this->magn.size() - 1; i >= 0; i--)
    {
        if (i < this->magn.size() - 1 || this->magn[i] > 99)
            printf("%d", (this->magn[i] / 100) % 10);
        if (i < this->magn.size() - 1 || this->magn[i] > 9)
            printf("%d", (this->magn[i] / 10) % 10);
        printf("%d,", (this->magn[i] / 1) % 10);
    }
    printf("\b");
}
void Integer::show(string prefix, string suffix)
{
    printf("%s", prefix.c_str());
    this->show();
    printf("%s", suffix.c_str());
}

bool Integer::operator<(Integer op2)
{
    // we have two Integers
    if (this->sign != op2.sign)
    {
        // both Integers have opposite signs
        return (this->isNegative());
    }

    // both Integers have same signs
    if (this->magn.size() < op2.magn.size())
    {
        return (this->isNonNegative());
    }
    if (this->magn.size() > op2.magn.size())
    {
        return (this->isNegative());
    }
    // both Integers have same signs and have same no of digits
    for (int i = this->magn.size() - 1; i >= 0; i--)
    {
        if (this->magn[i] < op2.magn[i])
        {
            return (this->isNonNegative());
        }
        if (this->magn[i] > op2.magn[i])
        {
            return (this->isNegative());
        }
    }
    // both Integers are equal
    return false;
}
bool Integer::operator>(Integer op2)
{
    return op2 < *this;
}
bool Integer::operator==(Integer op2)
{
    return (this->sign == op2.sign && this->magn == op2.magn);
}
bool Integer::operator!=(Integer op2)
{
    return !(*this == op2);
}
bool Integer::operator<=(Integer op2)
{
    return !(*this > op2);
}
bool Integer::operator>=(Integer op2)
{
    return !(*this < op2);
}
bool Integer::isNegative()
{
    return (this->sign == '-');
}
bool Integer::isNonNegative()
{
    return (this->sign == '+');
}
bool Integer::isOdd()
{
    return (this->magn[0] % 2 == 1);
}
bool Integer::isEven()
{
    return (this->magn[0] % 2 == 0);
}
bool Integer::isFactorOf(Integer op2)
{
    return (op2 % *this == Integer(0));
}
bool Integer::isMultipleOf(Integer op2)
{
    return (*this % op2 == Integer(0));
}

Integer Integer::inverse()
{
    Integer result = *this;
    if (*this > Integer(0))
    {
        result.sign = '-';
    }
    else
    {
        result.sign = '+';
    }
    return result;
}
Integer Integer::operator+(Integer op2)
{
    // Converting negative operands to positive
    if (this->isNegative() && op2.isNegative())
    {
        // (A + B)  ==  -((-A) + (-B))
        return (this->inverse() + op2.inverse()).inverse();
    }
    if (this->isNegative())
    {
        // (A + B)  == -((-A) - B)
        return (this->inverse() - op2).inverse();
    }
    if (op2.isNegative())
    {
        // (A + B)  ==  A - (-B)
        return (*this - op2.inverse());
    }

    // At this point, both Integers are positive
    if (*this < op2)
    {
        // (A + B) == (B + A)
        return (op2 + *this);
    }

    // At this point, A >= B >= 0
    Integer sum;
    sum.magn.clear();

    int i = 0;
    int carry = 0;
    while (i < this->magn.size() && i < op2.magn.size())
    {
        int res = this->magn[i] + op2.magn[i] + carry;
        carry = res / 1000;
        res = res % 1000;
        sum.magn.push_back(res);
        i += 1;
    }
    while (i < this->magn.size())
    {
        int res = this->magn[i] + carry;
        carry = res / 1000;
        res = res % 1000;
        sum.magn.push_back(res);
        i += 1;
    }
    if (carry)
    {
        sum.magn.push_back(carry);
        i += 1;
    }

    return sum;
}
Integer Integer::operator-(Integer op2)
{
    // Converting negative operands to positive
    if (this->isNegative() && op2.isNegative())
    {
        // (A - B) == -((-A) - (-B))
        return (this->inverse() - op2.inverse()).inverse();
    }
    if (this->isNegative())
    {
        // (A - B) == -((-A) + B)
        return (this->inverse() + op2).inverse();
    }
    if (op2.isNegative())
    {
        // (A - B) == A + (-B)
        return (*this + op2.inverse());
    }

    // At this point, both Integers are positive
    if (*this < op2)
    {
        // (A - B) == -(B - A)
        return (op2 - *this).inverse();
    }
    if (*this == op2)
    {
        // (A - A) == 0
        return Integer(0);
    }

    // At this point, A >= B >= 0
    Integer difference;
    difference.magn.clear();

    int i = 0;
    int carry = 0;
    while (i < this->magn.size() && i < op2.magn.size())
    {
        int res = this->magn[i] - op2.magn[i] - carry;
        carry = (res < 0) ? 1 : 0;
        res = (res + 1000) % 1000;
        difference.magn.push_back(res);
        i += 1;
    }
    while (i < this->magn.size())
    {
        int res = this->magn[i] - carry;
        carry = (res < 0) ? 1 : 0;
        res = (res + 1000) % 1000;
        difference.magn.push_back(res);
        i += 1;
    }

    while (difference.magn.size() > 1 && difference.magn.back() == 0)
    {
        // removing leading zeroes
        difference.magn.pop_back();
    }
    return difference;
}
Integer Integer::operator*(Integer op2)
{
    // Converting negative operands to positive
    if (this->isNegative() && op2.isNegative())
    {
        // (A * B)  ==  (-A) * (-B)
        return (this->inverse() * op2.inverse());
    }
    if (this->isNegative())
    {
        // (A * B)  == -((-A) * B)
        return (this->inverse() * op2).inverse();
    }
    if (op2.isNegative())
    {
        // (A * B)  ==  -(A * (-B))
        return (*this * op2.inverse()).inverse();
    }

    // At this point, both Integers are positive
    Integer zero(0);
    if (*this == zero || op2 == zero)
    {
        return zero;
    }
    if (*this < op2)
    {
        // (A * B)  ==  (B * A)
        return op2 * *this;
    }

    // At this point, A >= B >= 0
    Integer product(0); // product is initialised with Integer 0
    for (int i = 0; i < op2.magn.size(); i++)
    {
        Integer partial_product; // what we get after this->magn * op2.magn[i]
        partial_product.magn.clear();
        for (int t = 0; t < i; t++)
        {
            // to adjust and align the places
            partial_product.magn.push_back(0);
        }

        int carry = 0;
        for (int j = 0; j < this->magn.size(); j++)
        {
            int res = ((this->magn[j]) * (op2.magn[i])) + carry; // 0 <= res <= 998,999
            carry = (res / 1000);                                // 0 <= carry <= 998
            res = res % 1000;                                    // 0 <= res <= 999

            partial_product.magn.push_back(res);
        }

        if (carry) // 0 <= carry <= 998
        {
            partial_product.magn.push_back(carry);
        }
        Integer temp = product + partial_product;
        product = temp;
    }
    return product;
}
Integer Integer::operator/(Integer op2)
{
    // Given the relations :
    // [A = B*Q + R] && [0 <= R < B]
    // We say:
    // (A / B) gives Q the quotient
    // (A % B) gives R the remainder

    Integer zero(0);
    Integer one(1);

    if (op2.isNegative())
    {
        // (A / B)  ==  -(A / (-B))
        return (*this / op2.inverse()).inverse();
    }

    // At this point, B >= 0
    if (op2 == zero)
    {
        // Division operation (A / B) is not defined for (B == 0), but we still return 0
        // Raise an exception here
        return zero;
    }

    // At this point, B > 0
    if (op2 == one)
    {
        // (A / 1) == A
        return *this;
    }

    //  At this point, B > 1
    Integer remainder = *this % op2;
    Integer dividend = *this - remainder;
    if (dividend.isNegative())
    {
        // (A / B) == -((-A) / B)
        return (dividend.inverse() / op2).inverse();
    }

    // At this point, A >= 0 && B > 1
    if (dividend < op2)
    {
        return zero;
    }

    // At this point, A >= B > 1
    Integer quoteint;
    remainder = zero;

    while (dividend.magn.size() > 0)
    {
        // Extracting next digit from dividend
        int nextDigit = dividend.magn.back();
        dividend.magn.pop_back();

        // removing all leading zeros from remainder
        while (remainder.magn.size() > 0 && remainder.magn.back() == 0)
        {
            remainder.magn.pop_back();
        }
        // next 3 lines are equivalent to remainder.push_front();
        reverse(remainder.magn.begin(), remainder.magn.end());
        remainder.magn.push_back(nextDigit);
        reverse(remainder.magn.begin(), remainder.magn.end());

        // finding the largest multiple of divisor that fits in the remainder
        int low = 0;
        int upp = 999;
        int factor;
        while (low <= upp)
        {
            int mid = low + (upp - low) / 2;
            Integer multiple = op2 * Integer(mid);
            if (multiple > remainder)
            {
                upp = mid - 1;
            }
            else
            {
                factor = mid;
                low = mid + 1;
            }
        }
        // updating the remainder for next iteration
        Integer multiple = op2 * Integer(factor);
        Integer temp = remainder - multiple;
        remainder = temp;
        quoteint.magn.push_back(factor);
    }
    // adjusting the quotient
    reverse(quoteint.magn.begin(), quoteint.magn.end());
    while (quoteint.magn.size() > 1 && quoteint.magn.back() == 0)
    {
        // removing leading zeros
        quoteint.magn.pop_back();
    }
    return quoteint;
}
Integer Integer::operator%(Integer op2)
{
    // Given the relations :
    // [A = B*Q + R] && [0 <= R < B]
    // We say:
    // (A / B) gives Q the quotient
    // (A % B) gives R the remainder

    Integer zero(0);
    Integer one(1);

    if (op2 <= one)
    {
        // Modulus operation (A % B) is not defined for (B <= 1), but we still return 0
        // TODO : Raise an exception here
        return zero;
    }

    // At this point, 1 < B
    if (this->isNegative())
    {
        // (A % B) == B - (((-A) - 1) % B) - 1
        return op2 - ((this->inverse() - one) % op2) - one;
    }

    // At this point, A >= 0 && B > 1
    if (*this < op2)
    {
        return *this;
    }

    // At this point, A >= B > 1
    Integer dividend = *this; // a copy for making updates
    Integer remainder;

    while (dividend.magn.size() > 0)
    {
        // Extracting next digit from dividend
        int nextDigit = dividend.magn.back();
        dividend.magn.pop_back();

        // removing ALL leading zeros from remainder
        while (remainder.magn.size() > 0 && remainder.magn.back() == 0)
        {
            remainder.magn.pop_back();
        }
        // next 3 lines are equivalent to remainder.push_front();
        reverse(remainder.magn.begin(), remainder.magn.end());
        remainder.magn.push_back(nextDigit);
        reverse(remainder.magn.begin(), remainder.magn.end());

        // finding the largest multiple of divisor that fits in the remainder
        int low = 0;
        int upp = 999;
        int factor;
        while (low <= upp)
        {
            int mid = low + (upp - low) / 2;
            Integer multiple = op2 * Integer(mid);
            if (multiple > remainder)
            {
                upp = mid - 1;
            }
            else
            {
                factor = mid;
                low = mid + 1;
            }
        }
        // updating the remainder for next iteration
        Integer multiple = op2 * Integer(factor);
        Integer temp = remainder - multiple;
        remainder = temp;
    }
    return remainder;
}
Integer Integer::operator^(Integer op2)
{
    Integer zero(0);
    Integer one(1);

    if (op2.isNegative())
    {
        if (*this == zero)
        {
            // Exponent operation (A ^ B) is not defined for (A == 0 && B < 0), but we still return 0
            // TODO : Raise an exception here
            return zero;
        }
        if (this->isNonNegative() || (this->isNegative() && op2.isEven()))
        {
            return zero;
        }
        return Integer(-1);
    }

    // At this point, B >=0
    if (op2 == zero)
    {
        return one;
    }

    // At this point, B > 0
    if (op2 == one)
    {
        return *this;
    }

    // At this point, B > 1
    if (this->isNegative())
    {
        if (op2.isEven())
        {
            return this->inverse() ^ op2;
        }
        else
        {
            return (this->inverse() ^ op2).inverse();
        }
    }

    // At this point, A >= 0 && B > 1
    if (*this == zero)
    {
        return zero;
    }

    // At this point, A > 0 && B > 1
    Integer parity = op2.isEven() ? zero : one; // (B % 2)
    Integer halfEx = op2 / Integer(2);          // (B / 2)

    // B = halfEx + halfEx + parity
    Integer temp1 = this->operator^(halfEx);    // A ^ (halfEx)
    Integer temp2 = temp1 * temp1;              // A ^ (halfEx + halfEx)
    Integer power = temp2 * ((*this) ^ parity); // A ^ (halfEx + halfEx + parity) = (A ^ B)

    return power;
}

int main()
{
    Integer A;

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

        if (choice == 0)
        {
            cout << "\nGoodBye World!\n";
            return 0;
        }
        if (choice < 1 || choice > 6)
        {
            printf("Exception: Invalid choice !\n");
            continue;
        }

        string strNum;
        cout << "Enter second operand: ";
        cin >> strNum;
        Integer B(strNum);

        Integer zero(0);
        Integer two(2);
        if (choice == 4 && B == zero)
        {
            printf("Exception: Cannot divide by Integer(0) !\n");
            continue;
        }
        if (choice == 5 && B < two)
        {
            printf("Exception: Modulus must be greater than Integer(+1) !\n");
            continue;
        }

        Integer Result;
        string res_str;
        switch (choice)
        {
        case 1:
        {
            Result = A + B;
            res_str = " + (";
            break;
        }
        case 2:
        {
            Result = A - B;
            res_str = " - (";
            break;
        }
        case 3:
        {
            Result = A * B;
            res_str = " * (";
            break;
        }
        case 4:
        {
            Result = A / B;
            res_str = " / (";
            break;
        }
        case 5:
        {
            Result = A % B;
            res_str = " % (";
            break;
        }
        case 6:
        {
            Result = A ^ B;
            res_str = " ^ (";
            break;
        }
        }
        A.show("\nResult = (", ")");
        B.show(res_str, ")");
        Result.show(" = (", ")\n");
        A = Result;
    }
}
