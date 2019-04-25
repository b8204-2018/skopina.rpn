#include <iostream>
#include "src/rpn.h"


int main(int argc, char **argv) {
    if (argc < 2){
        return -1;
    }
    for (int i = 1; i < argc; i++){
        fstream f(argv[i]);
        string ex;
        getline(f, ex);
        Solver solver;
        cout << ex << " is equal to " << solver.solution(ex) << endl;
    }
    return 0;
}