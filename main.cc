#include<vector>
#include<iostream>
#include "automata_gen.h"

using namespace std;

int main() {
    vector<int> t{0, 1, 2, 3, 4, 5, 6, 7};
    print_automata(t);
    return 0;
}