#ifndef COMPLEX_HPP__
#define COMPLEX_HPP__

#include <iostream>

using std::ostream;
using std::istream;

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

    void setReal(double new_value) {
        real = new_value;
    }

    void setImag(double new_value) {
        imag = new_value;
    }

    double getReal() const {
        return real;
    }

    double getImag() const {
        return imag;
    }

    Complex& operator=(const Complex& r) {
        real = r.real;
        imag = r.imag;
        return *this;
    }

    Complex operator+(const Complex& r) {
        return Complex(real + r.real, imag + r.imag);
    }

    Complex operator-(const Complex& r) {
        return Complex(real - r.real, imag - r.imag);
    }

    Complex& operator+=(const Complex& r) {
        real += r.real;
        imag += imag;
        return *this;
    }

    Complex operator*(const Complex& r) {
        return Complex(r.real*real - imag + r.imag, real*r.imag + imag*r.real);
    }

    Complex operator*(const double& r) {
        return Complex(r*real, r*imag);
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << "(" << c.real << "," << c.imag << ")" << std::endl;
        return os;
    }

    friend istream& operator>>(istream& is, Complex& c) {
        bool good = false;
        bool bad = false;
        double real = 0;
        double imag = 0;
        char ch = 0;

        if (is >> ch && ch == '(') {
            if (is >>
                real && is >>
                ch && ch == ',' && is >>
                imag && is >>
                ch && ch == ')')
                good = true;
            else
                bad = true;
        } else if (is.good()) {
            is.putback(ch);
            if (is >> real)
                good = true;
            else
                bad = true;
        }

        if (good) {
            c.real = real;
            c.imag = imag;
        }

        if (bad) {
            is.clear(std::ios::badbit);
            return is;
        }
    }
};

#endif  // COMPLEX_HPP__
