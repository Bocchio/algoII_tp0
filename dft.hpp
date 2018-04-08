#ifndef DFT_HPP__
#define DFT_HPP__
#include <cmath>
#include "vector.hpp"
#include "complex.hpp"

class Dft{
    public:
        Vector<Complex> transform(const Vector<Complex>& input){
            size_t i, k, n;
            Vector<Complex> b;
            double wn;
            Complex c, c_nul;

            n=input.getSize();

            for(k=0; k<n; k++){
                for(i=0; i<n; i++){
                    wn=cos(2*k*i*M_PI/n)-sin(2*k*i*input[i].getImag()*M_PI/n);
                    c+=input[i]*wn;
                }
                b.append(c);
                c=c_nul;
            }
            return b;
        }

        Vector<Complex> inverse(const Vector<Complex>& input){
            size_t i, k, n;
            Complex c, c_nul;
            Vector<Complex> b;
            double wn;

            n=input.getSize();
            for(k=0; k<n; k++){
                for(i=0; i<n; i++){
                    wn=cos(2*k*i*M_PI/n)+sin(2*k*i*input[i].getImag()*M_PI/n);
                    c+=input[i]*(wn/n);
                }
                b.append(c);
                c=c_nul;
            }
            return b;
        }
};
#endif
