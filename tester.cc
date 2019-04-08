#include "Ordlistan.h"
#include <iostream>
#include <vector>
#include <fstream>
#include<sstream>
using namespace std;

int main(int argc, char *argv[]) {



    ifstream is("testfil.txt",ifstream::in);
    worder word_list{is,"-o"};
    cout << endl;
    cout << endl;
    word_list.out_data(cout);
    is.close();

    return 0;
}
