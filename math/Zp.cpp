#include <bits/stdc++.h>
using namespace std;

template<class T>
T mypow(T x, unsigned long long p) {
    T ret = 1;
    for(; p > 0; p >>= 1, x *= x) {
        if(p & 1) {
            ret *= x;
        }
    }
    return ret;
}

template<int P>
class Zp {
    public:
        Zp(long long _x = 0): x(_x) {x %= P; x = (x < 0)? x + P: x;}

        Zp& operator+=(const Zp& rhs) {this->x += rhs.x; if(this->x >= P) this->x -= P; return *this;}
        template<class T> Zp& operator+=(const T& rhs) {operator+=(Zp(rhs)); return *this;}
        template<class T> friend Zp operator+(Zp lhs, const T& rhs) {lhs += rhs; return lhs;}

        Zp& operator*=(const Zp& rhs) {this->x = (this->x * rhs.x) % P; return *this;}
        template<class T> Zp& operator*=(const T& rhs) {operator*=(Zp(rhs)); return *this;}
        template<class T> friend Zp operator*(Zp lhs, const T& rhs) {lhs *= rhs; return lhs;}

        Zp operator-() {return 0 - *this;}
        Zp& operator-=(const Zp& rhs) {this->x -= rhs.x; if(this->x < 0) this->x += P; return *this;}
        template<class T> Zp& operator-=(const T& rhs) {operator-=(Zp(rhs)); return *this;}
        template<class T> friend Zp operator-(Zp lhs, const T& rhs) {lhs -= rhs; return lhs;}

        Zp& operator/=(const Zp& rhs) {
            if(rhs.x == 0) {
                throw std::overflow_error("Divide by zero exception");
            }
            operator*=(mypow(rhs, P - 2));
            return *this;
        }
        template<class T> Zp& operator/=(const T& rhs) {operator/=(Zp(rhs)); return *this;}
        template<class T> friend Zp operator/(Zp lhs, const T& rhs) {lhs /= rhs; return lhs;}

        Zp& operator++() {operator+=(1); return *this;}
        Zp operator++(int) {Zp tmp(*this); operator++(); return tmp;}

        bool operator==(const Zp& rhs) {return this->x == rhs.x;}
        template<class T> bool operator==(const T& rhs) {return operator==(Zp(rhs));}
        template<class T> bool operator!=(const T& rhs) {return not operator==(Zp(rhs));}

    private:
        long long x;
        friend ostream& operator<<(ostream& out, const Zp& rhs) {return out << rhs.x;}
        friend istream& operator>>(istream& in, Zp& rhs) {long long t; in >> t; rhs = Zp(t); return in;}
};


int main()
{
    Zp<107> x = 100;
    cout << x + 10 << endl;
    x *= 100;
    cout << x++ << endl;
    cout << ++x << endl;
    auto y = 1/x;
    cout << y << " " << mypow(x, 105) << endl;
    cout << (x * y != 1) << " " << (x * y == 108) << endl;
    cout << x << " " << -x << endl;
    cout << 5 / (3 * (2 + (x - 5 - y))) << endl;
    x = 0;
    try {
        cout << 1 / x << endl;
    } catch(overflow_error& e) {
        cout << e.what() << endl;
    }
//    Zp<107> z;
//    cin >> z;
//    cout << z << endl;
    return 0;
}
