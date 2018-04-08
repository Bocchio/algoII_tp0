#ifndef COMPLEX_HPP__
#define COMPLEX_HPP__

#include <iostream>

class Complex{
    double real, imag;

 public:
    Complex(double a, double b) {
        real = a;
        imag = b;
    }

    Complex() {
        real = 0.0;
        imag = 0.0;
    }

    Complex(const Complex& c) {
        real = c.real;
        imag = c.imag;
    }

    ~Complex() {}

    void setReal(double n) {
        real = n;
    }

    void setImag(double n) {
        imag = n;
    }

    double getReal() const {
        return real;
    }

    double getImag() const {
        return imag;
    }

    Complex& operator=(const Complex& a) {
        real = a.real;
        imag = a.imag;
        return *this;
    }

    Complex operator+(const Complex& a) {
        return Complex(real+a.real, imag+a.imag);
    }

    Complex operator-(const Complex& a) {
        return Complex(real-a.real, imag-a.imag);
    }

    Complex& operator+=(const Complex& a) {
        real += a.real;
        imag += imag;
        return *this;
    }

    Complex operator*(const Complex& a) {
        return Complex(a.real*real-imag + a.imag, real*a.imag + imag*a.real);
    }

    Complex operator*(const double& d) {
        return Complex(d*real, d*imag);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << "," << c.imag << ")" << std::endl;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Complex& c) {
        bool good = false;
        bool bad = false;
        double real = 0;
        double imag = 0;
        char ch = 0;

        if(is>>ch && ch=='('){
            if(is>>real && is>> ch && ch==',' && is>>imag && is>>ch && ch==')')
                good = true;
            else
                bad = true;
        }
        else if(is.good()){
            is.putback(ch);
            if(is>>real)
                good = true;
            else
                bad = true;
        }
        if(good){
            c.real = real;
            c.imag = imag;
        }
        if(bad){
            is.clear(std::ios::badbit);
            return is;
        }
    }

};

#endif
