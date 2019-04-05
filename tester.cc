#include "Ordlistan.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {


    ifstream is("exempel.txt",ifstream::in);

    worder word_list{is};
    cout << endl;
    cout << endl;
    word_list.out_data(cout);
    is.close();

    return 0;
}
