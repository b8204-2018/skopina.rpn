#include <iostream>
#include <fstream>
#include "src/rpn.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2){
        return -1;
    }
    for (int i = 1; i < argc; i++){
        fstream f(argv[i]);
        string ex;
        getline(f, ex);
        Solver solver;
        cout << ex;
        try {
            double solution = solver.solution(ex);
            cout << " is equal to " << solution << endl;
        } catch (Exception &err) {
            cout << " " << err.getError();
        }

        
    }
    return 0;
}