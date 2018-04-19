#ifndef DFT_HPP__
#define DFT_HPP__

#include <cfloat>  // For DBL_EPSILON
#include <iostream>
#include "vector.hpp"
#include "complex.hpp"

#define TOLERANCE DBL_EPSILON*5

class DFT {

 public:
    static Vector<Complex> transform(const Vector<Complex>& x){
        Vector<Complex> y = Vector<Complex>(x);

        size_t N = x.getSize();
        double argument = -2*M_PI/N;
        Complex wn(cos(argument), sin(argument));
        for(Vector<Complex>::iterator yi = y.begin(); yi != y.end(); ++yi){
            size_t i = y.begin() - yi;
            *yi = Complex();
            Complex wn_ = wn^(-i);
            for(Vector<Complex>::iterator xj = x.begin(); xj != x.end(); ++xj){
                size_t j = x.begin() - xj;
                *yi += (*xj)*(wn_^j);
            }

            if (std::abs((*yi).getReal()) < TOLERANCE)
                (*yi).setReal(0);
            if (std::abs((*yi).getImag()) < TOLERANCE)
                (*yi).setImag(0);
        }

        return y;
    }

    static Vector<Complex> inverse(const Vector<Complex>& x){
        Vector<Complex> y = Vector<Complex>(x);

        size_t N = x.getSize();
        double argument = -2*M_PI/N;
        Complex wn(cos(argument), sin(argument));
        for(Vector<Complex>::iterator yi = y.begin(); yi != y.end(); ++yi){
            size_t i = y.begin() - yi;
            *yi = Complex();
            Complex wn_ = wn^(-i);
            for(Vector<Complex>::iterator xj = x.begin(); xj != x.end(); ++xj){
                size_t j = x.begin() - xj;
                *yi += (*xj)*(wn_^j);
            }
            *yi /= N;

            if (std::abs((*yi).getReal()) < TOLERANCE)
                (*yi).setReal(0);
            if (std::abs((*yi).getImag()) < TOLERANCE)
                (*yi).setImag(0);

        }

        return y;
    }
};

#endif  // DFT_HPP_
