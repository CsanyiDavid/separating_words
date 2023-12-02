#include<vector>
#include<iostream>
#include "automata_gen.h"

using namespace std;

int main() {
    vector<int> t{1, 3, 1, 2, 5, 2, 6, 4, 1, 0, 6, 4, 2, 6};
    Automata a{t};
    a.print();
    a.run("011010010111", true);
    return 0;
}