#ifndef AUTOMATA_GEN
#define AUTOMATA_GEN

#include<iostream>
#include<string>
#include<vector>


class Automata {
private:
    std::vector<int> t;

public:
    Automata(std::vector<int> in_t) : t{in_t}
    {}

    //Print the transition table of a DFA
    void print();

    //Run the DFA on a word and return the final state
    int run(std::string input, bool do_print=false);
};

#endif