#include <iostream>
#include <iomanip>  // for std::setprecision
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cfloat>

#include "cmdline.hpp"
#include "vector.hpp"
#include "complex.hpp"
#include "dft.hpp"
#include "func_utils.hpp"

using std::cout;
using std::endl;
// Prueba de la clase cmdline: dado un factor entero pasado por la
// línea de comando, leemos una secuencia de números que ingresan
// por la entrada estándar, los multiplicamos por ese factor, y
// luego mostramos el resultado por std::cout.
//
// $Id: main.cc,v 1.5 2012/09/15 12:23:57 lesanti Exp $

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_factor(string const &);
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
static option_t options[] = {
    {1, "i", "input", "-", opt_input, OPT_DEFAULT},
    {1, "o", "output", "-", opt_output, OPT_DEFAULT},
    {1, "f", "factor", NULL, opt_factor, OPT_MANDATORY},
    {0, "h", "help", NULL, opt_help, OPT_DEFAULT},
    {0, },
};
static int factor;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

static void
opt_input(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la entrada
    // estándar. De lo contrario, abrimos un archivo en modo
    // de lectura.
    //
    if (arg == "-") {
        iss = &cin;
    } else {
        ifs.open(arg.c_str(), ios::in);
        iss = &ifs;
    }

    // Verificamos que el stream este OK.
    //
    if (!iss->good()) {
        cerr << "cannot open "
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void
opt_output(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la salida
    // estándar. De lo contrario, abrimos un archivo en modo
    // de escritura.
    //
    if (arg == "-") {
        oss = &cout;
    } else {
        ofs.open(arg.c_str(), ios::out);
        oss = &ofs;
    }

    // Verificamos que el stream este OK.
    //
    if (!oss->good()) {
        cerr << "cannot open "
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void
opt_factor(string const &arg)
{
    istringstream iss(arg);

    // Intentamos extraer el factor de la línea de comandos.
    // Para detectar argumentos que únicamente consistan de
    // números enteros, vamos a verificar que EOF llegue justo
    // después de la lectura exitosa del escalar.
    //
    if (!(iss >> factor)
        || !iss.eof()) {
        cerr << "non-integer factor: "
             << arg
             << "."
             << endl;
        exit(1);
    }

    if (iss.bad()) {
        cerr << "cannot read integer factor."
             << endl;
        exit(1);
    }
}

static void
opt_help(string const &arg)
{
    cout << "cmdline -f factor [-i file] [-o file]"
         << endl;
    exit(0);
}

void
multiply(istream *is, ostream *os)
{
    int num;

    while (*is >> num) {
        *os << num * factor
            << "\n";
    }

    if (os->bad()) {
        cerr << "cannot write to output stream."
             << endl;
        exit(1);
    }
    if (is->bad()) {
        cerr << "cannot read from input stream."
             << endl;
        exit(1);
    }
    if (!is->eof()) {
        cerr << "cannot find EOF on input stream."
             << endl;
        exit(1);
    }
}

int
main(int argc, char * const argv[])
{
    cmdline cmdl(options);
    cmdl.parse(argc, argv);
    multiply(iss, oss);
}
