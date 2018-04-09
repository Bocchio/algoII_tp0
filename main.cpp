#include <iostream>
#include <iomanip>  // for std::setprecision
#include <cfloat>
#include "vector.hpp"
#include "complex.hpp"
#include "dft.hpp"
#include "func_utils.hpp"

using std::cout;
using std::endl;

void duppel(int &a) {
    a *= 2;
}

bool bigger(int &a) {
    return a > 20 ? true : false;
}

int summer(int l, int r) {
    return l + r;
}

int main()
{
    Vector<int> a;
    Vector<double> b;
    Vector<int> c;
    Vector<int> d;
    int q = 87;
    //a.append(5);
    a.append(q);
    a.append(7);
    a.append(1);
    a.append(2);
    a.append(3);
    a.append(4);
    a.append(510);
    a.append(72);
    a.append(53);
    a.append(74);
    //a.append(56);
    //a.append(77);
    b = Vector<double>(a.begin(), a.end());
    c = a;
    a[0] = 10;
    q = 78;
    // for(size_t i = 0; i < b.getSize(); i++)
    //    std::cout << b[i] << std::endl;
    // //std::cout << b[1] << std::endl;
    // //std::cout << b[9] << std::endl;

    // std::cout << "----------" << std::endl;

    // for(size_t i = 0; i < a.getSize(); i++)
    //    std::cout << a[i] << std::endl;

    // std::cout << "----------" << std::endl;

    // //for(size_t i = 0; i < c.getSize(); i++)
    // //   std::cout << c[i] << std::endl;
    // for(Vector<int>::iterator it = c.begin(); it != c.end(); it++)
    //     std::cout << *it << std::endl;

    cout << "a: " << a << endl;
    cout << "c: " << c << endl;
    //for(Vector<int>::iterator it = a.begin(); it != a.end(); it++)
    //    c.append(*it);
    cout << "c: " << c << endl;
    cout << a + c << endl;
    d = a + c;
    a[0] = -1;
    cout << "d: " << d << endl;
    // cout << "bigger than 20: " << filter(bigger, d) << endl;
    // map(duppel, d);
    // cout << "d: " << d.getSize() << endl;
    // cout << "d: " << reduce(summer, d, 0) << endl;

    Vector<Complex> dft;
    // dft.append(Complex(0, 0));
    // dft.append(Complex(0, 0));
    // dft.append(Complex(2, 0));
    // dft.append(Complex(3, 0));
    // dft.append(Complex(4, 0));
    // dft.append(Complex(0, 0));
    // dft.append(Complex(0, 0));
    // dft.append(Complex(0, 0));
    dft.append(Complex(1, 0));
    dft.append(Complex(1, 0));
    dft.append(Complex(1, 0));
    dft.append(Complex(1, 0));
    cout << dft << endl;
    cout << DFT::transform(dft) << endl;
    // double argument = -2*M_PI/10;
    // Complex wn(cos(argument), sin(argument));
    // cout << (wn^3) << endl;
    Vector<Complex> result = DFT::transform(dft);
    cout << result << endl;
    cout << DFT::inverse(result) << endl;

    return 0;
}
