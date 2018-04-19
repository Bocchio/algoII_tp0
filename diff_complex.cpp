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
#include "errors.hpp"

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

// syntax: {needs argument,
//          short name,
//          long name,
//          default value,
//          parser,
//          flag}
//
static option_t options[] = {
    {1, "i1", "input1", "-", opt_input1, OPT_DEFAULT},
    {1, "i2", "input2", "-", opt_input2, OPT_DEFAULT},
    {0, },
};

static istream *iss1 = 0;
static istream *iss2 = 0;
static fstream ifs1;
static fstream ifs2;


static void opt_input1(string const &arg)
{
    if (arg == "-") {
        iss = &cin;
    } else {
        ifs1.open(arg.c_str(), ios::in);
        iss = &ifs1;
    }

    if (!iss->good()) {
        cerr << ERROR_MSG_CANT_OPEN_FILE
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void opt_input2(string const &arg)
{
    if (arg == "-") {
        iss = &cin;
    } else {
        ifs2.open(arg.c_str(), ios::in);
        iss = &ifs2;
    }

    if (!iss->good()) {
        cerr << ERROR_MSG_CANT_OPEN_FILE
             << arg
             << "."
             << endl;
        exit(1);
    }
}

int main(int argc, char * const argv[])
{
    cmdline cmdl(options);
    cmdl.parse(argc, argv);

    Vector<Complex> v1, v2;
    if((*iss1 >> v1).bad()){
        cerr << ERROR_MSG_CORRUPTED_DATA << endl;
    }
    if((*iss2 >> v2).bad()){
        cerr << ERROR_MSG_CORRUPTED_DATA << endl;
    }
    if(v1 != v2)
        exit(1);

    return 0;
}
