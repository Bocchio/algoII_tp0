#ifndef DFT_HPP__
#define DFT_HPP__

#include <cfloat>  // For DBL_EPSILON
#include <cmath>
#include <iostream>
#include "vector.hpp"
#include "complex.hpp"

#define DFT_TOLERANCE 10E-4

class DFT {
 public:
    static Vector<Complex> transform(const Vector<Complex>& x) {
        Vector<Complex> y = Vector<Complex>(x);

        size_t N = x.getSize();
        double argument = -(2*M_PI)/N;
        Complex wn(cos(argument), sin(argument));
        for (Vector<Complex>::iterator yi = y.begin(); yi != y.end(); ++yi) {
            size_t i = yi - y.begin();
            *yi = Complex();
            for (Vector<Complex>::iterator xj = x.begin(); xj != x.end(); ++xj) {
                size_t j = xj - x.begin();
                *yi += (*xj)*(wn^(i*j));
            }

            //  Sets to 0 components that are almost 0
            if (std::abs((*yi).getReal()) < DFT_TOLERANCE)
                (*yi).setReal(0);
            if (std::abs((*yi).getImag()) < DFT_TOLERANCE)
                (*yi).setImag(0);
        }

        return y;
    }

    static Vector<Complex> inverse(const Vector<Complex>& x){
        Vector<Complex> y = Vector<Complex>(x);

        size_t N = x.getSize();
        double argument = (2*M_PI)/N;
        Complex wn(cos(argument), sin(argument));
        for (Vector<Complex>::iterator yi = y.begin(); yi != y.end(); ++yi) {
            size_t i = yi - y.begin();
            *yi = Complex();
            for (Vector<Complex>::iterator xj = x.begin(); xj != x.end(); ++xj) {
                size_t j = xj - x.begin();
                *yi += (*xj)*(wn^(i*j));
            }
            *yi /= N;

            //  Sets to 0 components that are almost 0
            if (std::abs((*yi).getReal()) < DFT_TOLERANCE)
                (*yi).setReal(0);
            if (std::abs((*yi).getImag()) < DFT_TOLERANCE)
                (*yi).setImag(0);
        }

        return y;
    }
};

#endif  // DFT_HPP_
