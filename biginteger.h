#ifndef UNTITLED_BIGINTEGER_H
#define UNTITLED_BIGINTEGER_H


#endif //UNTITLED_BIGINTEGER_H

#include "iostream"
#include <vector>
#include <string>
using namespace std;
class BigInteger {

public:

    void get_zeros()
    {
        int origin_l = l;
        for(int i = origin_l - 1; i > -1; --i)
        {
            if(a[i] > 0)
            {
              break;
            }
            else
            {
                l--;
            }
        }
        if(l == 0)
        {
            sign = 0;
        }
    }
    vector<int> a;
    int l = 0;
    int sign = 0;
    BigInteger(uint64_t z)
    {
        while (z > 0)
        {
            a.push_back(z%10);
            z/=10;
            l++;
        }
    }
    BigInteger(int64_t z)
    {
        while (z > 0)
        {
            a.push_back(z%10);
            z/=10;
            l++;
        }
        if(z < 0)
        {
            z*= -1;
            sign = 1;
            while (z > 0)
            {
                a.push_back(z%10);
                z/=10;
                l++;
            }
        }
    }
    template<class T>
    BigInteger(T some){
        *this = BigInteger((int64_t)(some));
    }
    BigInteger ()
    {}
    BigInteger(string s)
    {
        l = s.length();
        if(s[0] == '-') {
            sign = 1;
        }
        for(int i = l - 1; i > -1; --i)
        {
            if(s[i] != '-') {
                a.push_back(int(s[i]) - int('0'));
            }
        }
        if(s[0] == '-')
            l--;
        get_zeros();
    }

    bool operator==( BigInteger other)
    {
        get_zeros();
        other.get_zeros();
        return (this->toString() == other.toString());

    }
    bool operator !=(BigInteger other)
    {
        return !(*this == other);
    }
    bool operator>(const BigInteger& other)
    {

        get_zeros();
        if(*this == other)
            return false;
        if(sign == 0 && other.sign == 1)
        {
            return true;
        }
        if(sign == 1 && other.sign == 0)
        {
            return false;
        }
        if(sign == 0 && other.sign == 0)
        {
            if(l > other.l)
                return true;
            if(l < other.l)
                return false;
            if(l == other.l)
            {
                int i1 = l - 1, i2 = other.l - 1;
                while(a[i1] == other.a[i2])
                {
                    i1--;
                    i2--;
                }
                if(a[i1] > other.a[i2])
                    return true;
                else
                    return false;
            }
        }
        return false;
    }
    bool operator <(BigInteger& other)
    {
        return (other > *this);
    }
    bool operator >=( BigInteger& other)
    {
        if(*this > other || *this == other)
            return true;
        else
            return false;
    }
    bool operator <=(BigInteger& other)
    {
        return (other >= *this);
    }
    BigInteger operator-()
    {
        if(this->l == 0)
            return *this;
        BigInteger minus = *this;

        minus.sign = 1 - minus.sign;
        return minus;
    }
    BigInteger operator-( const BigInteger& oth) {
        BigInteger other = oth;
        if(other == BigInteger(0))
        {
            return *this;
        }
        if(this->l == 0)
            return -other;
        if (sign != other.sign) {
            {

                BigInteger newVal;
                int l2 = other.l;
                for (int i = 0; i < max(l, l2); ++i) {
                    if ((int)newVal.a.size() < i + 1) {
                        newVal.a.push_back(0);
                    }
                    if (i < l)
                        newVal.a[i] += a[i];
                    if (i < l2)
                        newVal.a[i] += other.a[i];
                    newVal.l = i + 1;
                    if ((int)newVal.a[i] > 9) {
                        if ((int)newVal.a.size() < i + 2) {
                            newVal.a.push_back(0);
                        }
                        newVal.a[i + 1] += newVal.a[i] / 10;
                        newVal.a[i] %= 10;
                        newVal.l = i + 2;
                    }
                }
                newVal.sign = this->sign;
                return newVal;
            }
        } else {
            BigInteger ans;
            bool u[l];
            for (int i = 0; i < l; ++i) {
                u[i] = false;
            }

            int u1 = sign, u2 = other.sign;
            sign = 0;
            other.sign = 0;
            if (*this >= other) {

                int i;
                for (i = 0; i < other.l; ++i) {
                    if (a[i] >= other.a[i]) {
                        ans.a.push_back(a[i] - other.a[i]);
                        ans.l++;
                    } else {
                        int j = i;
                        ans.a.push_back(a[i] + 10 - other.a[i]);
                        ans.l++;
                        while (a[j + 1] == 0) {
                            j++;
                            if (j < other.l) {
                                ans.a.push_back(9 - other.a[j]);
                                ans.l++;
                            } else {
                                ans.a.push_back(9);
                                ans.l++;
                            }
                        }
                        u[j + 1] = true;
                        a[j + 1]--;
                        i = j;
                    }

                }
                for (i = i; i < l; ++i) {
                    ans.a.push_back(a[i]);
                    ans.l++;
                }

                for (int i = 0; i < l; ++i) {
                    if (u[i])
                        a[i]++;
                }
            } else {
                ans = other - *this;
            }
            if ((*this >= other && u1 == 0) || (*this < other && u1 == 1)) {
                sign = u1;
                other.sign = u2;
                ans.sign = 0;
                return ans;
            } else {
                ans.sign = 1;
                sign = u1;
                other.sign = u2;
                return ans;

            }
        }
    }
    BigInteger& operator-=(const BigInteger& other)
    {
        BigInteger weird = other;
        *this =  *this - weird;
        return *this;
    }
    BigInteger operator+(const BigInteger& other)
    {
        BigInteger newVal;
        BigInteger key = other;
        key =  -key;
        newVal = *this - (key);
        return newVal;
    }

    BigInteger& operator+=(BigInteger other)
    {
        *this =  *this + other;
        return *this;
    }

    BigInteger operator*(BigInteger& other)
    {
        if(this->l == 1)
        {
            if(sign == other.sign || (sign == 0 && other.sign == 1))
                return multiply_with_int(other, a[0]);
            else
                return -((multiply_with_int(other, a[0])));
        }
        if(this->l == 0 || other.l == 0)
        {
            return BigInteger{0};
        }
        BigInteger newVal;
        for(int i = 0; i < l; ++i)
        {

            BigInteger k;
            for(int p = 0; p < i; ++p)
                k.a.push_back(0);
            k.l = i;
            for(int j = 0; j < other.l; ++j)
            {
                k.a.push_back(a[i]*other.a[j]);
                k.l++;
            }
            newVal+=k;
        }
        for(int i = 0; i < newVal.l-1; ++i)
        {
            if(newVal.a[i] > 9)
            {
                newVal.a[i+1]+= newVal.a[i]/10;
                newVal.a[i]%=10;
            }
        }
        if (newVal.a[newVal.l - 1] > 9)
        {
            newVal.a.push_back(newVal.a[newVal.l - 1]/10);
            newVal.a[newVal.l - 1]%=10;
            newVal.l++;
        }
        if(sign == other.sign)
            newVal.sign = 0;
        else
            newVal.sign = 1;
        return newVal;
    }
    BigInteger& operator*=(BigInteger other)
    {
        *this = *this*other;
        return *this;
    }
    BigInteger& operator/=(int o)
    {
        if(o == 1)
            return *this;
        if(o == -1)
        {
            this->sign = 1 - sign;
            return *this;
        }
        if(o != 2)
        {
            BigInteger z(o);
            *this/=z;
            return *this;
        }

        this->get_zeros();
        if(this->l == 0 || (this->l == 1 && this->a[0] < 2)) {
            *this-=*this;
            return *this;
        }
        BigInteger ans;
        if(sign)
            ans.sign = 1;
        for(int i = 0; i < l; ++i)
        {
            ans.a.push_back(0);
        }
        ans.l = l;
        for(int i = l-1; i > -1; --i)
        {
            if(a[i] >= 0)
            {
                ans.a[i] = a[i]/2;
                a[i]%=2;
            }
            if(a[i] > 0)
            {
                if(i > 0)
                    a[i-1]+= 10;
            }
        }
        *this = ans;
        this->get_zeros();
        return *this;
    }

    BigInteger operator/(BigInteger& other)
    {
        BigInteger le(0), r = (*this);
        r.sign = 0;
        r = r+1;
        int orsign1 = sign, orsign2 = other.sign;
        sign = 0;
        other.sign = 0;
        BigInteger ed = BigInteger(1);
        while((r - le) > ed)
        {
            BigInteger m = (r+le);
            m/=2;
            if(m*other > *this)
            {
                r = m;
            }
            else
                le = m;
        }
        sign = orsign1;
        other.sign = orsign2;
        if(sign == other.sign)
            le.sign = 0;
        else
            le.sign = 1;
        return le;
    }
    BigInteger& operator/=(BigInteger other)
    {
        *this = *this/other;
        return *this;
    }
    BigInteger operator%(BigInteger& other)
    {
        BigInteger key = *this/other;
        key*=other;
        return *this - key;
    }
    string toString()
    {
        this->get_zeros();
        if(l == 0)
        {return "0";}
        string s, ans;
        for(int i = 0; i < l; ++i)
        {
            s+=char(a[i] + int('0'));
        }
        if(sign == 1)
            ans = "-";
        for(int i = 0; i < l; ++i)
        {
            ans+=s[l - i - 1];
        }
        return ans;
    }
    BigInteger& operator%=(BigInteger other)
    {
        *this = *this % other;
        return *this;
    }
    BigInteger& operator++() {
        *this= *this + 1;
        return *this;
    }
    BigInteger operator++(int) {
        BigInteger temp = *this;
        *this += 1;
        return temp;
    }
    BigInteger& operator--() {
        *this = *this - 1;
        return *this;
    }
    BigInteger operator--(int) {
        BigInteger temp = *this;
        --(*this);
        return temp;
    }
    explicit operator bool()  {
        BigInteger z(0);
        return (*this != z);
    }
    static BigInteger multiply_with_int(BigInteger &x, int other)
    {
        if(x.l == 0)
            return x;
        if(other > 9 || other < 0)
        {
            BigInteger newVal(other);
            return x*newVal;
        }
        int key = 0;
        BigInteger newVal = x;
        for(int i = 0; i < x.l-1; ++i)
        {
            newVal.a[i] = x.a[i]*other;
            newVal.a[i]+=key;
            key=(newVal.a[i])/10;
            newVal.a[i]%=10;
        }
        newVal.a[x.l-1]*=other;
        newVal.a[x.l-1]+=key;
        if(newVal.a[x.l-1] > 9)
        {
            int f = newVal.a[x.l-1];
            newVal.a[x.l-1]%=10;
            newVal.a.push_back(f/10);
            newVal.l++;
        }
        newVal.get_zeros();
        return newVal;
    }

    friend ostream& operator<<(ostream& os, const BigInteger& x);
    friend istream& operator>>(istream& is, BigInteger& x);

};

ostream& operator<<(ostream& os,  const BigInteger& x)
{
    BigInteger ans = x;
    os << ans.toString();
    return os;
}

istream &operator>>(istream &is, BigInteger &x) {
    string s;
    is >> s;
    x = BigInteger(s);
    return is;
}