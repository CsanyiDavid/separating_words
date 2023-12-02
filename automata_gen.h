#ifndef AUTOMATA_GEN
#define AUTOMATA_GEN

#include<vector>
#include<iostream>


class Automata {
private:
    std::vector<int> t;

public:
    Automata(std::vector<int> in_t) : t{in_t}
    {}

    //Print the transition table of a DFA
    void print();
};

#endif