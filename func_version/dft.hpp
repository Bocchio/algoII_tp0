#ifndef DFT_HPP__
#define DFT_HPP__

#include <cfloat>  // For DBL_EPSILON
#include "../vector.hpp"
#include "../complex.hpp"
#include "func_utils.hpp"  // Because functional programming is fun

#define TOLERANCE DBL_EPSILON*5

class DFT {

    // Calculating the k-th element of the DFT is basically folding, so it's
    // useful to think about it in those terms
    class Fold {
        long k;
        Complex wn;
     public:
        Fold(Complex wn, long k) {
            this->wn = wn;
            this->k = k;
        }

        Complex operator()(const Complex& l, const Complex& r, size_t n) {
            Complex result = l + r*(wn^(k*n));  // Should work
            return result;
        }
    };

    // Calculating the DFT transform is basically applying a function to each
    // element of the original vector, so it's useful to think about it
    // in those terms
    class Transform {
        Complex wn;
        Vector<Complex> x;
     public:
        // Control coupling :( at least the default value makes it a little better
        Transform(const Vector<Complex>& x, bool inverse = false) {
            double argument = -2*M_PI/x.getSize();
            this->x = Vector<Complex>(x);

            if (inverse) {
                argument = -argument;
                this->x /= x.getSize();
            }
            wn = Complex(cos(argument), sin(argument));
        }

        // Non-const reference here, Google's against it
        void operator()(Complex& value, size_t k) {
            Fold folder(wn, k);
            value = reduce(folder, x, Complex(0, 0));

            // But as floating point calculations bring certain mistakes
            if (value.getReal() < TOLERANCE)
                value.setReal(0);
            if (value.getImag() < TOLERANCE)
                value.setImag(0);
        }
    };

 public:
    static Vector<Complex> transform(const Vector<Complex>& x){
        Vector<Complex> result = Vector<Complex>(x);

        Transform dft_transform(result);
        map(dft_transform, result);

        return result;
    }

    static Vector<Complex> inverse(const Vector<Complex>& X){
        Vector<Complex> result = Vector<Complex>(X);

        Transform dft_inverse(result, true);
        map(dft_inverse, result);

        return result;
    }
};

#endif  // DFT_HPP_
