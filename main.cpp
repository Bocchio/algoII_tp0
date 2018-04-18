#include <iostream>
#include <iomanip>  // for std::setprecision
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cfloat>
#include <string>

#include "cmdline.hpp"
#include "vector.hpp"
#include "complex.hpp"
#include "dft.hpp"
#include "func_utils.hpp"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::fstream;
using std::ios;
using std::istringstream;
using std::string;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_method(string const &);
static void opt_help(string const &);

// Tabla de opciones de línea de comando. El formato de la tabla
// consta de un elemento por cada opción a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opción lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opción.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opción en caso que no esté explícitamente presente
//   en la línea de comandos del programa. Si la opción no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al método de parseo de la opción,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La última columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opción: cuando la
//   opción es obligatoria, deberá activarse OPT_MANDATORY.
//
// Además, la última entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//
// syntax: {needs argument,
//          short name,
//          long name,
//          default value,
//          parser,
//          flag}
//
static option_t options[] = {
    {1, "i", "input", "-", opt_input, OPT_DEFAULT},
    {1, "o", "output", "-", opt_output, OPT_DEFAULT},
    {1, "m", "method", "DFT", opt_method, OPT_DEFAULT},
    {0, "h", "help", NULL, opt_help, OPT_DEFAULT},
    {0, },
};

static istream *iss = 0;
static ostream *oss = 0;
typedef Vector<Complex> (* transform_method)(const Vector<Complex> &v);
static transform_method transform;
static fstream ifs;
static fstream ofs;


static void opt_input(string const &arg)
{
    if (arg == "-") {
        iss = &cin;
    } else {
        ifs.open(arg.c_str(), ios::in);
        iss = &ifs;
    }

    if (!iss->good()) {
        cerr << "Cannot open "
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void opt_output(string const &arg)
{
    if (arg == "-") {
        oss = &cout;
    } else {
        ofs.open(arg.c_str(), ios::out);
        oss = &ofs;
    }

    if (!oss->good()) {
        cerr << "Cannot open "
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void opt_method(string const &method)
{
    if (method == "DFT")
        transform = DFT::transform;
    else if (method == "IDFT")
        transform = DFT::inverse;
    else {
        cerr << "Unkown mehotd." << endl;
        opt_help("");
    }
}

static void opt_help(string const &arg)
{
    cout << "cmdline [-i file] [-o file] [-m method]"
         << endl;
    exit(0);
}

int main(int argc, char * const argv[])
{
    cmdline cmdl(options);
    cmdl.parse(argc, argv);

    Vector<Complex> v;
    if((*iss >> v).bad()){
        cerr << "The input data was corrupt." << endl;
    }
    *oss << transform(v) << endl;

    return 0;
}
